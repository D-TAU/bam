#include "View.h"
#include "CallbackAssist.h"

View::View()
	: m_pEo(nullptr)
{
}

View::~View()
{
}

void View::setEo(Evas_Object *obj)
{
	m_pEo = obj;
	evas_object_event_callback_add(m_pEo, EVAS_CALLBACK_FREE, EVAS_OBJECT_EVET_CB(View, onFree), this);
}

void View::onDestroy(View &view)
{
	delete this;
}

void View::onFree(Evas_Object *obj, void *eventInfo)
{
	onDestroy(*this);
}

void View::expand()
{
	evas_object_size_hint_align_set(m_pEo, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(m_pEo, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
}

