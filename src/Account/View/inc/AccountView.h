
#ifndef ACCOUNTVIEW_H_
#define ACCOUNTVIEW_H_

#include "View.h"
#include <string>


class AccountViewListener;

class AccountView
	: public View
{
public:
	enum ButtonId
	{
		WithdrawButtonId,
		DepositButtonId,
		TransactButtonId
	};

public:
	AccountView(Evas_Object *parent);
	void setCurrentBalance(const std::string &str);
	void setInterestsRate(const std::string &str);
	std::string getInputMoney() const;
	void setListener(AccountViewListener * l);

protected:
	virtual ~AccountView();

private:
	void create(Evas_Object *parent);
	Evas_Object *createCurrentBalance(Evas_Object *parent);
	Evas_Object *createInterestsRate(Evas_Object *parent);
	Evas_Object *createTransactionButton(Evas_Object *parent);

	void onTransactButtonClicked(Evas_Object *btn, void *eventInfo);

	void onOverviewTabSelected(Evas_Object *tab, void *eventInfo);
	void onTransactTabSelected(Evas_Object *tab, void *eventInfo);

private:
	Evas_Object *m_pCurrentBalanceLabel;
	Evas_Object *m_pInterestsRateLabel;
	Evas_Object *m_pTabContent;
	AccountViewListener *m_pListener;
};

class AccountViewListener
{
public:
	virtual ~AccountViewListener() {}
	virtual void onButtonClicked(AccountView &view, AccountView::ButtonId buttonId) {};
};


#endif /* ACCOUNTVIEW_H_ */
