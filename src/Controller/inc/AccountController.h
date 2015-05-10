#ifndef ACCOUNTCONTROLLER_H_
#define ACCOUNTCONTROLLER_H_

#include "AccountView.h"
#include "Account.h"

class Application;

class AccountController
	: private AccountView
{
public:
	AccountController(Application &app, Evas_Object *parent);
	Evas_Object *getEo() const;

private:
	~AccountController();
	void updateView();
	double getInputMoney() const;

private:

	// AccountView
	virtual void onButtonClicked(AccountView &view, AccountView::ButtonId buttonId);

	// Hardware buttons:
	void onHwBackButtonPressed(Evas_Object *obj, void *eventInfo);
	void onHwMoreButtonPressed(Evas_Object *obj, void *eventInfo);


private:
	Application &m_App;
	Account m_Account;
};

#endif /* ACCOUNTCONTROLLER_H_ */
