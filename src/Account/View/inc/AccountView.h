
#ifndef ACCOUNTVIEW_H_
#define ACCOUNTVIEW_H_

#include "View.h"
#include <string>
#include <vector>


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
	void setPaidInterests(const std::string &str);
	void setAccruedInterests(const std::string &str);
	void setOpenDate(const std::string &str);
	void setTransactionsList(const std::vector<std::string>& tlist);
	std::string getInputMoney() const;
	void setListener(AccountViewListener * l);

protected:
	virtual ~AccountView();

private:
	void create(Evas_Object *parent);
	Evas_Object *createCurrentBalance(Evas_Object *parent);
	Evas_Object *createInterestsRate(Evas_Object *parent);
	Evas_Object *createPaidInterests(Evas_Object *parent);
	Evas_Object *createAccrInterests(Evas_Object *parent);
	Evas_Object *createOpenDate(Evas_Object *parent);

	Evas_Object *createTransactionButton(Evas_Object *parent);
	Evas_Object *createOverviewTabContent(Evas_Object *parent);
	Evas_Object *createTransactionsTabContent(Evas_Object *parent);

	void onTransactButtonClicked(Evas_Object *btn, void *eventInfo);
	void onOverviewTabSelected(Evas_Object *tab, void *eventInfo);
	void onTransactTabSelected(Evas_Object *tab, void *eventInfo);

private:
	enum TabContent {tcOverview, tcTransactions};
	TabContent m_currentTabContent;

	Evas_Object *m_pCurrentBalanceLabel;
	Evas_Object *m_pInterestsRateLabel;
	Evas_Object *m_pOpenDateLabel;
	Evas_Object *m_pAccrInterestsLabel;
	Evas_Object *m_pPaidInterestsLabel;
	Evas_Object *m_pOverviewTabContent, *m_pTransactionsTabContent;
	Evas_Object *m_pTransactionBtn;
	AccountViewListener *m_pListener;
};

class AccountViewListener
{
public:
	virtual ~AccountViewListener() {}
	virtual void onButtonClicked(AccountView &view, AccountView::ButtonId buttonId) {};
};


#endif /* ACCOUNTVIEW_H_ */
