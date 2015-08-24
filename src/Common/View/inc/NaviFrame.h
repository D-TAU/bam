/*
 * Naviframe.h
 *
 *  Created on: Aug 22, 2015
 *      Author: D-TAU
 */

#ifndef NAVIFRAME_H_
#define NAVIFRAME_H_

#include "View.h"
#include "NaviFrameItem.h"

class NaviFrame
	: public View
{
public:
	NaviFrame(Evas_Object *parent);
	virtual ~NaviFrame();

	void push(NaviFrameItem *item);
	void pop();
	NaviFrameItem *getTopItem() const;
	NaviFrameItem *getBottomItem() const;
};


#endif /* NAVIFRAME_H_ */
