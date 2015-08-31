/*
 * TransactionController.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: vifactor
 */

#include "Bam.h"
#include "TransactionController.h"

TransactionController::TransactionController(Application &app, NaviFrame &naviframe)
	: NaviFrameItem()
	, m_App(app)
	, m_NaviFrame(naviframe)
{
	m_pTransactionView = new TransactionView(m_NaviFrame);
	m_pTransactionView->setListener(this);
	m_pTransactionView->show();

//	eext_object_event_callback_add(*m_pTransactionView, EEXT_CALLBACK_MORE,
//			EEXT_EVET_CB(TransactionController, onHwMoreButtonPressed), this);
//	updateView();
}

TransactionController::~TransactionController()
{
	// TODO Auto-generated destructor stub
}

void TransactionController::onFrameCreated(NaviFrameItem &item)
{
	getNaviBar().setTitle("Transaction");
	setContent(*m_pTransactionView);
}

double TransactionController::getAmountInput() const
{
	double money = 0.0;
	std::string str = m_pTransactionView->getAmountInput();
	if(!str.empty())
		money = std::stod(str);
	return money;
}

void TransactionController::onButtonClicked(TransactionView &view, TransactionView::ButtonId buttonId)
{
	BAM_LOG("OnButtonClicked: id = %i", buttonId);

	switch(buttonId)
	{
		case TransactionView::DepositButtonId:
		{
			//FIXME boilerplate with date
			//m_Account.deposit(Date::today(), getInputMoney());
			//updateView();
			m_NaviFrame.pop();
			break;
		}

		case TransactionView::WithdrawButtonId:
		{
			//FIXME boilerplate with date
			//m_Account.withdraw(Date::today(), getInputMoney());
			//updateView();
			m_NaviFrame.pop();
			break;
		}

		default:
			BAM_LOG_ERROR("Unknown account button id");
			break;
	}
}
