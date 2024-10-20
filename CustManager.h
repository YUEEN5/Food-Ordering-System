#include"Customer.h"


#ifndef CUSTMANAGER_H
#define CUSTMANAGER_H

class CustManager
{
public:
	//can add, delete, update
	bool custExists(int custID);
	int addCust(Customer* cust);
	int updateCust(Customer* cust);
	int deleteCust(Customer* cust);
	Customer* getCust(int custID);
	Customer* getCusts();
	Customer* getIC(int custID);
};

#endif
#pragma once
