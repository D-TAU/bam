#include "AccountView.h"
#include "CallbackAssist.h"

#include <sstream>
#include <cstdlib>

namespace
{
	std::string applyFontSize(const std::string &str)
	{
		std::ostringstream ss;
		ss << "<font_size=36>" << str << "</font_size>";
		return ss.str();
	}
}

AccountView::AccountView(Evas_Object *parent)
	: m_pCurrentBalanceLabel(nullptr)
	, m_pInterestsRateLabel(nullptr)
	, m_pListener(nullptr)
{
	create(parent);
}

AccountView::~AccountView()
{
}

void AccountView::setListener(AccountViewListener * l)
{
	m_pListener = l;
}

void AccountView::create(Evas_Object *parent)
{
	Evas_Object *mainBox, *tb;
	mainBox = elm_box_add(parent);
	setEo(mainBox);
	evas_object_size_hint_weight_set(mainBox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(mainBox, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(mainBox);

	tb = elm_toolbar_add(parent);
	elm_toolbar_shrink_mode_set(tb, ELM_TOOLBAR_SHRINK_SCROLL);
	evas_object_size_hint_weight_set(tb, 0.0, 0.0);
	evas_object_size_hint_align_set(tb, EVAS_HINT_FILL, 0.0);
	evas_object_show(tb);

	elm_toolbar_item_append(tb, nullptr, "Overview", EVAS_SMART_CB(AccountView, onOverviewTabSelected), this);
	elm_toolbar_item_append(tb, nullptr, "Transactions", EVAS_SMART_CB(AccountView, onTransactTabSelected), this);

	m_pTransactionBtn = createTransactionButton(mainBox);
	m_pOverviewTabContent = createOverviewTabContent(mainBox);
	m_pTransactionsTabContent = createTransactionsTabContent(mainBox);

	/*initially overview tab is active*/
	m_currentTabContent = tcOverview;
	evas_object_show(m_pOverviewTabContent);
	elm_box_pack_end(mainBox, tb);
	elm_box_pack_end(mainBox, m_pOverviewTabContent);
	elm_box_pack_end(mainBox, m_pTransactionBtn);
}

Evas_Object *AccountView::createCurrentBalance(Evas_Object *parent)
{
	Evas_Object *box = elm_box_add(parent);
	evas_object_show(box);
	elm_box_homogeneous_set(box, false);
	elm_box_horizontal_set(box, true);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.5);

	Evas_Object *label = elm_label_add(box);
	elm_object_text_set(label, applyFontSize("Current balance: ").c_str());
	evas_object_show(label);

	m_pCurrentBalanceLabel = elm_label_add(box);
	evas_object_show(m_pCurrentBalanceLabel);

	elm_box_pack_end(box, label);
	elm_box_pack_end(box, m_pCurrentBalanceLabel);

	return box;
}

Evas_Object *AccountView::createInterestsRate(Evas_Object *parent)
{
	Evas_Object *box = elm_box_add(parent);
	evas_object_show(box);
	elm_box_homogeneous_set(box, false);
	elm_box_horizontal_set(box, true);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.5);

	Evas_Object *label = elm_label_add(box);
	elm_object_text_set(label, applyFontSize("Annual interests rate: ").c_str());
	evas_object_show(label);

	m_pInterestsRateLabel = elm_label_add(box);
	evas_object_show(m_pInterestsRateLabel);

	elm_box_pack_end(box, label);
	elm_box_pack_end(box, m_pInterestsRateLabel);

	return box;
}

Evas_Object *AccountView::createOpenDate(Evas_Object *parent)
{
	Evas_Object *box = elm_box_add(parent);
	evas_object_show(box);
	elm_box_homogeneous_set(box, false);
	elm_box_horizontal_set(box, true);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.5);

	Evas_Object *label = elm_label_add(box);
	elm_object_text_set(label, applyFontSize("Open date: ").c_str());
	evas_object_show(label);

	m_pOpenDateLabel = elm_label_add(box);
	evas_object_show(m_pOpenDateLabel);

	elm_box_pack_end(box, label);
	elm_box_pack_end(box, m_pOpenDateLabel);

	return box;
}

Evas_Object *AccountView::createPaidInterests(Evas_Object *parent)
{
	Evas_Object *box = elm_box_add(parent);
	evas_object_show(box);
	elm_box_homogeneous_set(box, false);
	elm_box_horizontal_set(box, true);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.5);

	Evas_Object *label = elm_label_add(box);
	elm_object_text_set(label, applyFontSize("Paid interests: ").c_str());
	evas_object_show(label);

	m_pPaidInterestsLabel = elm_label_add(box);
	evas_object_show(m_pPaidInterestsLabel);

	elm_box_pack_end(box, label);
	elm_box_pack_end(box, m_pPaidInterestsLabel);

	return box;
}

Evas_Object *AccountView::createAccrInterests(Evas_Object *parent)
{
	Evas_Object *box = elm_box_add(parent);
	evas_object_show(box);
	elm_box_homogeneous_set(box, false);
	elm_box_horizontal_set(box, true);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.5);

	Evas_Object *label = elm_label_add(box);
	elm_object_text_set(label, applyFontSize("Accrued interests: ").c_str());
	evas_object_show(label);

	m_pAccrInterestsLabel = elm_label_add(box);
	evas_object_show(m_pAccrInterestsLabel);

	elm_box_pack_end(box, label);
	elm_box_pack_end(box, m_pAccrInterestsLabel);

	return box;
}

Evas_Object *AccountView::createTransactionButton(Evas_Object *parent)
{
	Evas_Object *transact = elm_button_add(parent);
	evas_object_size_hint_align_set(transact, EVAS_HINT_FILL, 0.5);
	evas_object_size_hint_weight_set(transact, EVAS_HINT_EXPAND, 0.25);
	evas_object_show(transact);
	elm_object_text_set(transact, applyFontSize("Transaction").c_str());
	evas_object_smart_callback_add(transact, "clicked", EVAS_SMART_CB(AccountView, onTransactButtonClicked), this);

	return transact;
}

Evas_Object *AccountView::createOverviewTabContent(Evas_Object *parent)
{
	Evas_Object * contentBox = elm_box_add(parent);
	evas_object_size_hint_weight_set(contentBox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(contentBox, EVAS_HINT_FILL, EVAS_HINT_FILL);

	Evas_Object *openDate = createOpenDate(contentBox);
	Evas_Object *balance = createCurrentBalance(contentBox);
	Evas_Object *interestsRate = createInterestsRate(contentBox);
	Evas_Object *paidInterests = createPaidInterests(contentBox);
	Evas_Object *accrInterests = createAccrInterests(contentBox);

	elm_box_pack_end(contentBox, openDate);
	elm_box_pack_end(contentBox, balance);
	elm_box_pack_end(contentBox, interestsRate);
	elm_box_pack_end(contentBox, paidInterests);
	elm_box_pack_end(contentBox, accrInterests);

	return contentBox;
}

Evas_Object *AccountView::createTransactionsTabContent(Evas_Object *parent)
{
	Evas_Object *list = elm_list_add(parent);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);

	return list;
}

void AccountView::setCurrentBalance(const std::string &str)
{
	std::ostringstream ss;
	ss << "<color=#72ea79><b>" << str << "</b></color>";
	elm_object_text_set(m_pCurrentBalanceLabel, applyFontSize(ss.str()).c_str());
}

void AccountView::setInterestsRate(const std::string &str)
{
	std::ostringstream ss;
	ss << "<color=#72ea79><b>" << str << "% </b></color>";
	elm_object_text_set(m_pInterestsRateLabel, applyFontSize(ss.str()).c_str());
}

void AccountView::setAccruedInterests(const std::string &str)
{
	std::ostringstream ss;
	ss << "<color=#72ea79><b>" << str << "</b></color>";
	elm_object_text_set(m_pAccrInterestsLabel, applyFontSize(ss.str()).c_str());
}

void AccountView::setPaidInterests(const std::string &str)
{
	std::ostringstream ss;
	ss << "<color=#72ea79><b>" << str << "</b></color>";
	elm_object_text_set(m_pPaidInterestsLabel, applyFontSize(ss.str()).c_str());
}

void AccountView::setOpenDate(const std::string &str)
{
	std::ostringstream ss;
	ss << "<color=#72ea79><b>" << str << "</b></color>";
	elm_object_text_set(m_pOpenDateLabel, applyFontSize(ss.str()).c_str());
}

void AccountView::setTransactionsList(const std::vector<std::string>& tlist)
{
	/*clear list from previously added items: prevent repeating*/
	elm_list_clear(m_pTransactionsTabContent);
	for(size_t i = 0; i < tlist.size(); ++i)
		elm_list_item_append(m_pTransactionsTabContent, tlist[i].c_str(), nullptr, nullptr, nullptr, nullptr);

	elm_list_go(m_pTransactionsTabContent);
	evas_object_show(m_pTransactionsTabContent);
}

void AccountView::onTransactButtonClicked(Evas_Object *btn, void *eventInfo)
{
	if(m_pListener)
		m_pListener->onButtonClicked(*this, TransactButtonId);
}

void AccountView::onOverviewTabSelected(Evas_Object *tab, void *eventInfo)
{
	if (m_currentTabContent != tcOverview)
	{
		m_currentTabContent = tcOverview;
		elm_box_unpack(getEo(), m_pTransactionsTabContent);
		evas_object_hide(m_pTransactionsTabContent);

		elm_box_pack_before(getEo(), m_pOverviewTabContent, m_pTransactionBtn);
		evas_object_show(m_pOverviewTabContent);
	}
}

void AccountView::onTransactTabSelected(Evas_Object *tab, void *eventInfo)
{
	if (m_currentTabContent != tcTransactions)
	{
		m_currentTabContent = tcTransactions;
		elm_box_unpack(getEo(), m_pOverviewTabContent);
		evas_object_hide(m_pOverviewTabContent);

		elm_box_pack_before(getEo(), m_pTransactionsTabContent,
				m_pTransactionBtn);
		evas_object_show(m_pTransactionsTabContent);
	}
}
