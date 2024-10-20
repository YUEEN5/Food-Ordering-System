#include"DatabaseConnection.h" 
#include"AccountManager.h"
#include<iostream>
#include <mysql/jdbc.h>

void transform(sql::ResultSet* rs, Account* acc)
{
	acc->accID = rs->getInt("Account_id");
	acc->custID = rs->getInt("Cust_id");
	acc->staffID = rs->getInt("Staff_id");
	acc->adminRole = rs->getBoolean("AdminRole");
	acc->userName = rs->getString("UserName");
	acc->password = rs->getString("Password");
}

bool AccountManager::pwCorrectS(std::string password)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Account WHERE Password = ?");
	ps->setString(1, password);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	rs->close();
	ps->close();
	delete ps;
	delete rs;

	return exists;
}

bool AccountManager::pwCorrectC(std::string password)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Account WHERE Password = ?");
	ps->setString(1, password);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

int AccountManager::addAccC(Account* acc)
{
	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Account(ACCOUNT_ID, CUST_ID, ADMINROLE, USERNAME, PASSWORD) VALUES (?,?,?,?,?)");

	ps->setInt(1, acc->accID);
	ps->setInt(2, acc->custID);
	ps->setBoolean(3, acc->adminRole);
	ps->setString(4, acc->userName);
	ps->setString(5, acc->password);

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}

Account* AccountManager::getAccS(int staffID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Account WHERE Staff_id = ?");

	ps->setInt(1, staffID); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Account* acc = NULL;

	if (rs->next())
	{
		acc = new Account();
		transform(rs, acc);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return acc;
}

int AccountManager::updateAccPwC(Account* acc)
{
	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Account SET Password = ? WHERE Cust_id = ?");


	ps->setString(1, acc->password);

	ps->setInt(2, acc->custID);

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}

int AccountManager::updateAccPw(Account* acc)
{
	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Account SET Password = ? WHERE Staff_id = ?");


	ps->setString(1, acc->password);

	ps->setInt(2, acc->staffID);

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}

int AccountManager::updateAcc(Account* acc)
{
	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Account SET Account_id = ?, Cust_id = ?, AdminRole = ?, UserName=?, Password=? WHERE VALUES Account_id=?");

	ps->setInt(1, acc->accID);
	ps->setInt(2, acc->custID);
	ps->setBoolean(3, acc->adminRole);
	ps->setString(4, acc->userName);
	ps->setString(5, acc->password);

	ps->setInt(6, acc->accID);

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}

int AccountManager::deleteAcc(Account* acc)
{

	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Account WHERE Account_id = ?");

	ps->setInt(1, acc->accID); //index always start at 1 for sql

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}

int AccountManager::deleteAccC(Account* acc)
{

	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Account WHERE Cust_id = ?");

	ps->setInt(1, acc->custID); //index always start at 1 for sql

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}

int AccountManager::deleteAccS(Account* acc)
{

	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Account WHERE Staff_id = ?");

	ps->setInt(1, acc->staffID); //index always start at 1 for sql

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}

int AccountManager::addAccS(Account* acc)
{
	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Account(ACCOUNT_ID, STAFF_ID, ADMINROLE, USERNAME, PASSWORD) VALUES (?,?,?,?,?)");

	ps->setInt(1, acc->accID); //index always start at 1 for sql
	ps->setInt(2, acc->staffID);
	ps->setBoolean(3, acc->adminRole);
	ps->setString(4, acc->userName);
	ps->setString(5, acc->password);

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}


