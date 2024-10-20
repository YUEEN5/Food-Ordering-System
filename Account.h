#include <string>
#include "Customer.h"
using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
	Customer cust;
	int accID, custID, staffID;
	string password, userName;
	bool adminRole;
	Account* next;
};

#endif
#pragma once
