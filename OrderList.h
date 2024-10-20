#include<ctime>
using namespace std;

#ifndef ORDERLIST_H
#define ORDERLIST_H

class OrderList
{
public:
	int orderID, quantity, custID, disCode;
	double tPrice, discount;
	string remark, menuID, oDateTime, payMethod, delivery, address;
	//time_t oDateTime;
	//std::tm oDateTime;
	OrderList* next;
};

#endif
#pragma once
