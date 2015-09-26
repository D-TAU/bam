/*
 * TransactionItem.cpp
 *
 *  Created on: Sep 26, 2015
 *      Author: vifactor
 */

#include <TransactionItem.h>

std::string TransactionItem::getTextForEnum(TransactionItem::Type enumVal )
{
    static const char * EnumStrings[] = { "0", "1"};
    return EnumStrings[enumVal];
}

TransactionItem::TransactionItem()
{
	// TODO Auto-generated constructor stub

}

TransactionItem::~TransactionItem()
{
	// TODO Auto-generated destructor stub
}
