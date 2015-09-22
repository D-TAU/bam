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
	evas_object_show(mainBox);

	tb = elm_toolbar_add(parent);
	elm_toolbar_shrink_mode_set(tb, ELM_TOOLBAR_SHRINK_SCROLL);
	evas_object_size_hint_weight_set(tb, 0.0, 0.0);
	evas_object_size_hint_align_set(tb, EVAS_HINT_FILL, 0.0);
	evas_object_show(tb);

	elm_toolbar_item_append(tb, nullptr, "Overview", EVAS_SMART_CB(AccountView, onOverviewTabSelected), this);
	elm_toolbar_item_append(tb, nullptr, "Transactions", EVAS_SMART_CB(AccountView, onTransactTabSelected), this);

	m_pTabContent = elm_box_add(mainBox);
	evas_object_size_hint_weight_set(m_pTabContent, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	elm_box_pack_end(mainBox, tb);
	elm_box_pack_end(mainBox, m_pTabContent);
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
	elm_object_text_set(label, applyFontSize("Interests rate: ").c_str());
	evas_object_show(label);

	m_pInterestsRateLabel = elm_label_add(box);
	evas_object_show(m_pInterestsRateLabel);

	elm_box_pack_end(box, label);
	elm_box_pack_end(box, m_pInterestsRateLabel);

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

void AccountView::setCurrentBalance(const std::string &str)
{
	std::ostringstream ss;
	ss << "<color=#72ea79><b>" << str << "</b></color>";
	elm_object_text_set(m_pCurrentBalanceLabel, applyFontSize(ss.str()).c_str());
}

void AccountView::setInterestsRate(const std::string &str)
{
	std::ostringstream ss;
	ss << "<color=#72ea79><b>" << str << "</b></color>";
	elm_object_text_set(m_pInterestsRateLabel, applyFontSize(ss.str()).c_str());
}

void AccountView::onTransactButtonClicked(Evas_Object *btn, void *eventInfo)
{
	if(m_pListener)
		m_pListener->onButtonClicked(*this, TransactButtonId);
}

void AccountView::onOverviewTabSelected(Evas_Object *tab, void *eventInfo)
{
	elm_box_clear(m_pTabContent);

	Evas_Object *balance = createCurrentBalance(m_pTabContent);
	Evas_Object *interests = createInterestsRate(m_pTabContent);
	Evas_Object *tbutton = createTransactionButton(m_pTabContent);

	elm_box_pack_end(m_pTabContent, balance);
	elm_box_pack_end(m_pTabContent, interests);
	elm_box_pack_end(m_pTabContent, tbutton);

	evas_object_show(m_pTabContent);
}

void AccountView::onTransactTabSelected(Evas_Object *tab, void *eventInfo)
{
	elm_box_clear(m_pTabContent);
	//FIXME: insert here real transactions
	Evas_Object *list = elm_list_add(m_pTabContent);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_box_pack_end(m_pTabContent, list);
	//TODO: probably scroller would be useful
	elm_list_item_append(list, "Transaction 1", nullptr, nullptr, nullptr, nullptr);
	elm_list_item_append(list, "Transaction 2", nullptr, nullptr, nullptr, nullptr);
	elm_list_item_append(list, "Transaction N", nullptr, nullptr, nullptr, nullptr);
	/* enable multiple selection and always select */

	elm_list_go(list);
	evas_object_show(list);

	evas_object_show(m_pTabContent);
}
