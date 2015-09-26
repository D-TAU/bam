/*
 * TransactionItem.h
 *
 *  Created on: Sep 26, 2015
 *      Author: vifactor
 */

#ifndef TRANSACTIONITEM_H_
#define TRANSACTIONITEM_H_

#include <string>
#include <Date.h>

class TransactionItem
{
public:
	TransactionItem();
	virtual ~TransactionItem();

	enum Type {ttUSER, ttINTERESTS};
	static std::string getTextForEnum( Type enumVal );

    double m_amount;
    Date m_date;
    int m_id;
    Type m_type;
};

#endif /* TRANSACTIONITEM_H_ */
