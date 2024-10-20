#include"DatabaseConnection.h" // this can be put in either .cpp or . put here is better
#include"StaffManager.h"

void transform(sql::ResultSet* rs, Staff* staff)
{
	staff->staffID = rs->getInt(1);
	staff->staffIC = rs->getString(2);
	staff->name = rs->getString(3);
	staff->phoneNo = rs->getString(4);
	staff->email = rs->getString(5);
	staff->role = rs->getString(6);
}

bool StaffManager::staffExists(int staffID)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE staff_id = ?");
	ps->setInt(1, staffID);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

Staff* StaffManager::getStaffs() //select all customer
{
	DatabaseConnection dbConn;

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff");
	sql::ResultSet* rs = ps->executeQuery();

	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next())
	{
		if (staff == NULL)
		{
			staff = new Staff();
			head = staff;
		}
		else
		{
			staff->next = new Staff();
			staff = staff->next;
		}
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

int StaffManager::addStaff(Staff* staff)
{
	DatabaseConnection dbConn; // declare dbConn

	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Staff(STAFF_ID, SIC, SName, SPhone_No, SEmail, SRole) VALUES (?,?,?,?,?,?)");
	//if the menu_id is auto generated than no need to insert here
	ps->setInt(1, staff->staffID);
	ps->setString(2, staff->staffIC);
	ps->setString(3, staff->name);
	ps->setString(4, staff->phoneNo);
	ps->setString(5, staff->email);
	ps->setString(6, staff->role);

	int numRowsaffected = ps->executeUpdate();

	ps->close();
	//psSelect->close();
	delete ps;
	//delete psSelect;
	return numRowsaffected;
}

int StaffManager::updateStaff(Staff* staff)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps;

	std::string query = "UPDATE Staff SET ";

	bool needsComma = false;

	if (!staff->staffIC.empty())
	{
		query += "SIC = ?";
		needsComma = true;
	}

	if (!staff->name.empty())
	{
		if (needsComma)
			query += ", ";

		query += "SName = ?";
		needsComma = true;
	}

	if (!staff->phoneNo.empty()) // Assuming 0 is not a valid price
	{
		if (needsComma)
			query += ", ";

		query += "SPhone_No = ?";
		needsComma = true;
	}

	if (!staff->email.empty())
	{
		if (needsComma)
			query += ", ";

		query += "SEmail = ?";
		needsComma = true;
	}

	if (!staff->role.empty())
	{
		if (needsComma)
			query += ", ";

		query += "SRole = ?";
	}

	// Add the WHERE clause
	query += " WHERE Staff_id = ?";

	ps = dbConn.prepareStatement(query);

	// Bind parameters based on the provided fields
	int parameterIndex = 1;

	if (!staff->staffIC.empty())
		ps->setString(parameterIndex++, staff->staffIC);

	if (!staff->name.empty())
		ps->setString(parameterIndex++, staff->name);

	if (!staff->phoneNo.empty())
		ps->setString(parameterIndex++, staff->phoneNo);

	if (!staff->email.empty())
		ps->setString(parameterIndex++, staff->email);

	if (!staff->role.empty())
		ps->setString(parameterIndex++, staff->role);

	ps->setInt(parameterIndex, staff->staffID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;
	//ps = nullptr;
	return numRowsAffected;
}

int StaffManager::deleteStaff(Staff* staff)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Staff WHERE Staff_id = ?");

	ps->setInt(1, staff->staffID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();

	delete ps;

	return numRowsAffected;
}

Staff* StaffManager::getStaff(int staffID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE Staff_id = ?");

	ps->setInt(1, staffID); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;

	if (rs->next())
	{
		staff = new Staff();
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return staff;
}