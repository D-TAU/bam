#include "Naviframe.h"

NaviFrame::NaviFrame(Evas_Object * parent)
{
	setEo(elm_naviframe_add(parent));
}

NaviFrame::~NaviFrame()
{
}

void NaviFrame::push(NaviFrameItem * item)
{
	Elm_Object_Item * elmItem = elm_naviframe_item_push(getEo(), nullptr, nullptr, nullptr, item->getContent(), nullptr);
	item->setElmItem(elmItem);
	item->onFrameCreated(*item);
}

void NaviFrame::pop()
{
	elm_naviframe_item_pop(getEo());
}

NaviFrameItem *NaviFrame::getTopItem() const
{
	Elm_Object_Item *elmItem = elm_naviframe_top_item_get(getEo());
	NaviFrameItem *item = static_cast<NaviFrameItem*>(elm_object_item_data_get(elmItem));
	return item;
}

NaviFrameItem *NaviFrame::getBottomItem() const
{
	Elm_Object_Item *elmItem = elm_naviframe_bottom_item_get(getEo());
	NaviFrameItem *item = static_cast<NaviFrameItem*>(elm_object_item_data_get(elmItem));
	return item;
}
