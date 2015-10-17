/*
 * TransactionViewItem.cpp
 *
 *  Created on: Oct 11, 2015
 *      Author: D-TAU
 */

#include "TransactionViewItem.h"

namespace
{
	GenlistItemClassRef defaultStyle = std::make_shared<GenlistItemClass>("default");
}

TransactionViewItem::TransactionViewItem(Genlist &parent)
	: GenlistItem(parent, defaultStyle)
{

}

TransactionViewItem::~TransactionViewItem()
{
}

