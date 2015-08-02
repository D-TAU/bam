/*
 * ViewItem.cpp
 *
 *  Created on: Aug 2, 2015
 *      Author: D-TAU
 */

#include "ViewItem.h"
#include "CallbackAssist.h"

ViewItem::ViewItem()
	: m_pItem(nullptr)
{
}

ViewItem::~ViewItem()
{
}

void ViewItem::setElmItem(Elm_Object_Item *item)
{
	m_pItem = item;
	elm_object_item_del_cb_set(item, EVAS_SMART_CB(ViewItem, onDel));
}

void ViewItem::onDestroy(ViewItem &item)
{
	delete this;
}

void ViewItem::onDel(Evas_Object *obj, void *event_info)
{
	onDestroy(*this);
}

