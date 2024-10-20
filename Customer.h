#include<string>
#include<iomanip>
#include <sstream>
using namespace std;
#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer
{
public:
	int custID;
	string custIC, name, address, phoneNo, email, gender;
	//double date;
	Customer* next;
	/*Customer() {
		// Auto-generate custId using the counter with leading zeros
		std::stringstream ss;
		ss << "C" << std::setfill('0') << std::setw(3) << counter;
		custID = ss.str();
		counter++;
	}*/
};

#endif
#pragma once
