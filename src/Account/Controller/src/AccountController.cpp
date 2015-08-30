
#include "Bam.h"
#include "AccountController.h"
#include "TransactionController.h"
#include "CallbackAssist.h"
#include "Application.h"

#include <efl_extension.h>
#include <sstream>
#include <string>

AccountController::AccountController(Application &app, sqlite::database * db,  NaviFrame &naviFrame)
	: NaviFrameItem()
	, m_App(app)
	, m_NaviFrame(naviFrame)
	, m_Account(db, "MyName", 9, "25", Date("2015-08-03")) //FIXME account initialization

{
	m_pAccountView = new AccountView(m_NaviFrame);
	m_pAccountView->setListener(this);
	m_pAccountView->show();

	eext_object_event_callback_add(*m_pAccountView, EEXT_CALLBACK_MORE, EEXT_EVENT_CB(AccountController, onHwMoreButtonPressed), this);
	updateView();
}

AccountController::~AccountController()
{
	BAM_LOG("AccountController destroy");
}

void AccountController::onFrameCreated(NaviFrameItem &item)
{
	getNaviBar().setTitle("Account");
	setContent(*m_pAccountView);
}

Evas_Object *AccountController::getEo() const
{
	return *m_pAccountView;
}

void AccountController::updateView()
{
	std::ostringstream ss;

	ss << m_Account.getBalance();
	m_pAccountView->setCurrentBalance(ss.str());

	ss.str("");
	ss << m_Account.getInterestsRate();
	m_pAccountView->setInterestsRate(ss.str());
}

double AccountController::getInputMoney() const
{
	double money = 0.0;
	std::string str = m_pAccountView->getInputMoney();
	if(!str.empty())
		money = std::stod(str);
	return money;
}

void AccountController::onButtonClicked(AccountView &view, AccountView::ButtonId buttonId)
{
	BAM_LOG("OnButtonClicked: id = %i", buttonId);

	switch(buttonId)
	{
		case AccountView::DepositButtonId:
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

		case AccountView::TransactButtonId:
		{
			TransactionController * frame = new TransactionController(m_App, m_NaviFrame);
			m_NaviFrame.push(frame);
			break;
		}

		default:
			BAM_LOG_ERROR("Unknown account button id");
			break;
	}
}

void AccountController::onHwMoreButtonPressed(Evas_Object *obj, void *eventInfo)
{
	BAM_LOG("OnHwMoreButtonPressed");
}

