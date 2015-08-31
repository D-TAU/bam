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
#include "Date.h"

class Application;

class TransactionController
		: public NaviFrameItem
		, private TransactionViewListener
{
public:
	TransactionController(Application &app, NaviFrame &naviframe);

private:
	// Destructor
	virtual ~TransactionController();

	// NaviFrameItem inherited method
	virtual void onFrameCreated(NaviFrameItem &item);

	// AccountViewListener:
	virtual void onButtonClicked(TransactionView &view, TransactionView::ButtonId buttonId);

	// Hardware buttons:
	void onHwMoreButtonPressed(Evas_Object *obj, void *eventInfo);

private:
	double getAmountInput() const;
	Date getDateInput() const;

private:
	Application &m_App;
	NaviFrame &m_NaviFrame;
	TransactionView *m_pTransactionView;
};

#endif /* TRANSACTIONCONTROLLER_H_ */
