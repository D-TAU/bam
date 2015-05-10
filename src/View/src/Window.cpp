#include "Window.h"
#include "Bam.h"

Window::Window()
	: View()
	, m_pWin(nullptr)
	, m_pConform(nullptr)
	, m_pBg(nullptr)
{
	create();
}

Window::~Window()
{
	BAM_LOG("Window destroy");
}

void Window::create()
{
	m_pWin = elm_win_add(NULL, APP_NAME, ELM_WIN_BASIC);
	elm_win_conformant_set(m_pWin, EINA_TRUE);
	elm_win_indicator_mode_set(m_pWin, ELM_WIN_INDICATOR_SHOW);
	setEo(m_pWin);

	m_pConform = elm_conformant_add(m_pWin);
	evas_object_show(m_pConform);
	evas_object_size_hint_align_set(m_pConform, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(m_pConform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	m_pBg = elm_bg_add(m_pConform);
	evas_object_size_hint_align_set(m_pBg, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(m_pBg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(m_pBg);

	elm_win_resize_object_add(m_pWin, m_pConform);
	elm_object_part_content_set(m_pConform, "elm.swallow.bg", m_pBg);
}

void Window::setContent(Evas_Object *content)
{
    elm_object_part_content_set(m_pConform, "elm.swallow.content", content);
}

Evas_Object *Window::getContent() const
{
	 return elm_object_part_content_get(m_pConform, "elm.swallow.content");
}
