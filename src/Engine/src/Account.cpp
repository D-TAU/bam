#include "Account.h"

Account::Account(double ibal)
	: m_Balance(ibal)
{
}

Account::~Account()
{
    //dtor
}

Account::OpStatus Account::withdraw(double amount)
{
    /*do not withdraw more than you have*/
    if(amount < m_Balance)
    {
    	m_Balance -= amount;
        return SUCCESS;
    }
    else
        return FAILURE;
}

Account::OpStatus Account::deposit(double amount)
{
	m_Balance += amount;
    return SUCCESS;
}

double Account::getBalance() const
{
	return m_Balance;
}
