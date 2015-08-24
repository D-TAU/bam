#include "AccountView.h"
#include "CallbackAssist.h"

#include <sstream>
#include <stdlib.h>

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
	: m_pMoneyEntry(nullptr)
	, m_pCurrentBalanceLabel(nullptr)
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
	Evas_Object *mainBox = elm_box_add(parent);
	setEo(mainBox);
	elm_box_homogeneous_set(mainBox, false);
	elm_box_horizontal_set(mainBox, false);

	Evas_Object *balance = createCurrentBalance(mainBox);
	Evas_Object *interests = createInterestsRate(mainBox);
	//Evas_Object *entry = createEntry(mainBox);
	//Evas_Object *buttons = createButtons(mainBox);
	Evas_Object *tbutton = createTransactionButton(mainBox);

	elm_box_pack_end(mainBox, balance);
	elm_box_pack_end(mainBox, interests);
	//elm_box_pack_end(mainBox, entry);
	elm_box_pack_end(mainBox, tbutton);
	//elm_box_pack_end(mainBox, buttons);
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

Evas_Object *AccountView::createEntry(Evas_Object *parent)
{
	Evas_Object *layout = elm_layout_add(parent);
	elm_layout_theme_set(layout, "layout", "application", "default");
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);
	evas_object_show(layout);

	Evas_Object *bg = elm_bg_add(layout);
	evas_object_show(bg);
	evas_object_size_hint_align_set(bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_color_set(bg, 140, 150, 170, 200);
	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	m_pMoneyEntry = elm_entry_add(layout);
	elm_entry_single_line_set(m_pMoneyEntry, true);
	evas_object_show(m_pMoneyEntry);
	elm_entry_text_style_user_push(m_pMoneyEntry, "DEFAULT='font_size=36'");
	elm_object_part_text_set(m_pMoneyEntry, "guide", applyFontSize("Input...").c_str());

	elm_object_part_content_set(layout, "elm.swallow.bg", bg);
	elm_layout_content_set(layout, "elm.swallow.content", m_pMoneyEntry);

	return layout;
}

Evas_Object *AccountView::createButtons(Evas_Object *parent)
{
	Evas_Object *box = elm_box_add(parent);
	evas_object_show(box);
	elm_box_homogeneous_set(box, false);
	elm_box_horizontal_set(box, true);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.2);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object *withdraw = elm_button_add(box);
	evas_object_size_hint_align_set(withdraw, 0.9, 0.5);
	evas_object_size_hint_weight_set(withdraw, EVAS_HINT_EXPAND, 0.5);
	evas_object_show(withdraw);
	elm_object_text_set(withdraw, applyFontSize("Withdraw").c_str());
    evas_object_smart_callback_add(withdraw, "clicked", EVAS_SMART_CB(AccountView, onWithdrawButtonClicked), this);

	Evas_Object *depos = elm_button_add(box);
	evas_object_size_hint_align_set(depos, 0.1, 0.5);
	evas_object_size_hint_weight_set(depos, EVAS_HINT_EXPAND, 0.5);
	evas_object_show(depos);
	elm_object_text_set(depos, applyFontSize("Deposit").c_str());
    evas_object_smart_callback_add(depos, "clicked", EVAS_SMART_CB(AccountView, onDepositButtonClicked), this);

	elm_box_pack_end(box, withdraw);
	elm_box_pack_end(box, depos);

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

std::string AccountView::getInputMoney() const
{
	std::string res;
	const char *text = elm_object_text_get(m_pMoneyEntry);
	char *utf8Text = elm_entry_markup_to_utf8(text);

	if(utf8Text)
	{
		res = utf8Text;
		free(utf8Text);
	}

	return res;
}

void AccountView::onWithdrawButtonClicked(Evas_Object *btn, void *eventInfo)
{
	if(m_pListener)
		m_pListener->onButtonClicked(*this, WithdrawButtonId);
}

void AccountView::onDepositButtonClicked(Evas_Object *btn, void *eventInfo)
{
	if(m_pListener)
		m_pListener->onButtonClicked(*this, DepositButtonId);
}

void AccountView::onTransactButtonClicked(Evas_Object *btn, void *eventInfo)
{
	if(m_pListener)
		m_pListener->onButtonClicked(*this, TransactButtonId);
}

Evas_Object *AccountView::createTransactionView(Elm_Object_Item *parent)
{
/*	Evas_Object * box = elm_box_add(m_pNaviFrame);
	evas_object_show(box);
	elm_box_homogeneous_set(box, false);
	elm_box_horizontal_set(box, false);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, 0.2);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	Evas_Object *entry = createEntry(box);
	Evas_Object *buttons = createButtons(box);

	elm_box_pack_end(box, entry);
	elm_box_pack_end(box, buttons);

	return box;*/

	return nullptr;
}
