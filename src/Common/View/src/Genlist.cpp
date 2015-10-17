#include "Genlist.h"
#include "CallbackAssist.h"

Genlist::Genlist(Evas_Object *parent)
	: View()
	, m_pListener(nullptr)
{
	setEo(elm_genlist_add(parent));
}

Genlist::~Genlist()
{

}

void Genlist::setListener(IGenlistListener *listener)
{
	m_pListener = listener;
}

void Genlist::appendItem(GenlistItem &item, GenlistItem *parentItem, Elm_Genlist_Item_Type type)
{
	GenlistItemClassRef itemClass = item.getItemClass();
	Elm_Genlist_Item_Class *item_class = itemClass ? itemClass->getGenlistItemClass() : nullptr;
	Elm_Object_Item *parent_item = parentItem ? parentItem->getElmItem() : nullptr;
	elm_genlist_item_append(getEo(), item_class, &item, parent_item, type, EVAS_SMART_CB(Genlist, onSelected), this);
}

void Genlist::onSelected(Evas_Object *obj, void *eventInfo)
{
	if(m_pListener)
	{
		Elm_Object_Item *it = (Elm_Object_Item*)eventInfo;
		GenlistItem *item = static_cast<GenlistItem*>(elm_object_item_data_get(it));
		m_pListener->onSelected(*this, *item);
	}
}

