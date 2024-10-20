//implementation file

//#include <mysql/jdbc.h>
//using namespace sql; 
// //if we r not using this, then we need to add sql:: infront of allmysql, Connection those things come from sql
//same goes to std
#include"DatabaseConnection.h" // this can be put in either .cpp or . put here is better
#include"MenuManager.h"

void transform(sql::ResultSet* rs, Menu* menu)
{
	menu->menu_id = rs->getString(1);
	menu->name = rs->getString(2);
	menu->description = rs->getString(3);
	menu->price = rs->getDouble(4);
	menu->status = rs->getString(5);
}

bool MenuManager::menuExists(std::string menu_id)
{
	// Assuming you have a DatabaseConnection object named dbConn
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Menu WHERE Menu_id = ?");
	ps->setString(1, menu_id);

	sql::ResultSet* rs = ps->executeQuery();

	bool exists = rs->next(); // Check if there is at least one row in the result set

	// Cleanup resources
	ps->close();
	delete ps;

	return exists;
}

//want to transform from result set, so that we no need to edit the same things many times
//coz many functions using the same things, so we hv this function then everytime we want to use, we just call transform function
//can just modify here
int MenuManager::addMenu(Menu* menu)
{
	/*sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
	sql::Connection* connection = driver->connect("tcp://localhost", "root", ""); // or use tcp://127.0.0.1:3306

	connection->setSchema("dbOFOS_Workshop1");*/
	//this dy moved to DatabaseConnection so no need to have here

	DatabaseConnection dbConn; // declare dbConn
	//from dbConn we can call preparedStatement
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Menu(Menu_ID, Name, Description, Price, Status) VALUES (?,?,?,?,?)");
	//if the menu_id is auto generated than no need to insert here

	ps->setString(1, menu->menu_id); //index always start at 1 for sql
	ps->setString(2, menu->name);
	ps->setString(3, menu->description);
	ps->setDouble(4, menu->price);
	ps->setString(5, menu->status);
	
	int numRowsaffected = ps->executeUpdate(); 
	//executeUpdate if for all insert, delete, update
	//numRowsaffected return 0 means failed to insert, 1 means succeed to insert
	//update or delete will return more than 1, 0 can be delete or update more than 1, so maybe return 2 or 3 or 4....10

	//rs->next(); //ask result to check, to go to the next line, if can return true, if cannot return false

	ps->close();
	//connection->close();
	delete ps;
	return numRowsaffected;
}
//overriding/implementing addMenu in the MenuManager

/*int MenuManager::updateMenu(Menu* menu)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Menu SET Menu_id = ?, Name = ? , Description = ? , Price = ?  WHERE Menu_id = ?");

	ps->setString(1, menu->menu_id);
	ps->setString(2, menu->name);
	ps->setString(3, menu->description);
	ps->setDouble(4, menu->price);
	
	ps->setString(5, menu->menu_id);

	int numRowsaffected = ps->executeUpdate();

	ps->close();

	delete ps;
	return numRowsaffected;
}*/

int MenuManager::updateMenu(Menu* menu)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps;

	// Build the base UPDATE query
	std::string query = "UPDATE Menu SET ";

	// Conditionally add fields to the query based on whether they are provided
	bool needsComma = false;

	if (!menu->name.empty())
	{
		query += "Name = ?";
		needsComma = true;
	}

	if (!menu->description.empty())
	{
		if (needsComma)
			query += ", ";

		query += "Description = ?";
		needsComma = true;
	}

	if (!menu->status.empty())
	{
		if (needsComma)
			query += ", ";

		query += "Status = ?";
		needsComma = true;
	}

	if (menu->price != 0.0) // Assuming 0 is not a valid price
	{
		if (needsComma)
			query += ", ";

		query += "Price = ?";
	}

	// Add the WHERE clause
	query += " WHERE Menu_id = ?";

	ps = dbConn.prepareStatement(query);

	// Bind parameters based on the provided fields
	int parameterIndex = 1;

	if (!menu->name.empty())
		ps->setString(parameterIndex++, menu->name);

	if (!menu->description.empty())
		ps->setString(parameterIndex++, menu->description);

	if (!menu->status.empty())
		ps->setString(parameterIndex++, menu->status);

	if (menu->price != 0.0)
		ps->setDouble(parameterIndex++, menu->price);

	ps->setString(parameterIndex, menu->menu_id);

	int numRowsAffected = ps->executeUpdate();

	ps->close();
	delete ps;

	return numRowsAffected;
}

int MenuManager::deleteMenu(Menu* menu)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Menu WHERE Menu_id = ?");
	//if the menu_id is auto generated than no need to insert here

	ps->setString(1, menu->menu_id); //index always start at 1 for sql

	int numRowsaffected = ps->executeUpdate();

	//rs->next(); //ask result to check, to go to the next line, if can return true, if cannot return false

	ps->close();
	//connection->close();
	delete ps;
	return numRowsaffected;
}

/*Menu* MenuManager::getPrice(std::string menu_id)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Price FROM Menu WHERE Menu_id = ?");

	ps->setString(1, menu_id); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Menu* menu = NULL;

	double price = -1.0;  // Default value if menu ID is not found

	if (rs->next())
	{
		menu = new Menu();
		menu->price = rs->getDouble("Price");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return menu;
}*/

Menu* MenuManager::getRandMenu()
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM MENU WHERE STATUS = 'AVAILABLE' ORDER BY RAND() LIMIT 1");

	sql::ResultSet* rs = ps->executeQuery();
	Menu* menu = NULL;

	if (rs->next())
	{
		menu = new Menu();
		transform(rs, menu);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return menu;

}

Menu* MenuManager::getMenu(std::string menu_id)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Menu WHERE Menu_id = ?");

	ps->setString(1, menu_id); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Menu* menu = NULL;

	if (rs->next())
	{
		menu = new Menu();
		transform(rs, menu);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return menu;
}

Menu* MenuManager::getMenuN(std::string name)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Menu WHERE Name = ?");

	ps->setString(1, name); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Menu* menu = NULL;

	if (rs->next())
	{
		menu = new Menu();

		transform(rs, menu);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return menu;
}

Menu* MenuManager::getcustMenus() //select all menu
{
	DatabaseConnection dbConn;

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Menu where status = 'available'");
	sql::ResultSet* rs = ps->executeQuery();

	Menu* menu = NULL;
	Menu* head = NULL;

	while (rs->next())
	{
		if (menu == NULL)
		{
			menu = new Menu();
			head = menu;
		}
		else
		{
			menu->next = new Menu();
			menu = menu->next;
		}
		transform(rs, menu);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Menu* MenuManager::getMenus() //select all menu
{
		DatabaseConnection dbConn;

		sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Menu");
		sql::ResultSet* rs = ps->executeQuery();

		Menu* menu = NULL;
		Menu* head = NULL;

		while (rs->next())
		{
			if (menu == NULL)
			{
				menu = new Menu();
				head = menu;
			}
			else
			{
				menu->next = new Menu();
				menu = menu->next;
			}
			transform(rs, menu);
		}

		rs->close();
		ps->close();

		delete rs;
		delete ps;

		return head;
}

Menu* MenuManager::getAllMenuID() //for total sales (is it same with get all menu?
{
	DatabaseConnection dbConn;

	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Menu");
	sql::ResultSet* rs = ps->executeQuery();

	Menu* menu = NULL;
	Menu* head = NULL;

	while (rs->next())
	{
		if (menu == NULL)
		{
			menu = new Menu();
			head = menu;
		}
		else
		{
			menu->next = new Menu();
			menu = menu->next;
		}
		transform(rs, menu);
		//menu->menu_id = rs->getString("Menu_id");
		//menu->name = rs->getString("name");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Menu* MenuManager::getMenu(double minPrice)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT FROM Menu WHERE minPrice >= ?");

	ps->setDouble(1, minPrice); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Menu* menu = NULL; //this contain the next data
	//this only store one
	//so we want to use linked list instead of array, coz using array might cause wasting or insufficient
	//allow us to store multiple menu
	Menu* head = NULL; //head contain the data we want to store

	while (rs->next())
	{
		if (menu == NULL)
		{
			menu = new Menu();//if the menu hasn't exist, then we create a new menu
			head = menu;
		}
		else
		{
			menu->next = new Menu();
			menu = menu->next;
		}
		//value of head will always be the same but value of menu will be uodated according to the rows
		menu = new Menu();

		transform(rs, menu);
	}
	//if only read 1 result, so we use while here, it will read until the end
	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return menu;
}

Menu* MenuManager::getMenus(double maxPrice)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT FROM Menu WHERE maxPrice <= ?");

	ps->setDouble(1, maxPrice); //directly provide the car id, so no need to hv arrow

	sql::ResultSet* rs = ps->executeQuery();
	Menu* menu = NULL; //this contain the next data
	//this only store one
	//so we want to use linked list instead of array, coz using array might cause wasting or insufficient
	//allow us to store multiple menu
	Menu* head = NULL; //head contain the data we want to store

	while (rs->next())
	{
		if (menu == NULL)
		{
			menu = new Menu();//if the menu hasn't exist, then we create a new menu
			head = menu;
		}
		else
		{
			menu->next = new Menu();
			menu = menu->next;
		}
		//value of head will always be the same but value of menu will be uodated according to the rows
		menu = new Menu();

		transform(rs, menu);
	}
	//if only read 1 result, so we use while here, it will read until the end
	rs->close();
	ps->close();

	delete rs;
	delete ps;
	//delete dbConn;

	return menu;
}