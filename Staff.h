#include<string>
#include<iomanip>
#include <sstream>
using namespace std;
#ifndef STAFF_H
#define STAFF_H

class Staff
{
public:
	int staffID;
	string staffIC, name, phoneNo, email, role;
	Staff* next;
};

#endif
#pragma once
