#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <string>
#include <map>

class Date;
class Account;
namespace sqlite{
    class database;
}

class AccountManager
{
public:
    struct AccountProps
    {
        AccountProps(const std::string& name):
            m_name(name)
                {}
        std::string m_name;
    };
    typedef std::map<int, AccountProps> AccountsMap;

    AccountManager();
    virtual ~AccountManager();

    void setCurrentAccount(int id);
    Account* getCurrentAccount();
    //returns an id of newly created account
    int createAccount(const std::string& name, double irate,
                                const std::string & pday, const Date& odate, double ibalance);
    const AccountsMap& getAccountsMap() const;
private:
    void createAccountsTable();
    void populateAccountsMap();
    void openAccount(int id);
    //returns an id of newly created account or 0 if account with such name exists
    int insertAccount(const std::string& name, double irate,
                                const std::string & pday, const Date& odate);
private:
    Account * m_pAccount;
    sqlite::database * m_db;
    std::string m_dbTblName;
    AccountsMap m_accountsMap;
};

#endif // ACCOUNTMANAGER_H
