#include"DatabaseConnection.h" // this can be put in either .cpp or . put here is better
#include"OrderManager.h"
#include<sstream>
#include<iomanip>

void transform(sql::ResultSet* rs, OrderList* order)
{
	order->orderID = rs->getInt(1);
	order->menuID = rs->getString(2);
	order->custID = rs->getInt(3);
	order->remark = rs->getString(4);
	order->tPrice = rs->getDouble(5);
	order->quantity = rs->getInt(6);
	order->payMethod = rs->getString(7);
	order->delivery = rs->getString(8);
	order->disCode = rs->getInt(9);
	order->discount = rs->getDouble(10);
	order->oDateTime = rs->getString(11);
	order->address = rs->getString(12);
}

bool OrderManager::fbExists(int fbId)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Orderlist WHERE Promocode = ?");
	ps->setInt(1, fbId);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

bool OrderManager::orderExists(int orderID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM OrderList WHERE Order_id = ?");
	ps->setInt(1, orderID);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

int OrderManager::addOrder(OrderList* order)
{
	DatabaseConnection dbConn; // declare dbConn

	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Orderlist(Order_ID, Menu_ID, Cust_ID, Remark, Total_Price, Quantity, PayMethod, Delivery, Promocode, Discount, Order_Date, address) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)");
	ps->setInt(1, order->orderID); //auto-generated
	ps->setString(2, order->menuID);
	ps->setInt(3, order->custID);
	ps->setString(4, order->remark);
	ps->setDouble(5, order->tPrice);
	ps->setInt(6, order->quantity);
	ps->setString(7, order->payMethod);
	ps->setString(8, order->delivery);
	ps->setInt(9, order->disCode);
	ps->setDouble(10, order->discount);
	ps->setString(11, order->oDateTime);
	ps->setString(12, order->address);
	//ps->setUInt64(7, static_cast<uint64_t>(order->oDateTime));


	// Convert order->oDateTime to string in the format 'YYYY-MM-DD HH:MM:SS'
	/*std::stringstream dateTimeStream;
	dateTimeStream << std::put_time(std::localtime(&order->oDateTime), "%Y-%m-%d %H:%M:%S");
	std::string dateTimeString = dateTimeStream.str();

	// Set the formatted date and time
	ps->setString(6, dateTimeString);*/

	int numRowsaffected = ps->executeUpdate();

	ps->close();
	delete ps;
	return numRowsaffected;
}

OrderList* OrderManager::getOrder(int orderID)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Orderlist WHERE Order_id = ?");

	ps->setInt(1, orderID); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	OrderList* order = NULL;

	if (rs->next())
	{
		order = new OrderList();
		transform(rs, order);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return order;
}

int OrderManager::updateOrder(OrderList* order)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps;

	// Build the base UPDATE query
	std::string query = "UPDATE ORDERLIST SET ";

	// Conditionally add fields to the query based on whether they are provided
	bool needsComma = false;

	if (!order->menuID.empty())
	{
		query += "Menu_id = ?";
		needsComma = true;
	}

	if (!order->remark.empty())
	{
		if (needsComma)
			query += ", ";

		query += "Remark = ?";
		needsComma = true;
	}

	if (order->quantity != 0.0) // Assuming 0 is not a valid price
	{
		if (needsComma)
			query += ", ";

		query += "Quantity = ?";
	}

	// Add the WHERE clause
	query += " WHERE Order_id = ?";

	ps = dbConn.prepareStatement(query);

	// Bind parameters based on the provided fields
	int parameterIndex = 1;

	if (!order->menuID.empty())
		ps->setString(parameterIndex++, order->menuID);

	if (!order->remark.empty())
		ps->setString(parameterIndex++, order->remark);

	if (order->quantity != 0.0)
		ps->setDouble(parameterIndex++, order->quantity);

	ps->setInt(parameterIndex, order->orderID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

int OrderManager::deleteOrder(OrderList* order)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM ORDERLIST WHERE order_id = ?");

	ps->setInt(1, order->orderID); //index always start at 1 for sql

	int numRowsaffected = ps->executeUpdate();

	//rs->next(); //ask result to check, to go to the next line, if can return true, if cannot return false

	ps->close();
	//connection->close();
	delete ps;
	return numRowsaffected;
}

OrderList* OrderManager::getOrders() //select all customer
{
	DatabaseConnection dbConn;

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM OrderList");
	sql::ResultSet* rs = ps->executeQuery();


	OrderList* order = NULL;
	OrderList* head = NULL;

	while (rs->next())
	{
		if (order == NULL)
		{
			order = new OrderList();
			head = order;
		}
		else
		{
			order->next = new OrderList();
			order = order->next;
		}
		transform(rs, order);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


OrderList* OrderManager::getOrderswifMenuID(std::string menuid)
{
	DatabaseConnection dbConn;

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM OrderList where menu_id = ?");

	ps->setString(1, menuid);

	sql::ResultSet* rs = ps->executeQuery();

	OrderList* order = NULL;
	OrderList* head = NULL;

	while (rs->next())
	{
		if (order == NULL)
		{
			order = new OrderList();
			head = order;
		}
		else
		{
			order->next = new OrderList();
			order = order->next;
		}
		transform(rs, order);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

/*OrderList* OrderManager::getCustOrders(int custid) //select all customer
{
	DatabaseConnection dbConn;

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT FROM OrderList where Cust_id = ?");

	ps->setInt(1, custid);

	sql::ResultSet* rs = ps->executeQuery();

	OrderList* order = NULL;
	OrderList* head = NULL;

	while (rs->next())
	{
		if (order == NULL)
		{
			order = new OrderList();
			head = order;
		}
		else
		{
			order->next = new OrderList();
			order = order->next;
		}

		order = new OrderList();
		transform(rs, order);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return order;

}*/

OrderList* OrderManager::getCustOrders(int custid)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM OrderList WHERE Cust_id = ?");

	ps->setInt(1, custid); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	OrderList* order = NULL; //this contain the next data

	OrderList* head = NULL; //head contain the data we want to store

	while (rs->next())
	{
		if (order == NULL)
		{
			order = new OrderList();//if the menu hasn't exist, then we create a new menu
			head = order;
		}
		else
		{
			order->next = new OrderList();
			order = order->next;
		}

		//order = new OrderList();

		transform(rs, order);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

double OrderManager::getDailySales(int year, int month, int day) {
	DatabaseConnection dbConn;

	//prepare the SQL query to get daily sales
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DELIVERY, TOTAL_PRICE FROM OrderList WHERE YEAR(ORDER_DATE) = ? AND MONTH(ORDER_DATE) = ? AND DAY(ORDER_DATE) = ?");
	ps->setInt(1, year);
	ps->setInt(2, month);
	ps->setInt(3, day);

	//execute the query
	sql::ResultSet* rs = ps->executeQuery();

	double dailySales = 0.0;

	while (rs->next())
	{
		std::string deliveryMethod = rs->getString(1);
		double totalSales = rs->getDouble(2);

		if (deliveryMethod == "Delivery") {
			totalSales -= 2.0;
		}

		dailySales += totalSales;
	}

	// Close resources
	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return dailySales;
}

double OrderManager::getMonthlySales(int year, int month) {
	DatabaseConnection dbConn; 

	//prepare the SQL query to get monthly sales
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DELIVERY, TOTAL_PRICE FROM OrderList WHERE YEAR(ORDER_DATE) = ? AND MONTH(ORDER_DATE) = ?");
	ps->setInt(1, year);
	ps->setInt(2, month);

	//execute the query
	sql::ResultSet* rs = ps->executeQuery();

	/*double monthlySales = 0.0;

	if (rs->next()) {
		monthlySales = rs->getDouble(1);
	}*/
	double monthlySales = 0.0;

	while (rs->next())
	{
		std::string deliveryMethod = rs->getString(1);
		double totalSales = rs->getDouble(2);

		if (deliveryMethod == "Delivery") {
			totalSales -= 2.0;
		}

		monthlySales += totalSales;
	}

	// Close resources
	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return monthlySales;
}

/*double OrderManager::getDailySales(int year, int month, int day) {
	DatabaseConnection dbConn; 

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT SUM(QUANTITY), SUM(TOTAL_PRICE) FROM OrderList WHERE YEAR(ORDER_DATE) = ? AND MONTH(ORDER_DATE) = ? AND DAY(ORDER_DATE) = ? AND MENU_ID = ?");
	ps->setInt(1, year);
	ps->setInt(2, month);
	ps->setInt(3, day);

	// Execute the query
	sql::ResultSet* rs = ps->executeQuery();

	double dailySales = 0.0;

	if (rs->next()) {
		dailySales = rs->getDouble(1);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return dailySales;
}*/

double OrderManager::SalesEachMonthbMenu(int year, int month, std::string menuID, int& totalQ) {
	DatabaseConnection dbConn;  // Assuming you have a DatabaseConnection class

	// Prepare the SQL query to get total sales and quantity sold for a specific MENU_ID on a specific date
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DELIVERY, QUANTITY, TOTAL_PRICE FROM OrderList WHERE YEAR(ORDER_DATE) = ? AND MONTH(ORDER_DATE) = ? AND MENU_ID = ?");
	ps->setInt(1, year);
	ps->setInt(2, month);
	ps->setString(3, menuID);

	sql::ResultSet* rs = ps->executeQuery();

	double menuSales = 0.0;
	totalQ = 0;

	while (rs->next())
	{
		std::string deliveryMethod = rs->getString(1);
		int quantitySold = rs->getInt(2);
		double totalSales = rs->getDouble(3);
		if (deliveryMethod == "Delivery") {
			totalSales -= 2.0;
		}
		totalQ += quantitySold;
		menuSales += totalSales;
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return menuSales;
}

double OrderManager::getDailySales(int year, int month, int day, std::string menuID, int& totalQ) {
	DatabaseConnection dbConn;  // Assuming you have a DatabaseConnection class

	// Prepare the SQL query to get total sales and quantity sold for a specific MENU_ID on a specific date
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DELIVERY, QUANTITY, TOTAL_PRICE FROM OrderList WHERE YEAR(ORDER_DATE) = ? AND MONTH(ORDER_DATE) = ? AND DAY(ORDER_DATE) = ? AND MENU_ID = ?");
	ps->setInt(1, year);
	ps->setInt(2, month);
	ps->setInt(3, day);
	ps->setString(4, menuID);

	sql::ResultSet* rs = ps->executeQuery();

	double dailySales = 0.0;
	totalQ = 0;

	while (rs->next()) 
	{
		std::string deliveryMethod = rs->getString(1);
		int quantitySold = rs->getInt(2);
		double totalSales = rs->getDouble(3);
		if (deliveryMethod == "Delivery") {
			totalSales -= 2.0;
		}
		totalQ += quantitySold;
		dailySales += totalSales;
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return dailySales;
}

double OrderManager::getMenuSales(std::string menuID) {
	DatabaseConnection dbConn; 

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DELIVERY, TOTAL_PRICE FROM OrderList WHERE MENU_ID = ?");
	ps->setString(1, menuID);

	sql::ResultSet* rs = ps->executeQuery();

	double menuSales = 0.0;

	while (rs->next()) 
	{
		std::string deliveryMethod = rs->getString(1);
		double totalSales = rs->getDouble(2);

		if (deliveryMethod == "Delivery") {
			totalSales -= 2.0;
		}

		menuSales += totalSales;
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return menuSales;
}

