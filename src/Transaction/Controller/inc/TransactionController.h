/*
 * TransactionController.h
 *
 *  Created on: Aug 30, 2015
 *      Author: vifactor
 */

#ifndef TRANSACTIONCONTROLLER_H_
#define TRANSACTIONCONTROLLER_H_

#include "TransactionView.h"
#include "NaviFrameItem.h"
#include "NaviFrame.h"

class Application;

class TransactionController
		: public NaviFrameItem
{
public:
	TransactionController(Application &app, NaviFrame &naviframe);
	virtual ~TransactionController();

private:
	Application &m_App;
	NaviFrame &m_NaviFrame;
	TransactionView *m_pTransactionView;
};

#endif /* TRANSACTIONCONTROLLER_H_ */
