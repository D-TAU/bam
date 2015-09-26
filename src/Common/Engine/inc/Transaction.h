/*
 * TransactionItem.h
 *
 *  Created on: Sep 26, 2015
 *      Author: vifactor
 */

#ifndef TRANSACTIONITEM_H_
#define TRANSACTIONITEM_H_

#include <string>
#include <vector>

#include "Date.h"

class Transaction;
typedef std::vector<Transaction> TransactionsList;

class Transaction
{
	friend class Account;

public:
	enum Type
	{
		ttUSER,
		ttINTERESTS
	};

public:
	~Transaction();
	Transaction();

	double getAmount() const;
	const Date & getDate() const;
	int getId() const;
	Type getType() const;

private:
    double m_Amount;
    Date m_Date;
    int m_Id;
    Type m_Type;
};

#endif /* TRANSACTIONITEM_H_ */
