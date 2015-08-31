/*
 * TransactionController.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: vifactor
 */

#include "TransactionController.h"

TransactionController::TransactionController(Application &app, NaviFrame &naviframe)
	: NaviFrameItem()
	, m_App(app)
	, m_NaviFrame(naviframe)
{
	m_pTransactionView = new TransactionView(m_NaviFrame);
	//m_pTransactionView->setListener(this);
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
