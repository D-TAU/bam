/*
 * TransactionItemController.cpp
 *
 *  Created on: Oct 11, 2015
 *      Author: D-TAU
 */

#include "TransactionItemController.h"

TransactionItemController::TransactionItemController(Genlist &genlist, const Transaction &transaction)
	: TransactionViewItem(genlist)
	, m_Transaction(transaction)
{
}

TransactionItemController::~TransactionItemController()
{
}

Transaction &TransactionItemController::getTransaction() const
{
	return const_cast<Transaction&>(m_Transaction);
}

