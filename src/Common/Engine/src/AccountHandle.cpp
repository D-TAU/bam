#include "AccountHandle.h"
#include <iostream>
#include <algorithm>
#include <sqlite_modern_cpp.h>

using namespace std;
using namespace sqlite;

AccountHandle::AccountHandle(database& db): m_db(db)
{
}

AccountHandle::~AccountHandle()
{
}

template<class...Args>
void AccountHandle::notifyListeners(void (IAccountListener::*method)(Args...args), Args&&...args)
{
    for(auto it : m_AccountListenerList)
        ((it)->*method)(args...);
}

void AccountHandle::addListener(IAccountListener &l)
{
    m_AccountListenerList.push_back(&l);
}

void AccountHandle::removeListener(IAccountListener &l)
{
    auto it = std::find(m_AccountListenerList.begin(), m_AccountListenerList.end(), &l);
    if(it != m_AccountListenerList.end())
        m_AccountListenerList.erase(it);
}

bool AccountHandle::create(const std::string& name,
            double interestsAnnualRate,
            const string& interestPayoffDay,
            const Date& openDate,
            double initialBalance)
{
    m_name                  = name;
    m_interestsRate         = interestsAnnualRate;
    m_interestsPayoffDay    = interestPayoffDay;
    m_openDate              = openDate;

    m_BalancesTblName       = m_name + "Balances";
    m_TransactionsTblName   = m_name + "Transactions";
    m_InterestsTblName      = m_name + "Interests";


    if(!exists())
    {
        createTables();
        createTriggers();
        /*open-date transaction*/
        deposit(openDate, initialBalance);
    }
    else
        return false;

    return true;
}

bool AccountHandle::open(const std::string& name,
            double interestsAnnualRate,
            const string& interestPayoffDay,
            const Date& openDate)
{
    m_name                  = name;
    m_interestsRate         = interestsAnnualRate;
    m_interestsPayoffDay    = interestPayoffDay;
    m_openDate              = openDate;

    m_BalancesTblName       = m_name + "Balances";
    m_TransactionsTblName   = m_name + "Transactions";
    m_InterestsTblName      = m_name + "Interests";


    if(exists())
        updateInterestsTable();
    else
        return false;

    return true;
}

bool AccountHandle::deposit(const Date& date, double amount)
{
    if(date >= m_openDate)
    {
        m_db << "INSERT INTO " + m_TransactionsTblName + "(TransactionDate, Amount) VALUES(?,  ?);"
            << date.toStrFmt() << amount;
        //update interest table after this transaction
        updateInterestsTableAfter(date);
        return true;
    }
    else
        return false;
}

bool AccountHandle::withdraw(const Date& date, double amount)
{
    double balance = getBalanceOn(date);

    // withdraw transaction is not allowed if it leads to negative balance
    if((balance >= amount) and (date >= m_openDate))
    {
        m_db << "INSERT INTO " + m_TransactionsTblName + "(TransactionDate, Amount) VALUES(?,  ?);"
            << date.toStrFmt() << -amount;
        //update interest table after this transaction
        updateInterestsTableAfter(date);
        return true;
    }
    else
        return false;
}

void AccountHandle::createTables()
{
    createBalancesTable();
    createTransactionsTable();
    createInterestsTable();
}

void AccountHandle::createBalancesTable()
{
    m_db <<
        "CREATE TABLE IF NOT EXISTS " + m_BalancesTblName +
        "("
            "OnDate DATETIME UNIQUE,"
            "Balance FLOAT DEFAULT 0,"
            "DeltaDays INTEGER DEFAULT 0"
        ");";
}

void AccountHandle::createTransactionsTable()
{
    m_db <<
        "CREATE TABLE IF NOT EXISTS " + m_TransactionsTblName +
        "("
            "Id INTEGER PRIMARY KEY,"
            "InsertionDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
            "TransactionDate DATETIME,"
            "Amount FLOAT"
        ");";
}

void AccountHandle::createInterestsTable()
{
    m_db << "CREATE TABLE IF NOT EXISTS " + m_InterestsTblName + " "
        "("
            "Id INTEGER PRIMARY KEY,"
            "InsertionDate DATETIME DEFAULT CURRENT_TIMESTAMP,"
            "TransactionDate DATETIME UNIQUE,"
            "Amount FLOAT"
        ");";
}

void AccountHandle::createTriggers()
{
    createOnInterestsInsertTrigger();
    createOnTransactionInsertTrigger();
    createOnTransactionDeleteTrigger();
    createOnInterestsUpdateTrigger();
}

void AccountHandle::createOnInterestsInsertTrigger()
{
    string trigName = m_name + "OnInterestsInsert";
    m_db << "CREATE TRIGGER IF NOT EXISTS " + trigName + " AFTER INSERT ON " + m_InterestsTblName + " "
    "BEGIN "
        "INSERT OR IGNORE INTO " + m_BalancesTblName + "(OnDate, Balance, DeltaDays) "
            "VALUES("
                "new.TransactionDate,"
                "coalesce((SELECT Balance FROM " + m_BalancesTblName + " "
                        "WHERE onDate = (SELECT MAX(OnDate) FROM " + m_BalancesTblName + " "
                            "WHERE OnDate < new.TransactionDate)), 0),"
                "coalesce((SELECT (strftime('%s', new.TransactionDate) - strftime('%s', OnDate))/60/60/24 FROM " + m_BalancesTblName + " "
                        "WHERE OnDate = (SELECT Max(OnDate) FROM " + m_BalancesTblName + " "
                            "WHERE OnDate < new.TransactionDate)), 0)"
            ");"
        "UPDATE " + m_BalancesTblName + " SET Balance = Balance + new.amount "
            "WHERE OnDate >= new.TransactionDate;"

//        "UPDATE  " + m_BalancesTblName + "  SET DeltaDays = (SELECT (strftime('%s', OnDate) - strftime('%s', new.TransactionDate))/60/60/24"
//                                            "FROM  " + m_BalancesTblName + " "
//                        "WHERE OnDate = (SELECT Min(OnDate) FROM  " + m_BalancesTblName + " "
//                            "WHERE OnDate > new.TransactionDate))"
//            "WHERE OnDate = (SELECT Min(OnDate) FROM  " + m_BalancesTblName + " "
//                            "WHERE OnDate > new.TransactionDate);"
    "END;";
}

void AccountHandle::createOnTransactionInsertTrigger()
{
    string trigName = m_name + "OnTransactionInsert";
    m_db << "CREATE TRIGGER IF NOT EXISTS " + trigName + " AFTER INSERT ON  " + m_TransactionsTblName + " "
    "BEGIN "
        "INSERT OR IGNORE INTO " + m_BalancesTblName + "(OnDate, Balance, DeltaDays) "
            "VALUES("
                "new.TransactionDate,"
                "coalesce((SELECT Balance FROM " + m_BalancesTblName + " "
                        "WHERE OnDate = (SELECT MAX(OnDate) FROM " + m_BalancesTblName + " "
                            "WHERE OnDate < new.TransactionDate)), 0),"
                "coalesce((SELECT (strftime('%s', new.TransactionDate) - strftime('%s', OnDate))/60/60/24 FROM " + m_BalancesTblName + " "
                        "WHERE OnDate = (SELECT Max(OnDate) FROM " + m_BalancesTblName + " "
                            "WHERE OnDate < new.TransactionDate)), 0)"
            ");"
    "UPDATE " + m_BalancesTblName + " SET Balance = Balance + new.amount "
        "WHERE OnDate >= new.TransactionDate;"
    "UPDATE " + m_BalancesTblName + " SET DeltaDays = (SELECT (strftime('%s', OnDate) - strftime('%s', new.TransactionDate))/60/60/24 "
                                            "FROM " + m_BalancesTblName + " "
                        "WHERE OnDate = (SELECT Min(OnDate) FROM " + m_BalancesTblName + " "
                            "WHERE OnDate > new.TransactionDate)) "
        "WHERE OnDate = (SELECT Min(OnDate) FROM " + m_BalancesTblName + " "
                            "WHERE OnDate > new.TransactionDate);"
    "END;";
}

void AccountHandle::createOnTransactionDeleteTrigger()
{
    string trigName = m_name + "OnTransactionDelete";
    m_db << "CREATE TRIGGER IF NOT EXISTS " + trigName + " AFTER DELETE ON  " + m_TransactionsTblName + " "
    "BEGIN "
        "UPDATE " + m_BalancesTblName + " SET Balance = Balance - old.amount "
            "WHERE OnDate >= old.TransactionDate;"
    "END;";
}

void AccountHandle::createOnInterestsUpdateTrigger()
{
    string trigName = m_name + "OnInterestsUpdate";
    m_db << "CREATE TRIGGER IF NOT EXISTS " + trigName + " AFTER UPDATE ON " + m_InterestsTblName + " "
        "BEGIN "
            "UPDATE " + m_BalancesTblName + " SET Balance = Balance + (new.amount - old.amount) "
                "WHERE OnDate >= new.TransactionDate;"
        "END;";
}

double AccountHandle::getBalanceOn(const Date& date) const
{
    double result = 0;

    m_db << "SELECT Balance FROM " + m_BalancesTblName + " "
                    "WHERE OnDate = (SELECT Max(OnDate) FROM " + m_BalancesTblName + " "
                        "WHERE OnDate <= " + date.toSqlFmt() + ");"
            >> [&result](double balance)
                {
                    result = balance;
                };
    return result;
}

double AccountHandle::getBalance() const
{
    return getBalanceOn(Date::today());
}

Date AccountHandle::getInterestsPayoffDateAfter(const Date& date) const
{
    Date result;
    string dateStr = date.toStrFmt();
    /*replace days field with interests payoff day*/
    result = dateStr.replace(dateStr.end()-2, dateStr.end(), m_interestsPayoffDay);
    if(result <= date)
        result += 1_months;

    return result;
}

Date AccountHandle::getLastInterestsPayoffDateBefore(const Date& date) const
{
    string dateStr = "";
    m_db << "SELECT TransactionDate FROM " + m_InterestsTblName + " "
                    "WHERE TransactionDate = (SELECT Max(TransactionDate) FROM " + m_InterestsTblName + " "
                        "WHERE TransactionDate < " + date.toSqlFmt() + ");"
            >> [&dateStr](string tdate)
                {
                    dateStr = tdate;
                };
    if(dateStr.empty())
    {
        Date openDate;
        //find first balance field date
        m_db << "SELECT Min(OnDate) FROM " + m_BalancesTblName
                >> [&openDate](string ondate)
                {
                    openDate = ondate;
                };
        //first payoff date after open date
        //shifted by 1 month back (before the first payoff date)
        return (getInterestsPayoffDateAfter(openDate) - 1_months);
    }
    else
        return dateStr;
}

void AccountHandle::updateInterestsTable()
{
    updateInterestsTableAfter(Date::today());
}

void AccountHandle::updateInterestsTableAfter(const Date& somedate)
{
    Date date, today, nextDate, lastDate;
    const double percentagePerDay = m_interestsRate / 100 / 365;
    double interestsPerDay = 0;

    /*get current date*/
    today = Date::today();

    date = getLastInterestsPayoffDateBefore(somedate);
    nextDate = getInterestsPayoffDateAfter(date);
    //cout << "x:" << date << " " << nextDate << endl;
    while(nextDate <= today)
    {
        double interests = 0;
        lastDate = date;
        m_db << "SELECT OnDate, Balance, DeltaDays FROM " + m_BalancesTblName + " "
                "WHERE OnDate BETWEEN " + date.toSqlFmt() + " AND " + nextDate.toSqlFmt()
                >> [&](string onDate, double bal, int ddays)
                {
                    interests += interestsPerDay * ddays;
                    interestsPerDay = bal * percentagePerDay;
                    lastDate = onDate;
                };
        interests += interestsPerDay * (nextDate - lastDate);

        //insert and update interests
        upsertInterests(nextDate, interests);

        date = nextDate;
        nextDate = getInterestsPayoffDateAfter(date);
    }
}

void AccountHandle::upsertInterests(const Date& date, double amount)
{
    m_db << "INSERT OR IGNORE INTO " + m_InterestsTblName + "(TransactionDate, Amount) VALUES(?,  ?);"
        << date.toStrFmt() << 0;
    m_db << "UPDATE " + m_InterestsTblName + " SET Amount = (?) "
        "WHERE TransactionDate = " + date.toSqlFmt() + ";"
            << amount;
}

bool AccountHandle::exists() const
{
    const size_t NB_TABLES = 3;
    const size_t NB_TRIGGERS = 4;
    bool tablesExist = false;
    bool triggersExist = false;

    m_db << "SELECT count(name) FROM sqlite_master"
                    " WHERE type='table' AND ("
                    "name = '" + m_BalancesTblName + "' OR "
                    "name = '" + m_InterestsTblName + "' OR "
                    "name = '" + m_TransactionsTblName + "');"
            >> [&tablesExist](int cnt)
                {
                    if(cnt == NB_TABLES)
                        tablesExist = true;
                };
    m_db << "SELECT count(name) FROM sqlite_master"
                    " WHERE type='trigger' AND ("
                        "name = '" + m_name + "OnInterestsInsert' OR "
                        "name = '" + m_name + "OnTransactionInsert' OR "
                        "name = '" + m_name + "OnTransactionDelete' OR "
                        "name = '" + m_name + "OnInterestsUpdate');"
            >> [&triggersExist](int cnt)
                {
                    if(cnt == NB_TRIGGERS)
                        triggersExist = true;
                };

    return (tablesExist and triggersExist);
}

bool AccountHandle::deleteTransaction(int id)
{
    Date date;

    /*select transaction with given id and memorize its date*/
    m_db << "SELECT TransactionDate FROM " + m_TransactionsTblName + " "
                "WHERE Id = (?);" << id
            >> [&date](string str)
                {
                    date = str;
                };
    /*delete transaction by id*/
    m_db << "DELETE FROM " + m_TransactionsTblName + " "
                "WHERE Id = (?);"
                << id;
    //update interest table after this transaction
    updateInterestsTableAfter(date);

    return true;
}

const std::string& AccountHandle::getName() const
{
    return m_name;
}

const std::string& AccountHandle::getInterestsPayoffDay() const
{
    return m_interestsPayoffDay;
}

double AccountHandle::getInterestsRate() const
{
    return m_interestsRate;
}

double AccountHandle::getPaidInterests() const
{
    double result = 0;

    m_db << "SELECT Sum(Amount) FROM " + m_InterestsTblName + ";"
            >> [&result](double sum)
                {
                    result = sum;
                };

    return result;
}

double AccountHandle::getAccruedInterests() const
{
    double interests = 0;
    Date date, today, lastDate;
    const double percentagePerDay = m_interestsRate / 100 / 365;
    double interestsPerDay = 0;

    /*get current date*/
    today = Date::today();
    date = getLastInterestsPayoffDateBefore(today);

    m_db << "SELECT OnDate, Balance, DeltaDays FROM " + m_BalancesTblName + " "
                    "WHERE OnDate BETWEEN " + date.toSqlFmt() + " AND " + today.toSqlFmt()
                        >> [&](string onDate, double bal, int ddays)
                            {
                                interests += interestsPerDay * ddays;
                                interestsPerDay = bal * percentagePerDay;
                                lastDate = onDate;
                            };
    interests += interestsPerDay * (today - lastDate);

    return interests;
}

std::vector<AccountHandle::TransactionStruct> AccountHandle::getTransactions() const
{
    std::vector<TransactionStruct> transactions;
    TransactionStruct transaction;

    m_db << "SELECT Id, TransactionDate, Amount, "
                    + TransactionStruct::getTextForEnum(TransactionStruct::ttUSER) + " "
                "FROM " + m_TransactionsTblName + " "
            "UNION ALL "
            "SELECT Id, TransactionDate, Amount, "
                    + TransactionStruct::getTextForEnum(TransactionStruct::ttINTERESTS) + " "
                "FROM " + m_InterestsTblName + " "
                "ORDER BY TransactionDate;"
            >> [&](int id, std::string date, double amount, int type)
            {
                transaction.id = id;
                transaction.date = date;
                transaction.amount = amount;
                transaction.type = static_cast<TransactionStruct::Type>(type);

                transactions.push_back(transaction);
            };
    return transactions;
}
