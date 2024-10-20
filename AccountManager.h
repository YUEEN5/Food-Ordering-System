#include"Account.h"

#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

class AccountManager
{
public:
	//can add, delete, update
	int addAccC(Account* acc);
	int addAccS(Account* acc);
	int updateAcc(Account* acc);
	int updateAccPw(Account* acc);
	int updateAccPwC(Account* acc);
	int deleteAcc(Account* acc);
	int deleteAccC(Account* acc);
	int deleteAccS(Account* acc);
	bool pwCorrectC(std::string password);
	bool pwCorrectS(std::string password);
	Account* getAccS(int staffID);
};

#endif
#pragma once
