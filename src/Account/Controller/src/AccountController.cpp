
#include "Bam.h"
#include "AccountController.h"
#include "CallbackAssist.h"
#include "Application.h"

#include <efl_extension.h>
#include <sstream>
#include <string>

AccountController::AccountController(Application &app, Evas_Object *parent)
	: AccountView(parent)
	, m_App(app)
	, m_Account(500)
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
			m_Account.deposit(getInputMoney());
			updateView();
			break;
		}

		case AccountView::WithdrawButtonId:
		{
			m_Account.withdraw(getInputMoney());
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

