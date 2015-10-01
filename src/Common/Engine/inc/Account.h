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
	friend class AccountManager;

    Account(sqlite::database& db);
    virtual ~Account();
            
    void addListener(IAccountListener &l);
    void removeListener(IAccountListener &l);


    bool withdraw(const Date& date, double amount);
    bool deposit(const Date&, double amount);
    bool deleteTransaction(int id);
    /*returns all transactions sorted by date*/
    TransactionsList getTransactions() const;

    Date getOpenDate() const; 					/*date when account was created (open)*/
    double getPaidInterests() const;			/*how much interests were already paid since account was created*/
    double getAccruedInterests() const;			/*how much interests has been accrued (but not paid)
     	 	 	 	 	 	 	 	 	  	  	  since last interests payoff*/
    double getBalanceOn(const Date& date) const;/*what was account balance on 'date'*/
    double getBalance() const;					/*what is current balance ('date' = today)*/
    Date getInterestsPayoffDateAfter(
    					const Date& date) const;/*when will be the next interests payoff after 'date'*/
    const std::string& getName() const;			/*account name*/
    const std::string&
    			getInterestsPayoffDay() const;	/*at which day of a month interests are paid*/
    double getInterestsRate() const;			/*annual interests rate (percentage)*/
    int getId() const;
    void setId(unsigned int id);
private:
    typedef std::vector<IAccountListener*> AccountListenerList;
    
    sqlite::database& m_db;
    std::string m_name;
    /*annual interests rate*/
    double m_interestsRate;
    std::string m_interestsPayoffDay;
    Date m_openDate;
    int m_id;							/*account id, set up by an account manager*/

    std::string m_BalancesTblName;
    std::string m_InterestsTblName;
    std::string m_TransactionsTblName;
    AccountListenerList m_AccountListenerList;

    bool open(const std::string& name,
                double interestsAnnualRate,
                const std::string& interestPayoffDay,
                const Date& openDate);
    bool create(const std::string& name,
                double interestsAnnualRate,
                const std::string& interestPayoffDay,
                const Date& openDate,
                double initialBalance = 0);

    Date getLastInterestsPayoffDateBefore(const Date& date) const;
    /*checks whether Account tables already exist in the database*/
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
