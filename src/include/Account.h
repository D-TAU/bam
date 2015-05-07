#ifndef ACCOUNT_H
#define ACCOUNT_H


class Account
{
public:
    Account(double ibal);
    virtual ~Account();

    enum OpStatus {FAILURE, SUCCESS};
    virtual OpStatus withdraw(double amount);
    virtual OpStatus deposit(double amount);
protected:
    double m_balance;
};

#endif // ACCOUNT_H
