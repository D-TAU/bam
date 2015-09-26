#ifndef ACCOUNTHANDLE_H
#define ACCOUNTHANDLE_H

#include <string>
#include <vector>
#include <sqlite_modern_cpp.h>

#include "Account.h"
#include "Transaction.h"
#include "Date.h"

namespace sqlite
{
    class database;
}
class IAccountListener;


class Account
{
public:
    Account(sqlite::database& db);
    virtual ~Account();

    bool create(const std::string& name,
            double interestsAnnualRate,
            const std::string& interestPayoffDay,
            const Date& openDate,
            double initialBalance = 0);
    bool open(const std::string& name,
            double interestsAnnualRate,
            const std::string& interestPayoffDay,
            const Date& openDate);
            
    void addListener(IAccountListener &l);
    void removeListener(IAccountListener &l);


    bool withdraw(const Date& date, double amount);
    bool deposit(const Date&, double amount);
    bool deleteTransaction(int id);
    /*returns all transactions sorted by date*/
    TransactionsList getTransactions() const;

    Date getOpenDate() const;
    double getPaidInterests() const;
    double getAccruedInterests() const;
    double getBalanceOn(const Date& date) const;
    double getBalance() const;
    Date getInterestsPayoffDateAfter(const Date& date) const;
    const std::string& getName() const;
    const std::string& getInterestsPayoffDay() const;
    double getInterestsRate() const;
private:
    typedef std::vector<IAccountListener*> AccountListenerList;
    
    sqlite::database& m_db;
    std::string m_name;
    double m_interestsRate;
    std::string m_interestsPayoffDay;
    Date m_openDate;

    Date getLastInterestsPayoffDateBefore(const Date& date) const;

    std::string m_BalancesTblName;
    std::string m_InterestsTblName;
    std::string m_TransactionsTblName;
    AccountListenerList m_AccountListenerList;

    /*checks whether AccountHandle already exists in the database*/
    bool exists() const;

    void createTables();
    void createBalancesTable();
    void createTransactionsTable();
    void createInterestsTable();

    void createTriggers();
    void createOnInterestsInsertTrigger();
    void createOnTransactionInsertTrigger();
    void createOnTransactionDeleteTrigger();
    void createOnInterestsUpdateTrigger();

    void updateInterestsTable();
    void updateInterestsTableAfter(const Date& date);
    void upsertInterests(const Date& date, double amount);
    
    template<class...Args>
    void notifyListeners(void (IAccountListener::*method)(Args...args), Args&&...args);
};

class IAccountListener
{
public:
    virtual ~IAccountListener() {}
    virtual void onTransaction() {}; // TODO: Transaction args
};
#endif // ACCOUNTHANDLE_H
