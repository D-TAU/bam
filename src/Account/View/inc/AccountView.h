
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
	Evas_Object *createEntry(Evas_Object *parent);
	Evas_Object *createButtons(Evas_Object *parent);
	Evas_Object *createTransactionButton(Evas_Object *parent);

	// TODO: delete this shit
	Evas_Object *createTransactionView(Elm_Object_Item *parent);

	void onWithdrawButtonClicked(Evas_Object *btn, void *eventInfo);
	void onDepositButtonClicked(Evas_Object *btn, void *eventInfo);
	void onTransactButtonClicked(Evas_Object *btn, void *eventInfo);

private:
	Evas_Object *m_pMoneyEntry;
	Evas_Object *m_pCurrentBalanceLabel;
	Evas_Object *m_pInterestsRateLabel;
	AccountViewListener *m_pListener;
};

class AccountViewListener
{
public:
	virtual ~AccountViewListener() {}
	virtual void onButtonClicked(AccountView &view, AccountView::ButtonId buttonId) {};
};


#endif /* ACCOUNTVIEW_H_ */
