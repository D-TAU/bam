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
class AccountHandle;

class AccountManager
{
public:
	AccountManager();
	virtual ~AccountManager();

	AccountHandle * getCurrentAccount() const;
	void setCurrentAccount(int id);
private:
	/*accounts database*/
	sqlite::database *m_db;
	/*pointer to current account*/
	AccountHandle * m_pAccount;
};

#endif /* ACCOUNTMANAGER_H_ */
