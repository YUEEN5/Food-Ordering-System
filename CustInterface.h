#include "Customer.h"
#include "MenuManager.h"
#ifndef CUSTINTERFACE_H
#define CUSTINTERFACE_H

class CustInterface
{
public:
	void viewMenu();
	void viewRandMenu();
	void PlaceOrder(int custid);
	//void DeleteO(int orderid);
	//void EditOrder(int orderid);
	//void RegMember();
	void viewFeedback();
	void viewCode(int custid);
	void viewOrderbyUser(int custid);
	void doFeedback(int custid);
	void selectmultiple();
	void selectOneCust(int custid);
	void SignUpCust(int& custid);
	void editPw(int custID, int& status);
	void UpdateProfile(int custid);

};
#endif
#pragma once
