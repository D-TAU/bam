#include "GenlistItem.h"
#include <string.h>

GenlistItem::GenlistItem(Genlist &parent, GenlistItemClassRef &itemClass)
	: m_pGenlist(&parent)
	, m_ItemClass(itemClass)
{

}

GenlistItem::~GenlistItem()
{

}

Genlist *GenlistItem::getParent() const
{
	return m_pGenlist;
}

GenlistItemClassRef GenlistItem::getItemClass() const
{
	return m_ItemClass;
}

std::string GenlistItem::getText(const char *part)
{
	return std::string();
}

Evas_Object *GenlistItem::getContent(const char *part)
{
	return nullptr;
}

bool GenlistItem::getState(const char *part)
{
	return false;
}

void GenlistItem::onDel()
{
	delete this;
}

void GenlistItem::onDestroy(ViewItem &item)
{
 // see onDel
}

char *GenlistItem::get_text_cb(void *data, Evas_Object *obj, const char *part)
{
	GenlistItem *self = static_cast<GenlistItem*>(data);
	std::string str = self->getText(part);
	return str.empty() ? nullptr : strdup(str.c_str());
}

Evas_Object *GenlistItem::get_content_cb(void *data, Evas_Object *obj, const char *part)
{
	GenlistItem *self = static_cast<GenlistItem*>(data);
	return self->getContent(part);
}

Eina_Bool GenlistItem::get_state_cb(void *data, Evas_Object *obj, const char *part)
{
	GenlistItem *self = static_cast<GenlistItem*>(data);
	return self->getState(part);
}

void GenlistItem::del_cb(void *data, Evas_Object *obj)
{
	GenlistItem *self = static_cast<GenlistItem*>(data);
	self->onDel();
}
