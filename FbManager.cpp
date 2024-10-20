#include"DatabaseConnection.h" // this can be put in either .cpp or . put here is better
#include"FbManager.h"

void transform(sql::ResultSet* rs, Feedback* fb)
{
	fb->fbID = rs->getInt(1);
	fb->orderID = rs->getInt(2);
	fb->custID = rs->getInt(3);
	fb->rating = rs->getInt(4);
	fb->comment = rs->getString(5);

}

bool FbManager::fbExists(int fbId)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Feedback WHERE Feedback_id = ?");
	ps->setInt(1, fbId);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

bool FbManager::odExists(int orderID)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Feedback WHERE Order_id = ?");
	ps->setInt(1, orderID);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

bool FbManager::custExists(int custid)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Feedback WHERE Cust_id = ?");
	ps->setInt(1, custid);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

int FbManager::addFb(Feedback* fb)
{
	DatabaseConnection dbConn; // declare dbConn

	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO feedback(feedback_id, Order_id, Cust_id, rating, comments) VALUES (?,?,?,?,?)");
	//if the menu_id is auto generated than no need to insert here
	ps->setInt(1, fb->fbID);
	ps->setInt(2, fb->orderID);
	ps->setInt(3, fb->custID);
	ps->setInt(4, fb->rating);
	ps->setString(5, fb->comment);

	int numRowsaffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsaffected;
}

Feedback* FbManager::getFbbasedOrder(int orderID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Feedback WHERE ORDER_ID = ?");

	ps->setInt(1, orderID); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Feedback* fb = NULL;

	if (rs->next())
	{
		fb = new Feedback();
		transform(rs, fb);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return fb;
}

Feedback* FbManager::getFb(int fbID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Feedback WHERE FEEDBACK_ID = ?");

	ps->setInt(1, fbID); 

	sql::ResultSet* rs = ps->executeQuery();
	Feedback* fb = NULL;

	if (rs->next())
	{
		fb = new Feedback();
		transform(rs, fb);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return fb;
}

Feedback* FbManager::getFbforCust(int custID)
{
	DatabaseConnection dbConn;

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Feedback WHERE CUST_ID = ?");

	ps->setInt(1, custID);

	sql::ResultSet* rs = ps->executeQuery();

	Feedback* fb = NULL;
	Feedback* head = NULL;

	while (rs->next())
	{
		if (fb == NULL)
		{
			fb = new Feedback();
			head = fb;
		}
		else
		{
			fb->next = new Feedback();
			fb = fb->next;
		}
		transform(rs, fb);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}