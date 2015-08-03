
#include "Bam.h"
#include "AccountController.h"
#include "CallbackAssist.h"
#include "Application.h"

#include <efl_extension.h>
#include <sstream>
#include <string>

AccountController::AccountController(Application &app, sqlite::database * db,
		Evas_Object *parent)
	: AccountView(parent)
	, m_App(app)
	//FIXME account initialization
	, m_Account(db, "MyName", 9, "25", Date("2015-08-03"))
{
	eext_object_event_callback_add(getEo(), EEXT_CALLBACK_BACK, EEXT_EVET_CB(AccountController, onHwBackButtonPressed), this);
	eext_object_event_callback_add(getEo(), EEXT_CALLBACK_MORE, EEXT_EVET_CB(AccountController, onHwMoreButtonPressed), this);
	updateView();
}

AccountController::~AccountController()
{
	BAM_LOG("AccountController destroy");
}

Evas_Object *AccountController::getEo() const
{
	return AccountView::getEo();
}

void AccountController::updateView()
{
	std::ostringstream ss;

	ss << m_Account.getBalance();
	setCurrentBalance(ss.str());

	ss.str("");
	ss << m_Account.getInterestsRate();
		setInterestsRate(ss.str());
}

double AccountController::getInputMoney() const
{
	double money = 0.0;
	std::string str = AccountView::getInputMoney();
	if(!str.empty())
		money = std::stod(str);
	return money;
}

void AccountController::onButtonClicked(AccountView &view, AccountView::ButtonId buttonId)
{
	BAM_LOG("OnButtonClicked: id = %i", buttonId);

	switch(buttonId)
	{
		case AccountView::DepositDuttonId:
		{
			//FIXME boilerplate with date
			m_Account.deposit(Date::today(), getInputMoney());
			updateView();
			break;
		}

		case AccountView::WithdrawButtonId:
		{
			//FIXME boilerplate with date
			m_Account.withdraw(Date::today(), getInputMoney());
			updateView();
			break;
		}

		default:
			BAM_LOG_ERROR("Unknown account button id");
			break;
	}
}

void AccountController::onHwBackButtonPressed(Evas_Object *obj, void *eventInfo)
{
	BAM_LOG("OnHwBackButtonPressed");
	m_App.exit();
}

void AccountController::onHwMoreButtonPressed(Evas_Object *obj, void *eventInfo)
{
	BAM_LOG("OnHwMoreButtonPressed");
}

