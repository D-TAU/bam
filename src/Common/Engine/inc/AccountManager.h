#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <string>
#include <vector>
#include <memory>

class Date;
class Account;
namespace sqlite{
    class database;
}

typedef std::vector<std::unique_ptr<Account> > AccountsList;

class AccountManager
{
public:

    AccountManager();
    virtual ~AccountManager();

    //returns an id of newly created account
    Account * addAccount(const std::string& name, double irate,
                                const std::string & pday, const Date& odate, double ibalance);
    const AccountsList& getAccountsList() const;
private:
    void createAccountsTable();
    void populateAccountsList();
    //returns an id of newly created account or 0 if account with such name exists
    int insertAccount(const std::string& name, double irate,
                                const std::string & pday, const Date& odate);
private:
    sqlite::database * m_db;
    std::string m_dbTblName;
    AccountsList m_accountsList;
};

#endif // ACCOUNTMANAGER_H
