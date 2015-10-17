/*
 * TransactionViewItem.h
 *
 *  Created on: Oct 11, 2015
 *      Author: D-TAU
 */

#ifndef TRANSACTIONVIEWITEM_H_
#define TRANSACTIONVIEWITEM_H_

#include "GenlistItem.h"

class TransactionViewItem
	: public GenlistItem
{
public:
	TransactionViewItem(Genlist &parent);

protected:
	virtual std::string getDateTime() = 0;

	virtual ~TransactionViewItem();
};

#endif /* TRANSACTIONVIEWITEM_H_ */
