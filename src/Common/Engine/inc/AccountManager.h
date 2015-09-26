/*
 * AccountManager.h
 *
 *  Created on: Sep 1, 2015
 *      Author: vifactor
 */

#ifndef ACCOUNTMANAGER_H_
#define ACCOUNTMANAGER_H_

namespace sqlite
{
    class database;
};
class Account;

class AccountManager
{
public:
	AccountManager();
	virtual ~AccountManager();

	Account * getCurrentAccount() const;
	void setCurrentAccount(int id);
private:
	/*accounts database*/
	sqlite::database *m_db;
	/*pointer to current account*/
	Account * m_pAccount;
};

#endif /* ACCOUNTMANAGER_H_ */
