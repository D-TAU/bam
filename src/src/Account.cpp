#include "Account.h"

Account::Account(double ibal)
{
    /*setup initial account balance*/
    m_balance = ibal;
}

Account::~Account()
{
    //dtor
}

Account::OpStatus Account::withdraw(double amount)
{
    /*do not withdraw more than you have*/
    if(amount < m_balance)
    {
        m_balance -= amount;
        return SUCCESS;
    }
    else
        return FAILURE;
}

Account::OpStatus Account::deposit(double amount)
{
    m_balance += amount;
    return SUCCESS;
}
