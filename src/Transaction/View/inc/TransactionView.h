/*
 * TransactionView.h
 *
 *  Created on: Aug 30, 2015
 *      Author: vifactor
 */

#ifndef TRANSACTIONVIEW_H_
#define TRANSACTIONVIEW_H_

#include "View.h"
#include <string>

class TransactionViewListener;

class TransactionView
	: public View
{
public:
	enum ButtonId
	{
		WithdrawButtonId,
		DepositButtonId
	};
public:
	TransactionView(Evas_Object *parent);

	std::string getAmountInput() const;
	time_t getDateInput() const;

	void setListener(TransactionViewListener * l);

protected:
	virtual ~TransactionView();

private:
	void create(Evas_Object *parent);

	Evas_Object *createEntry(Evas_Object *parent);
	Evas_Object *createCalendar(Evas_Object *parent);
	Evas_Object *createButtons(Evas_Object *parent);

	void onWithdrawButtonClicked(Evas_Object *btn, void *eventInfo);
	void onDepositButtonClicked(Evas_Object *btn, void *eventInfo);
private:
	Evas_Object *m_pAmountEntry;
	Evas_Object *m_pDateEntry;

	TransactionViewListener *m_pListener;
};


class TransactionViewListener
{
public:
	virtual ~TransactionViewListener() {}
	virtual void onButtonClicked(TransactionView &view, TransactionView::ButtonId buttonId) {};
};

#endif /* TRANSACTIONVIEW_H_ */
