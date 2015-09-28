#include "AccountManager.h"

#include "Account.h"

using namespace sqlite;
using namespace std;

AccountManager::AccountManager()
{
    m_db = new database(":memory:");// FIXME: change to file-based database

    //creates accounts table if it did not exist
    createAccountsTable();
    //populate accounts list
    populateAccountsList();
}

AccountManager::~AccountManager()
{
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

void AccountManager::populateAccountsList()
{
	(*m_db) << "SELECT Id, Name, OpenDate, InterestsRate, PayoffDay FROM " + m_dbTblName + ";"
	            >> [&](int id, string name, string odate, double irate, string pday)
	                {
						std::unique_ptr<Account> pAccount(new Account(*m_db));
						pAccount->setId(id);
						pAccount->open(name, irate, pday, odate);
						m_accountsList.push_back(std::move(pAccount));
	                };
}

const AccountsList& AccountManager::getAccountsList() const
{
    return m_accountsList;
}

Account * AccountManager::addAccount(const string& name, double irate,
                                const string & pday, const Date& odate, double ibalance)
{
    //try to insert account into the accounts table
    int id = insertAccount(name, irate, pday, odate);

    // check if account props were inserted into accounts table
    if(id > 0)
    {
    	std::unique_ptr<Account> pAccount(new Account(*m_db));
        //create and populate account's tables
        pAccount->create(name, irate, pday, odate, ibalance);
        pAccount->setId(id);
        //append accounts list
        m_accountsList.push_back(std::move(pAccount));

        return m_accountsList.back().get();
    }
    else
    	return nullptr;
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

    return ID;
}
