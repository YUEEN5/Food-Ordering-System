#include"DatabaseConnection.h" // this can be put in either .cpp or . put here is better
#include"CustManager.h"

void transform(sql::ResultSet* rs, Customer* cust)
{
	cust->custID = rs->getInt(1);
	cust->custIC = rs->getString(2);
	cust->name = rs->getString(3);
	cust->phoneNo = rs->getString(4);
	cust->email = rs->getString(5);
	cust->address = rs->getString(6);
	cust->gender = rs->getString(7);
}

bool CustManager::custExists(int custID)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customer WHERE Cust_id = ?");
	ps->setInt(1, custID);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

int CustManager::addCust(Customer* cust)
{
	DatabaseConnection dbConn; // declare dbConn

	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Customer(Cust_id, CIC, CName, CPhone_No, CEmail, CAddress, CGender) VALUES (?,?,?,?,?,?,?)");
	//if the menu_id is auto generated than no need to insert here
	ps->setInt(1, cust->custID);
	ps->setString(2, cust->custIC); 
	ps->setString(3, cust->name);
	ps->setString(4, cust->phoneNo);
	ps->setString(5, cust->email);
	ps->setString(6, cust->address);
	ps->setString(7, cust->gender);

	int numRowsaffected = ps->executeUpdate();

	ps->close();
	//psSelect->close();
	delete ps;
	//delete psSelect;
	return numRowsaffected;
}

int CustManager::updateCust(Customer* cust)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps;

	std::string query = "UPDATE Customer SET ";

	bool needsComma = false;

	if (!cust->custIC.empty())
	{
		query += "CIC = ?";
		needsComma = true;
	}

	if (!cust->name.empty())
	{
		if (needsComma)
			query += ", ";
		
		query += "CName = ?";
		needsComma = true;
	}

	if (!cust->phoneNo.empty()) // Assuming 0 is not a valid price
	{
		if (needsComma)
			query += ", ";

		query += "CPhone_No = ?";
		needsComma = true;
	}

	if (!cust->email.empty())
	{
		if (needsComma)
			query += ", ";

		query += "CEmail = ?";
		needsComma = true;
	}

	if (!cust->address.empty())
	{
		if (needsComma)
			query += ", ";

		query += "CAddress = ?";
		needsComma = true;
	}

	if (!cust->gender.empty())
	{
		if (needsComma)
			query += ", ";

		query += "CGender = ?";
	}

	// Add the WHERE clause
	query += " WHERE Cust_id = ?";

	ps = dbConn.prepareStatement(query);

	// Bind parameters based on the provided fields
	int parameterIndex = 1;

	if (!cust->custIC.empty())
		ps->setString(parameterIndex++, cust->custIC);

	if (!cust->name.empty())
		ps->setString(parameterIndex++, cust->name);

	if (!cust->phoneNo.empty())
		ps->setString(parameterIndex++, cust->phoneNo);

	if (!cust->email.empty())
		ps->setString(parameterIndex++, cust->email);

	if (!cust->address.empty())
		ps->setString(parameterIndex++, cust->address);

	if (!cust->gender.empty())
		ps->setString(parameterIndex++, cust->gender);

	ps->setInt(parameterIndex, cust->custID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;
	//ps = nullptr;
	return numRowsAffected;
}

int CustManager::deleteCust(Customer* cust)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Customer WHERE Cust_id = ?");

	ps->setInt(1, cust->custID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();

	delete ps;

	return numRowsAffected;
}

Customer* CustManager::getCust(int custID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customer WHERE Cust_id = ?");

	ps->setInt(1, custID); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Customer* cust = NULL;

	if (rs->next())
	{
		cust = new Customer();
		transform(rs, cust);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return cust;
}

Customer* CustManager::getCusts() //select all customer
{
	DatabaseConnection dbConn;

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customer");
	sql::ResultSet* rs = ps->executeQuery();

	Customer* cust = NULL;
	Customer* head = NULL;

	while (rs->next())
	{
		if (cust == NULL)
		{
			cust = new Customer();
			head = cust;
		}
		else
		{
			cust->next = new Customer();
			cust = cust->next;
		}
		transform(rs, cust);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Customer* CustManager::getIC(int custID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT CIC FROM Customer WHERE Cust_id = ?");

	ps->setInt(1, custID); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Customer* cust = NULL;

	if (rs->next())
	{
		cust = new Customer();
		cust->custIC = rs->getString("CIC");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return cust;
}