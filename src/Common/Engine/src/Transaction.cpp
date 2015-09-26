/*
 * TransactionItem.cpp
 *
 *  Created on: Sep 26, 2015
 *      Author: vifactor
 */

#include "Transaction.h"

Transaction::Transaction()
	: m_Amount()
	, m_Date()
	, m_Id()
	, m_Type()
{
	// TODO Auto-generated constructor stub
}

Transaction::~Transaction()
{
	// TODO Auto-generated destructor stub
}

double Transaction::getAmount() const
{
	return m_Amount;
}

const Date & Transaction::getDate() const
{
	return m_Date;
}

int Transaction::getId() const
{
	return m_Id;
}

Transaction::Type Transaction::getType() const
{
	return m_Type;
}
