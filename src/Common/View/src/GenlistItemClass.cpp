#include "GenlistItemClass.h"
#include "GenlistItem.h"

GenlistItemClass::GenlistItemClass(const char *itemStyle, const char *decorateItemStyle, const char *decorateAllItemStyle)
	: m_pClass(nullptr)
{
	m_pClass = elm_genlist_item_class_new();
	m_pClass->item_style = itemStyle;
	m_pClass->decorate_item_style = decorateItemStyle;
	m_pClass->decorate_all_item_style = decorateAllItemStyle;

	registerCb();
}

GenlistItemClass::~GenlistItemClass()
{
	elm_genlist_item_class_free(m_pClass);
}

void GenlistItemClass::registerCb()
{
	m_pClass->func.content_get = GenlistItem::get_content_cb;
	m_pClass->func.text_get = GenlistItem::get_text_cb;
	m_pClass->func.state_get = GenlistItem::get_state_cb;
	m_pClass->func.del = GenlistItem::del_cb;
}

