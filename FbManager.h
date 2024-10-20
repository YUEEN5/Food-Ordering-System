#include"Feedback.h"


#ifndef FBMANAGER_H
#define FBMANAGER_H

class FbManager
{
public:
	//can add, delete, update
	bool custExists(int custid);
	bool fbExists(int fbId);
	bool odExists(int orderID);
	int addFb(Feedback* fb);
	Feedback* getFbbasedOrder(int orderID);
	Feedback* getFb(int fbID);
	Feedback* getFbforCust(int custID);
};

#endif
#pragma once
