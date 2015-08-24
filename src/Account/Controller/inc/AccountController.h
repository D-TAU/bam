#ifndef ACCOUNTCONTROLLER_H_
#define ACCOUNTCONTROLLER_H_

#include "AccountView.h"
#include "Account.h"
#include "NaviFrameItem.h"
#include "NaviFrame.h"

class Application;

class AccountController
	: public NaviFrameItem
	, private AccountViewListener
{
public:
	AccountController(Application &app, sqlite::database *db, NaviFrame &naviFrame);
	Evas_Object *getEo() const;

private:
	~AccountController();
	void updateView();
	double getInputMoney() const;

private:
	// NaviFrameItem:
	virtual void onFrameCreated(NaviFrameItem &item);

	// AccountViewListener:
	virtual void onButtonClicked(AccountView &view, AccountView::ButtonId buttonId);

	// Hardware buttons:
	void onHwMoreButtonPressed(Evas_Object *obj, void *eventInfo);

private:
	Application &m_App;
	NaviFrame &m_NaviFrame;
	Account m_Account;
	AccountView *m_pAccountView;
};

#endif /* ACCOUNTCONTROLLER_H_ */
