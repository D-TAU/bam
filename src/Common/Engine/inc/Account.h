#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <sqlite_modern_cpp.h>
#include <Date.h>

class Account
{
public:
    Account(sqlite::database *db, const std::string& name,
            double interestsAnnualRate, const std::string& interestPayoffDay,
            const Date& openDate, double initialBalance = 0);
    virtual ~Account();

    bool withdraw(const Date& date, double amount);
    bool deposit(const Date&, double amount);
    bool deleteTransaction(int id);

    double getPaidInterests() const;
    double getAccruedInterests() const;
    double getBalanceOn(const Date& date) const;
    double getBalance() const;
    Date getInterestsPayoffDateAfter(const Date& date) const;
    const std::string& getName() const;
    const std::string& getInterestsPayoffDay() const;
    double getInterestsRate() const;
private:
    sqlite::database *m_db;
    std::string m_name;
    double m_interestsRate;
    std::string m_interestsPayoffDay;
    Date m_openDate;

    Date getLastInterestsPayoffDateBefore(const Date& date) const;

    std::string m_BalancesTblName;
    std::string m_InterestsTblName;
    std::string m_TransactionsTblName;

    /*checks whether account already exists in the database*/
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
};

#endif // ACCOUNT_H
