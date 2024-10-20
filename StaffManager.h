#include"Staff.h"

#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

class StaffManager
{
public:
	//can add, delete, update
	int addStaff(Staff* staff);
	int updateStaff(Staff* staff);
	int deleteStaff(Staff* staff);
	bool staffExists(int staffID);
	Staff* getStaff(int staffID);
	Staff* getStaffs();
};

#endif
#pragma once
