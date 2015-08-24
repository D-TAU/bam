#include "NaviFrameItem.h"

NaviFrameItem::NaviFrameItem()
	: m_pNaviBar(new NaviBar(*this))
{
}

NaviFrameItem::~NaviFrameItem()
{
	delete m_pNaviBar;
}

NaviFrameItem::NaviBar & NaviFrameItem::getNaviBar()
{
	return *m_pNaviBar;
}


NaviFrameItem::NaviBar::NaviBar(NaviFrameItem &parent)
	: m_Parent(parent)
{

}

NaviFrameItem::NaviBar::~NaviBar()
{
}

void NaviFrameItem::NaviBar::setTitle(const std::string &text)
{
	elm_object_item_part_text_set(m_Parent, "elm.text.title", text.c_str());
}


