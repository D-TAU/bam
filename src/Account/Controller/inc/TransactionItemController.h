#ifndef TRANSACTIONITEMCONTROLLER_H_
#define TRANSACTIONITEMCONTROLLER_H_

#include "TransactionViewItem.h"
#include "Transaction.h"

class TransactionItemController
	: public TransactionViewItem
{
public:
	TransactionItemController(Genlist &genlist, const Transaction &transaction);

	Transaction &getTransaction() const;

private:
	virtual ~TransactionItemController();

private:
	 const Transaction &m_Transaction;
};

#endif /* TRANSACTIONITEMCONTROLLER_H_ */
