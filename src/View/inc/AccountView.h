
#ifndef ACCOUNTVIEW_H_
#define ACCOUNTVIEW_H_

#include "View.h"
#include <string>

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
	void setCurrentBalance(const std::string &str);
	std::string getInputMoney() const;

protected:
	virtual void onButtonClicked(AccountView &view, AccountView::ButtonId buttonId) {};
	virtual ~AccountView();

private:
	void create(Evas_Object *parent);
	Evas_Object *createCurrentBalance(Evas_Object *parent);
	Evas_Object *createEntry(Evas_Object *parent);
	Evas_Object *createButtons(Evas_Object *parent);

	void onWithdrawButtonClicked(Evas_Object *btn, void *eventInfo);
	void onDepositButtonClicked(Evas_Object *btn, void *eventInfo);

private:
	Evas_Object *m_pMoneyEntry;
	Evas_Object *m_pCurrrentBalanceLabel;;
};


#endif /* ACCOUNTVIEW_H_ */
