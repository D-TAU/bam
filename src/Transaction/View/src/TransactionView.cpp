/*
 * TransactionView.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: vifactor
 */

#include "TransactionView.h"

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

TransactionView::TransactionView(Evas_Object *parent)
	: m_pMoneyEntry(nullptr)
	, m_pCalendar(nullptr)
{
	create(parent);
}

TransactionView::~TransactionView()
{
	// TODO Auto-generated destructor stub
}

void TransactionView::create(Evas_Object *parent)
{
	Evas_Object *mainBox = elm_box_add(parent);
	setEo(mainBox);
	elm_box_homogeneous_set(mainBox, false);
	elm_box_horizontal_set(mainBox, false);

	Evas_Object *entry = createEntry(mainBox);
	Evas_Object *calendar = createCalendar(mainBox);
	Evas_Object *buttons = createButtons(mainBox);

	elm_box_pack_end(mainBox, entry);
	elm_box_pack_end(mainBox, calendar);
	elm_box_pack_end(mainBox, buttons);
}

Evas_Object *TransactionView::createEntry(Evas_Object *parent)
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

Evas_Object *TransactionView::createCalendar(Evas_Object *parent)
{
	Evas_Object *box = elm_box_add(parent);

	return box;
}

Evas_Object *TransactionView::createButtons(Evas_Object *parent)
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
    //evas_object_smart_callback_add(withdraw, "clicked", EVAS_SMART_CB(AccountView, onWithdrawButtonClicked), this);

	Evas_Object *depos = elm_button_add(box);
	evas_object_size_hint_align_set(depos, 0.1, 0.5);
	evas_object_size_hint_weight_set(depos, EVAS_HINT_EXPAND, 0.5);
	evas_object_show(depos);
	elm_object_text_set(depos, applyFontSize("Deposit").c_str());
    //evas_object_smart_callback_add(depos, "clicked", EVAS_SMART_CB(AccountView, onDepositButtonClicked), this);

	elm_box_pack_end(box, withdraw);
	elm_box_pack_end(box, depos);

	return box;
}
