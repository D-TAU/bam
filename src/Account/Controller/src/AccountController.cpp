
#include "Bam.h"
#include "AccountController.h"
#include "AccountManager.h"
#include "TransactionController.h"
#include "CallbackAssist.h"
#include "Application.h"
#include "TransactionItem.h"


#include <efl_extension.h>
#include <sstream>
#include <string>
#include <iomanip>

AccountController::AccountController(Application &app,  NaviFrame &naviFrame)
	: NaviFrameItem()
	, m_App(app)
	, m_NaviFrame(naviFrame)
{
	app.getEngine().setCurrentAccount(0);//FIXME this should be done in another place
	m_Account = app.getEngine().getCurrentAccount();

	m_pAccountView = new AccountView(m_NaviFrame);
	m_pAccountView->setListener(this);
	m_pAccountView->show();

	eext_object_event_callback_add(*m_pAccountView, EEXT_CALLBACK_MORE,
			EEXT_EVENT_CB(AccountController, onHwMoreButtonPressed), this);
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

	ss.precision(2);
	ss.setf(std::ios::fixed);

	ss << m_Account->getBalance();
	m_pAccountView->setCurrentBalance(ss.str());

	ss.str("");
	ss << m_Account->getOpenDate().toStrFmt();
	m_pAccountView->setOpenDate(ss.str());

	ss.str("");
	ss << m_Account->getInterestsRate();
	m_pAccountView->setInterestsRate(ss.str());

	ss.str("");
	ss << m_Account->getPaidInterests();
	m_pAccountView->setPaidInterests(ss.str());

	ss.str("");
	ss << m_Account->getAccruedInterests();
	m_pAccountView->setAccruedInterests(ss.str());

	TransactionsList tlist = m_Account->getTransactions();
	m_pAccountView->setTransactionsList(tlist);
}

void AccountController::onButtonClicked(AccountView &view, AccountView::ButtonId buttonId)
{
	BAM_LOG("OnButtonClicked: id = %i", buttonId);

	switch(buttonId)
	{

		case AccountView::TransactButtonId:
		{
			TransactionController * frame = new TransactionController(m_App, m_NaviFrame, *m_Account);
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

