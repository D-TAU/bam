/*
 * AccountManager.cpp
 *
 *  Created on: Sep 1, 2015
 *      Author: vifactor
 */

#include "AccountManager.h"
#include "Account.h"

AccountManager::AccountManager()
	: m_pAccount(nullptr)
{
	//FIXME in-memory database should be replaced by database file
	m_db = new sqlite::database(":memory:");
}

AccountManager::~AccountManager()
{
	delete m_db;
}

Account * AccountManager::getCurrentAccount() const
{
	return m_pAccount;
}

void AccountManager::setCurrentAccount(int id)
{
	// FIXME: later account should be selected from the accounts table
	if(m_pAccount)
		delete m_pAccount;
	m_pAccount = new Account(*m_db);
	m_pAccount->create("MyName", 9, "25", Date("2015-08-03"));
}
