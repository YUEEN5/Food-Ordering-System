#include"OrderList.h"

#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

class OrderManager
{
public:
	//add, delete, update orders
	int addOrder(OrderList* order);
	int updateOrder(OrderList* order);
	int deleteOrder(OrderList* order);
	//check if the attribute exist
	bool orderExists(int orderID);
	bool fbExists(int fbId);
	//get order's info
	OrderList* getOrders();
	OrderList* getOrderswifMenuID(std::string menuid);
	OrderList* getCustOrders(int custid);
	OrderList* getOrder(int order_id);
	//to generate report
	double getMonthlySales(int year, int month);
	double getDailySales(int year, int month, int day);
	double getDailySales(int year, int month, int day, std::string menuID, int& totalQ);
	double getMenuSales(std::string menuID);
	double SalesEachMonthbMenu(int year, int month, std::string menuID, int& totalQ);
};

#endif;
#pragma once
