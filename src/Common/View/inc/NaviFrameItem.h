#ifndef NAVIFRAMEITEM_H_
#define NAVIFRAMEITEM_H_

#include "ViewItem.h"

#include <string>

class NaviFrameItem
	: public ViewItem
{
public:
	class NaviBar;
	friend class NaviFrame;

public:
	NaviFrameItem();
	virtual ~NaviFrameItem();

	NaviBar & getNaviBar();

private:
	virtual void onFrameCreated(NaviFrameItem &item) = 0;

private:
	NaviBar * m_pNaviBar;
};

class NaviFrameItem::NaviBar
{
public:
	friend class NaviFrameItem;

public:
	void setTitle(const std::string &text);

private:
	NaviBar(NaviFrameItem &parent);
	~NaviBar();

private:
	NaviFrameItem & m_Parent;
};

#endif /* NAVIFRAMEITEM_H_ */
