#include "MenuManager.h"
#ifndef AMINTERFACE_H
#define AMINTERFACE_H


class AmInterface
{
public:
	void selectOneStaff(int staffID);
	void editPw(int staffID, int& status);
	void editStaffProfile(int staffID);
	void viewAllStaff();
	void deleteS();
	void viewMenu();
	void addNewMenu();
	void deleteM();
	void updateM();
	void viewAllCustID();
	void viewCust();
	void deleteC();
	void updateC();
	void viewOrders();
	void selectOneMenu();
	void SignUpStaff(int& staffID);
	void TodaySalesReport();
	void DailySales();
	void DailySales2();
	void TotalSalesReport();
	void TodayOrders();
	//void MonthlySales();
	void YearlySales();
	void overallSales();
	void chooseMonthlySales();
};
#endif
#pragma once
