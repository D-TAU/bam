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
    Account(double ibal = 0);
    virtual ~Account();

    virtual OpStatus withdraw(double amount);
    virtual OpStatus deposit(double amount);

private:
    double m_Balance;
};

#endif // ACCOUNT_H
