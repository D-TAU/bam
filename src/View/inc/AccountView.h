
#ifndef ACCOUNTVIEW_H_
#define ACCOUNTVIEW_H_

#include "View.h"
#include <string>

class IAccountViewListener;

class AccountView
	: public View
{
public:
	enum ButtonId
	{
		WithdrawButtonId,
		DepositDuttonId
	};

public:
	AccountView(Evas_Object *parent);
	void setListener(IAccountViewListener *listener);
	void setCurrentBalance(const std::string &str);
	std::string getInputMoney() const;

private:
	virtual ~AccountView();
	void create(Evas_Object *parent);
	Evas_Object *createCurrentBalance(Evas_Object *parent);
	Evas_Object *createEntry(Evas_Object *parent);
	Evas_Object *createButtons(Evas_Object *parent);

	void onWithdrawButtonClicked(Evas_Object *btn, void *eventInfo);
	void onDepositButtonClicked(Evas_Object *btn, void *eventInfo);

private:
	Evas_Object *m_pMoneyEntry;
	Evas_Object *m_pCurrrentBalanceLabel;;
	IAccountViewListener *m_pListener;
};

class IAccountViewListener
{
public:
	virtual ~IAccountViewListener() {}
	virtual void onButtonClicked(AccountView &view, AccountView::ButtonId buttonId) {};
};

#endif /* ACCOUNTVIEW_H_ */
