#include "AccountManager.h"

#include "Account.h"

using namespace sqlite;
using namespace std;

AccountManager::AccountManager()
{
    m_db = new database(":memory:");// FIXME: change to file-based database
    m_pAccount = new Account(*m_db);

    //creates accounts table if it did not exist
    createAccountsTable();
    //populate accounts list
    populateAccountsMap();
}

AccountManager::~AccountManager()
{
    delete m_pAccount;
    delete m_db;
}

void AccountManager::createAccountsTable()
{
    m_dbTblName = "ManagedAccounts";
    (*m_db) <<
        "CREATE TABLE IF NOT EXISTS " + m_dbTblName +
        "("
            "Id INTEGER PRIMARY KEY,"
            "Name TEXT UNIQUE,"
            "OpenDate DATETIME,"
            "InterestsRate FLOAT,"
            "PayoffDay TEXT"
        ");";
}

void AccountManager::populateAccountsMap()
{
    (*m_db) << "SELECT Id, Name FROM " + m_dbTblName + ";"
            >> [&](int id, string name)
                {
                    this->m_accountsMap.insert(AccountsMap::value_type (id, AccountProps(name)));
                };
}

const AccountManager::AccountsMap& AccountManager::getAccountsMap() const
{
    return m_accountsMap;
}

void AccountManager::setCurrentAccount(int id)
{
    if(m_accountsMap.find(id) == m_accountsMap.end())
        m_pAccount = nullptr;
    else
    	openAccount(id);
}

Account* AccountManager::getCurrentAccount()
{
    return m_pAccount;
}

int AccountManager::createAccount(const string& name, double irate,
                                const string & pday, const Date& odate, double ibalance)
{
    //try to insert account into the accounts table
    int id = insertAccount(name, irate, pday, odate);

    // check if account props were inserted into accounts table
    if(id > 0)
    {
        //create and populate account's tables
        m_pAccount->create(name, irate, pday, odate, ibalance);
        //append account to the accounts map
        m_accountsMap.insert(AccountsMap::value_type (id, AccountProps(name)));
    }

    return id;
}

int AccountManager::insertAccount(const string& name, double irate,
                                const string & pday, const Date& odate)
{
    int ID;
    (*m_db) << "INSERT OR IGNORE INTO " + m_dbTblName
                + "(Name, OpenDate, InterestsRate, PayoffDay) "
                "VALUES(?, ?, ?, ?);"
        << name << odate.toStrFmt() << irate << pday;

    (*m_db) << "SELECT LAST_INSERT_ROWID();" >>
                [&ID](int id)
                {
                    ID = id;
                };
    //check if id existed in the list of accounts: row was not created
    if(m_accountsMap.find(ID) != m_accountsMap.end())
        ID = 0;

    return ID;
}

void AccountManager::openAccount(int id)
{
    (*m_db) << "SELECT Name, OpenDate, InterestsRate, PayoffDay FROM " + m_dbTblName
            + " WHERE Id = (?);" << id
            >> [&](string name, string odate, double irate, string pday)
                {
                    this->m_pAccount->open(name, irate, pday, odate);
                };
}
