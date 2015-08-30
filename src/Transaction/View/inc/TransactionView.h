/*
 * TransactionView.h
 *
 *  Created on: Aug 30, 2015
 *      Author: vifactor
 */

#ifndef TRANSACTIONVIEW_H_
#define TRANSACTIONVIEW_H_

#include "View.h"

class TransactionView: public View
{
public:
	TransactionView(Evas_Object *parent);
	virtual ~TransactionView();

private:
	void create(Evas_Object *parent);

	Evas_Object *createEntry(Evas_Object *parent);
	Evas_Object *createCalendar(Evas_Object *parent);
	Evas_Object *createButtons(Evas_Object *parent);

private:
	Evas_Object *m_pMoneyEntry;
	Evas_Object *m_pCalendar;
};

#endif /* TRANSACTIONVIEW_H_ */
