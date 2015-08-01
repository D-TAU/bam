#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
    enum OpStatus
    {
    	FAILURE,
    	SUCCESS
    };

public:
    Account(double ibal = 0, double irate = 0);
    virtual ~Account();

    virtual OpStatus withdraw(double amount);
    virtual OpStatus deposit(double amount);

    virtual double getBalance() const;
    virtual double getInterestsRate() const;
private:
    double m_Balance;
    double m_InterestsRate; // percent per year
};

#endif // ACCOUNT_H
