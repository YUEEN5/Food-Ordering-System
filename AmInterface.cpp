#include<iostream>
#include <conio.h>
#include <mysql/jdbc.h>
#include <limits>  // for numeric_limits, handling error wrong datatype
#include <regex> //for ic, phoneNum format
#include <sstream> // for std::ostringstream (menuid)
#include <chrono> //compare time
#include <ctime> //to solve unsave localtime

#include "AmInterface.h"
#include "MenuManager.h"
#include "StaffManager.h"
#include "OrderManager.h"
#include "CustManager.h"
#include "AccountManager.h"
#include "DatabaseConnection.h"

void dailySalesinMonth(int& year,int& month);

std::string generatePercentageGraph(int percentage)
{
	int asterisksCount = percentage / 10;
	std::string graph;

	for (int i = 0; i < asterisksCount; ++i)
	{
		graph += "*";
	}

	return graph;
}

void AmInterface::selectOneStaff(int staffID)
{
	//int custID;
	StaffManager staffManager;
	//std::cout << "Please enter the customer ID to view the menu." << std::endl;
	//std::cout << "\nCust ID: ";
	//std::cin >> custID;
	Staff* staff = staffManager.getStaff(staffID);
	staff->staffID = staffID;

	if (staff != NULL)
	{
		std::cout << std::endl << "Staff ID: " << staff->staffID << std::endl;
		std::cout << "Name: " << staff->name << std::endl;
		std::cout << "IC Number: " << staff->staffIC << std::endl;
		std::cout << "Phone Number: " << staff->phoneNo << std::endl;
		std::cout << "Email Address: " << staff->email << std::endl;
		std::cout << "Role: " << staff->role << std::endl << std::endl;
		std::cout << "*************************************************************************************************\n\n";
		staff = staff->next;
	}
	else
		std::cout << "Staff cannot found.";
	return;
}

void AmInterface::editPw(int staffID, int& status)
{
	AccountManager accManager;
	Account* acc = new Account();
	char o, c;
	//int status;
	std::string pw;
	bool change = false;
	do {
		std::cout << "Please insert your old password: "; //std::getline(std::cin, pw);
		while ((o = _getch()) != '\r')
		{
			if (o == '\b')
			{
				if (!pw.empty())
				{
					std::cout << "\b \b";
					pw.pop_back();
				}
			}
			else
			{
				pw += o;
				std::cout << "*";
			}
		}
		if (pw == "q" || pw == "Q")
		{	
			status == 0;
			return;
		}
		else if (accManager.pwCorrectS(pw))
		{
			//if (acc->staffID == staffID)
			//{
			acc->staffID = staffID;
			change = true;
			std::cout << "\n\nPlease insert your new password: "; //std::cin >> acc->password;
			while ((c = _getch()) != '\r')
			{
				if (c == '\b')
				{
					if (!acc->password.empty())
					{
						std::cout << "\b \b";
						acc->password.pop_back();
					}
				}
				else
				{

					acc->password += c;
					std::cout << "*";
				}
			}
			//}
			//else
		//	{
		//		std::cout << "Invalid Account. Please try again or click 'q' to cancel update." << std::endl;
		//	}
		}
		else
		{
			std::cout << "\n\nInvalid Old Password.Please try again or click 'q' to cancel update." << std::endl;	
			pw.clear();
			change = false;
		}
	} while (!change);

	int status1 = accManager.updateAccPw(acc);
	status = status1;

}

void AmInterface::editStaffProfile(int staffID)
{
	StaffManager staffManager;
	//AccountManager accManager;
	Staff* staff = new Staff();
	//Staff* staff = staffManager.getStaff(staffID);
	//Account* acc = new Account();

	//acc->staffID = staffID;
	char update, c, o, a;
	int status, success;
	bool change = false;
	std::string buffer, pw, role;
	std::cout << std::endl;
	std::cout << "*************************************************************************************************";
	std::cout << "\n                                       Update Profile";
	std::cout << "\n*************************************************************************************************";
	staff->staffID = staffID;
	//Account* acc = accManager.getAccS(staff->staffID);
	//std::cout << "\n\nCustomer ID: " << cust->custID;
	//ClrSn();
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\tProfile Details";
	std::cout << "\n*************************************************************************************************\n";
	selectOneStaff(staff->staffID);

	if (staff->staffID != 0)
	{
		std::cout << "\n\nPlease select the details of the menu that you want to update: " << std::endl;
		std::cout << "==================================================================";
		std::cout << "\n1. Name";
		std::cout << "\n2. IC Number";
		std::cout << "\n3. Role";
		std::cout << "\n4. Email address";
		std::cout << "\n5. Phone number";
		std::cout << "\n6. Password";
		std::cout << "\n7. Cancel Update";
		std::cout << "\n==================================================================";
		
		do {
			int choice;
			while (true) {
				try {
					std::cout << "\nPlease choose to update (1-7): ";
					std::cin >> choice;
					//std::cin.ignore();
					// Check if the input was successful
					if (std::cin.fail() || choice < 1 || choice > 7) {
						throw std::invalid_argument("Invalid input. Please enter a valid number. (1-7)");
					}

					// Input was successful, exit the loop
					break;
				}
				catch (const std::invalid_argument& e) {
					std::cout << e.what() << std::endl;

					// Clear the error state
					std::cin.clear();

					// Discard the invalid input
					std::cin.ignore(99, '\n');
				}
			}

			std::getline(std::cin, buffer);
			switch (choice)
			{
			case 1:
				std::cout << "Update Name: ";
				std::getline(std::cin, staff->name);
				break;
			case 2:
				do {
					std::cout << "Update IC Number (XXXXXX-XX-XXXX): ";
					std::getline(std::cin, staff->staffIC);
				} while (!std::regex_match(staff->staffIC, std::regex(R"(\d{6}-\d{2}-\d{4})")));
				//lastDigit = staff->staffIC.back() - '0';
				//staff->gender = (lastDigit % 2 == 0) ? "Female" : "Male";
				break;
			case 3:
				do {
					std::cout << "Update Role ('0' for staff role): ";

					while ((a = _getch()) != '\r')
					{
						if (a == '\b') // Check for backspace
						{
							if (!role.empty())
							{
								std::cout << "\b \b"; // Move the cursor back and erase the character
								role.pop_back();   // Remove the last character from the password
							}
						}
						else
						{
							role += a;
							std::cout << "*";
						}
					}
					if (role == "0")
					{
						staff->role = "STAFF";
					}
					else if (role == "9389")
					{
						staff->role = "ADMIN";
					}
					else
						std::cout << "Invalid input. Please try again. '0' for staff role.";
				} while (role != "9389" && role != "0");
			
				break;
			case 4:
				std::cout << "Update Email Address: ";
				std::getline(std::cin, staff->email);
				break;
			case 5:
				do {
					std::cout << "Update Phone Number (XXX-XXX XXXX): ";
					std::getline(std::cin, staff->phoneNo);
				} while (!std::regex_match(staff->phoneNo, std::regex(R"(\d{3}-\d{3} \d{4}|\d{3}-\d{4} \d{4})")));
				break;
			case 6:
				editPw(staffID, success);
				break;
			case 7:
				std::cout << "Update cancelled";
				return;
			default:
				std::cout << "Invalid choice. Please choose again.";
				return;
			}

			StaffManager staffManager; //use this to add menu to databasex
			//int status1 = accManager.updateAccPw(acc);
			if (choice != 6)
				status = staffManager.updateStaff(staff);
			else if (choice == 6)
				status = success;

			//std::cout << status1;

			if (status != 0)
				std::cout << "\nSuccessfully updated your profile." << std::endl;
			else
				std::cout << "\nSorry, unable to update your profile." << std::endl;
			std::cout << "Do you still want to update other attributes of your profile? (Y/N): ";
			std::cin >> update;
			std::cin.ignore(); //so that this won't bring to the next quetion
		} while (update == 'y' || update == 'Y');
	}
	else std::cout << "Staff not found";

	std::cout << "*************************************************************************************************";
	std::cout << "  \n                                Updated Profile Details";
	std::cout << "\n*************************************************************************************************\n";
	selectOneStaff(staffID);
	system("pause");
	return;
}

void AmInterface::viewAllStaff()
{
	StaffManager staffManager;
	Staff* staffs = staffManager.getStaffs();

	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\tStaff List";
	std::cout << "\n*************************************************************************************************";
	if (staffs != NULL)
	{
		Staff* staff = staffs;
		do
		{
			std::cout << std::endl << "Staff ID: " << staff->staffID << std::endl;
			std::cout << "Name: " << staff->name << std::endl;
			std::cout << "IC Number: " << staff->staffIC << std::endl;
			std::cout << "Phone Number: " << staff->phoneNo << std::endl;
			std::cout << "Email Address: " << staff->email << std::endl;
			std::cout << "Role: " << staff->role << std::endl;
			staff = staff->next;
		} while (staff != NULL);

	}
	else
		std::cout << "\nSorry, no customer found." << std::endl;
	std::cout << "\n*************************************************************************************************";
}

void AmInterface::deleteS()
{
	Staff* staff = new Staff();
	Account* acc = new Account();
	StaffManager staffManager;
	AccountManager accManager;
	do {
		viewAllStaff();
		std::cout << "\n*************************************************************************************************";
		std::cout << "\n                                       Delete Staff";
		std::cout << "\n*************************************************************************************************";
		std::cout << "\nClick '0' to go back to Main Menu. " << std::endl << std::endl;
		while (true)
		{
			try {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				std::cout << "\nPlease enter the staff ID that you want to delete: ";
				std::cin >> staff->staffID;
				acc->staffID = staff->staffID;

				if (std::cin.fail()) {
					std::cerr << "Invalid input. Please enter a valid number." << std::endl;

					// Clear the error state
					std::cin.clear();

					// Discard the invalid input
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;  // Continue the loop after handling the error
				}
				if (staff->staffID == 0)
				{
					return;
				}
				break;
			}
			catch (const std::exception& e) {
				// Catch and display any exceptions that might occur
				std::cerr << "\n\nError: " << e.what() << std::endl;
				// Cleanup memory
				delete staff;
			}
		}
		if (staffManager.staffExists(staff->staffID))//staff exists
		{
			int status2 = accManager.deleteAccS(acc);
			int status = staffManager.deleteStaff(staff);
			if (status != 0 && status2 != 0) {
				std::cout << "Successfully deleted the staff" << std::endl;
			}
			else {
				std::cout << "Unable to delete the staff. There is no staff with staff ID " << staff->staffID << std::endl;
			}

		}
		else
		{
			std::cout << "Staff not found" << std::endl;
			system("pause");
		}
	} while (!staffManager.staffExists(staff->staffID));
}

void AmInterface::viewMenu()
{
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\tLucky's Food Menu";
	std::cout << "\n*************************************************************************************************";
	MenuManager menuManager;
	Menu* menus = menuManager.getMenus();

	if (menus != NULL) //menu exists
	{
		Menu* menu = menus;
		do
		{
			std::cout << std::endl << "Menu ID: " << menu->menu_id << std::endl;
			std::cout << "Menu Name: " << menu->name << std::endl;
			std::cout << "Menu Description: " << menu->description << std::endl;
			std::cout << "Menu Price: " << menu->price << std::endl;
			std::cout << "Menu Status: " << menu->status << std::endl;
			menu = menu->next;
		} while (menu != NULL);

	}
	else
		std::cout << "\nSorry, no menu found." << std::endl;
	std::cout << "\n*************************************************************************************************\n\n";
}

void AmInterface::addNewMenu()
{
	std::cout << "*************************************************************************************************";
	std::cout << "\n                                       Add Menu";
	std::cout << "\n*************************************************************************************************";
	std::cout << "\nClick 'q' to go back to Main Menu. " << std::endl << std::endl;
	Menu* menu = new Menu();
	std::string buffer;
	char able;
	std::getline(std::cin, buffer);
	try {
		std::cout << "\nMenu ID: ";
		std::getline(std::cin, menu->menu_id);
		if (menu->menu_id == "q" || menu->menu_id == "Q") {
			return;
		}
		std::cout << "Menu name: ";
		std::getline(std::cin, menu->name);

		std::cout << "Menu description: ";
		std::getline(std::cin, menu->description);

		//error handling for price (int only)
		while (true) {
			try {
				std::cout << "Menu price: ";
				std::cin >> menu->price;
				std::cin.ignore();
				// Check if the input was successful
				if (std::cin.fail()) {
					throw std::invalid_argument("Invalid input. Please enter a valid number.");
				}

				// Input was successful, exit the loop
				break;
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what() << std::endl;

				// Clear the error state
				std::cin.clear();

				// Discard the invalid input
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		do {
			std::cout << "Status (A = Availaibble / U = Unavailable): ";
			std::cin >> able;
			if (able == 'A' || able == 'a')
			{
				menu->status = "AVAILABLE";
			}
			else if (able == 'U' || able == 'u')
			{
				menu->status = "UNAVAILABLE";
			}
			else
				std::cout << "Invalid input. Please type A or U only.";
		} while (able != 'A' && able != 'a' && able != 'U' && able != 'u');

		MenuManager menuManager; //use this to add menu to database
		int status = menuManager.addMenu(menu);
	if (status != 0)
		std::cout << "Successfully added a new menu" << std::endl;
	else
		std::cout << "Unable to add a new menu" << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << "\n\nError: " << e.what() << std::endl;
		delete menu;  // Delete the allocated menu in case of an error
		//return 0;     // Return an appropriate error code
	}
}

#include <iostream>
#include <limits>  // Required for numeric_limits

void AmInterface::deleteM() 
{
	Menu* menu = new Menu();
	MenuManager menuManager;
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n                                       Delete Menu";
	std::cout << "\n*************************************************************************************************";
	std::cout << "\nClick 'q' to go back to Main Menu. " << std::endl << std::endl;
	while (true) {
		try {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "\nPlease enter the menu ID that you want to delete: ";
			std::getline(std::cin, menu->menu_id);
			if (menu->menu_id == "q" || menu->menu_id == "Q") {
				return;
			}
			else if (menuManager.menuExists(menu->menu_id))//menu exists
			{
				int status = menuManager.deleteMenu(menu);

				if (status != 0) {
					std::cout << "Successfully deleted the menu" << std::endl;
				}
				else {
					std::cout << "Unable to delete the menu. There is no menu with menu ID " << menu->menu_id << std::endl;
				}
			}
			else
				std::cout << "Menu not found";
		}
		catch (const std::exception& e) {
			// Catch and display any exceptions that might occur
			std::cerr << "\n\nError: " << e.what() << std::endl;
			// Cleanup memory
			delete menu;
		}
	}

}


void AmInterface::updateM()
{
	MenuManager menuManager;
	Menu* menu = new Menu();
	char update, able;
	std::string buffer;
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n                                       Update Menu";
	std::cout << "\n*************************************************************************************************";
	std::cout << "\nClick 'q' to go back to Main Menu. " << std::endl << std::endl;
	try {
		do {
			std::cout << "\nMenu ID: ";
			std::cin >> menu->menu_id;
			//no need use if(menu !=NULL) it will always correct coz got the code new Menu()
			if (menu->menu_id == "q" || menu->menu_id == "Q") {
				return;
			}
			else if (menuManager.menuExists(menu->menu_id)) // Check if the menu exists
			{
				std::cout << "Please select the details of the menu that you want to update: " << std::endl;
				std::cout << "==================================================================";
				std::cout << "\n1. Name";
				std::cout << "\n2. Description";
				std::cout << "\n3. Price";
				std::cout << "\n4. Status";
				std::cout << "\n5. Cancel update";
				std::cout << "\n==================================================================";
				int choice;
				std::getline(std::cin, buffer);
				do {
					while (true) {
						try {
							std::cout << "\nPlease choose to update (1-5): ";
							std::cin >> choice;
							//clear the input
							std::cin.ignore();
							// Check if the input was successful
							if (std::cin.fail() || choice < 1 || choice > 5) {
								throw std::invalid_argument("Invalid input. Please enter a valid number. (1-5)");
							}

							// Input was successful, exit the loop
							break;
						}
						catch (const std::invalid_argument& e) {
							std::cout << e.what() << std::endl;

							// Clear the error state
							std::cin.clear();

							// Discard the invalid input
							std::cin.ignore(9999, '\n');
						}
					}
					switch (choice)
					{
					case 1:
						std::cout << "Update Menu Name: ";
						std::getline(std::cin, menu->name);
						break;
					case 2:
						std::cout << "Update Menu Description: ";
						std::getline(std::cin, menu->description);
						break;
					case 3:
						while (true) {
							try {
								std::cout << "\nUpdate Menu Price: ";
								std::cin >> menu->price;
								std::cin.ignore();
								// Check if the input was successful
								if (std::cin.fail()) {
									throw std::invalid_argument("Invalid input. Please enter a valid number.");
								}

								// Input was successful, exit the loop
								break;
							}
							catch (const std::invalid_argument& e) {
								std::cout << e.what() << std::endl;

								// Clear the error state
								std::cin.clear();

								// Discard the invalid input
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
						}
						break;
					case 4:
						do {
							std::cout << "\nUpdate Status (A = Availaibble / U = Unavailable): ";
							std::cin >> able;
							if (able == 'A' || able == 'a')
							{
								menu->status = "AVAILABLE";
							}
							else if (able == 'U' || able == 'u')
							{
								menu->status = "UNAVAILABLE";
							}
							else
								std::cout << "Invalid input. Please type A or U only.";
						} while (able != 'A' && able != 'a' && able != 'U' && able != 'u');
						break;
					case 5:
						std::cout << "Update cancelled";
						return;
					default:
						std::cout << "Invalid choice. Please choose again.";
						return;
					}

					MenuManager menuManager; //use this to update menu to databasex
					int status = menuManager.updateMenu(menu);

					if (status != 0)
					{
						std::cout << "Successfully updated the menu." << std::endl;
					}
					else
					{
						std::cout << "Unable to update the menu." << std::endl;
					}
					do {
						std::cout << "\nDo you still want to update other attributes of " << menu->menu_id << " ? (Y/N): ";
						std::cin >> update;
					} while (update != 'y' && update != 'Y' && update != 'n' && update != 'N');
				} while (update == 'y' || update == 'Y');
			}
			else std::cout << "Menu not found";
		} while (!menuManager.menuExists(menu->menu_id));
	}
	catch (const std::exception& e) {
		std::cerr << "\n\nError: " << e.what() << std::endl;
		delete menu;
	}
}

void AmInterface::viewAllCustID()
{
	CustManager custManager;
	Customer* custs = custManager.getCusts();

	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\tCustomer List";
	std::cout << "\n*************************************************************************************************\n";
	std::cout << "Customer ID " << std::setw(20)
		<< "Name " << std::setw(30)
		<< "IC Number " << std::setw(20)
		<< "Phone Number ";
	std::cout << "\n*************************************************************************************************";
	if (custs != NULL)
	{
		Customer* cust = custs;
		do
		{
			std::cout << std::endl << std::setw(5) <<  cust->custID << std::setw(25)
			<< cust->name << std::setw(30)
			<< cust->custIC << std::setw(20)
			<< cust->phoneNo;
			cust = cust->next;
		} while (cust != NULL);

	}
	else
		std::cout << "\nSorry, no customer found." << std::endl;
	std::cout << "\n*************************************************************************************************";
}

void AmInterface::viewCust()
{
	CustManager custManager;
	Customer* custs = custManager.getCusts();

	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\tCustomer List";
	std::cout << "\n*************************************************************************************************";
	if (custs != NULL)
	{
		Customer* cust = custs;
		do
		{
			std::cout << std::endl << "Customer ID: " << cust->custID << std::endl;
			std::cout << "Name: " << cust->name << std::endl;
			std::cout << "IC Number: " << cust->custIC << std::endl;
			std::cout << "Phone Number: " << cust->phoneNo << std::endl;
			std::cout << "Email Address: " << cust->email << std::endl;
			std::cout << "Address: " << cust->address << std::endl;
			std::cout << "Gender: " << cust->gender << std::endl;
			cust = cust->next;
		} while (cust != NULL);

	}
	else
		std::cout << "\nSorry, no customer found." << std::endl;
	std::cout << "\n*************************************************************************************************";
}

void AmInterface::deleteC()
{
	CustManager custManager;
	AccountManager accManager;
	Customer* cust = new Customer();
	Account* acc = new Account();
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\tDelete Customer";
	std::cout << "\n*************************************************************************************************";
	std::cout << "\nClick '0' to go back to Main Menu. " << std::endl << std::endl;
	do {
		while (true) {
			try {
				std::cout << "\nPlease enter the customer ID that you want to delete: "; std::cin >> cust->custID;
				acc->custID = cust->custID;

				if (std::cin.fail()) {
					std::cerr << "Invalid input. Please enter a valid number." << std::endl;

					// Clear the error state
					std::cin.clear();

					// Discard the invalid input
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;  // Continue the loop after handling the error
				}
				if (cust->custID == 0)
				{
					return;
				}


				break;
			}
			catch (const std::exception& e) {
				// Catch and display any exceptions that might occur
				std::cerr << "Error: " << e.what() << std::endl;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
				if (custManager.custExists(cust->custID))//menu exists 
				{
					int status1 = accManager.deleteAccC(acc);
					int status = custManager.deleteCust(cust);
					if (status != 0 && status1 != 0) {
						std::cout << "Successfully deleted the customer" << std::endl;
					}
					else {
						std::cout << "Unable to delete the customer. There is no customer with customer ID " << cust->custID << std::endl;
					}
					break;
				}
				else
					std::cout << "Customer not found";
	} while (!custManager.custExists(cust->custID));
	// Cleanup memory
	//delete cust;
}

void AmInterface::viewOrders()
{
	OrderManager orderManager;
	OrderList* orders = orderManager.getOrders();
	MenuManager menuManager;

	std::cout << "\n*********************************************************************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\t\t\t\t\tOrder List";
	std::cout << "\n*********************************************************************************************************************************************************";

	if (orders != NULL) {
		OrderList* order = orders;
	std::cout << "\n" << std::setw(8) << "Order ID" << std::setw(8) << "Cust ID" << std::setw(8) << "Menu ID"
		<< std::setw(22) << "Food Name" << std::setw(9) << "Quantity" << std::setw(7) << "Price"
		<< std::setw(21) << "Order Date" << std::setw(10) << "P/D" << std::setw(16) << "Payment Method" << std::setw(40) << "Delievery Address";
	std::cout << "\n*********************************************************************************************************************************************************";
		do
		{
			std::cout << "\n"  << std::setw(8) << order->orderID << std::setw(8) << order->custID << std::setw(8) << order->menuID;
			Menu* menu = menuManager.getMenu(order->menuID);
			std::cout << std::setw(22) << menu->name << std::setw(9) << order->quantity << std::setw(7) << order->tPrice
				<< std::setw(21) << order->oDateTime << std::setw(10) << order->delivery << std::setw(16) << order->payMethod << std::setw(40) << order->address;
			order = order->next;
		} while (order != NULL);
	}
	else
		std::cout << "\nNo order found!";
	std::cout << "\n*********************************************************************************************************************************************************";
}


void AmInterface::selectOneMenu()
{
	std::string menu_id;
	MenuManager menuManager;
	std::cout << "Please enter the menu ID to view the menu." << std::endl;
	std::cout << "\nMenu ID: ";
	std::cin >> menu_id;
	Menu* menu = menuManager.getMenu(menu_id);
	std::cout << "*************************************************************************************************";
	std::cout << "  \n                                   Menu Details";
	std::cout << "\n*************************************************************************************************";
	if (menuManager.menuExists(menu_id)) //menu exists
	{
		std::cout << "\nMenu ID: " << menu->menu_id << std::endl
			<< "Menu Name: " << menu->name << std::endl
			<< "Menu Description: " << menu->description << std::endl
			<< "Menu Price: " << menu->price << std::endl;
	}
	else
		std::cout << "Menu cannot found." << std::endl;
}

void AmInterface::SignUpStaff(int& staffID)
{
	DatabaseConnection dbConn;
	Staff* staff = new Staff();
	Account* acc = new Account();
	std::string buffer, UN, role;
	bool repeated;
	char c, a;
	std::getline(std::cin, buffer);

	sql::PreparedStatement* psSelect = dbConn.prepareStatement("SELECT MAX(Staff_id) AS MaxID FROM Staff");
	int maxID = 0;
	sql::ResultSet* rs = psSelect->executeQuery();

	if (rs->next()) {
		maxID = rs->getInt("MaxID");
	}

	int startingID = std::max(maxID + 1, 50001);

	staff->staffID = startingID;
	staffID = startingID;
	rs->close();
	delete rs;

	std::cout << "\nStaff ID:" << staff->staffID << std::endl;
	
		do {
			std::cout << "Ic Number (XXXXXX-XX-XXXX): ";
			std::getline(std::cin, staff->staffIC);
		} while (!std::regex_match(staff->staffIC, std::regex(R"(\d{6}-\d{2}-\d{4})")));
	
	std::cout << "Name: ";
	std::getline(std::cin, staff->name);

	do{
	std::cout << "Phone Number (XXX-XXX XXXX): ";
	std::getline(std::cin, staff->phoneNo);
	} while (!std::regex_match(staff->phoneNo, std::regex(R"(\d{3}-\d{3} \d{4}|\d{3}-\d{4} \d{4})")));

	std::cout << "Email: ";
	std::getline(std::cin, staff->email);

	do
	{
		std::cout << "Role (click '0' for staff): ";
		//std::cin >> role;
		while ((a = _getch()) != '\r')
		{
			if (a == '\b') // Check for backspace
			{
				if (!role.empty())
				{
					std::cout << "\b \b"; // Move the cursor back and erase the character
					role.pop_back();   // Remove the last character from the password
				}
			}
			else
			{
				role += a;
				std::cout << "*";
			}
		}
		if (role == "0")
		{
			staff->role = "STAFF";
		}
		else if (role == "9389")
		{
			staff->role = "ADMIN";
		}
		else
			std::cout << "Invalid input. Please try again. '0' for staff role.";
		//std::getline(std::cin, staff->role);
	} while (role != "0" && role != "9389");

	StaffManager staffManager;
	int status1 = staffManager.addStaff(staff);

	if (status1 != 0)
		std::cout << "\nSuccessfully signed up" << std::endl;
	else
		std::cout << "\nUnable to sign up" << std::endl;

	std::cout << "\nPlease enter your username and password for everytime log in:" << std::endl;
	acc->staffID = staff->staffID;
	acc->adminRole = 1;
	do {
		do {
			std::cout << "\nUsername: ";
			std::getline(std::cin, UN);
			if (UN.length() < 5) {
				std::cout << "\nUsername should have at least 5 characters.";
			}
		} while (UN.length() < 5);
		sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
		sql::Connection* connection = driver->connect("tcp://127.0.0.1::3306", "root", ""); // or use tcp://127.0.0.1:3306

		connection->setSchema("fos_ws1");

		sql::PreparedStatement* ps = connection->prepareStatement("SELECT * FROM ACCOUNT WHERE USERNAME = ?");

		ps->setString(1, UN); //index always start at 1 for sql

		sql::ResultSet* rs = ps->executeQuery(); //resultset is tabulate format
		//check if the same

		//rs->next(); //ask result to check, to go to the next line, if can return true, if cannot return false

		if (rs->next())
		{
			std::cout << "The user name exist already. Please try another user name.";
			repeated = true;
		}
		else
		{
			// Clear entered username and password for the next attempt using empty string
			//UN = "";
			//PW = "";
			acc->userName = UN;
			//acc->password = PW;

			repeated = false;
		}
	} while (repeated);

	std::cout << "Password: ";
	while ((c = _getch()) != '\r')
	{
		if (c == '\b')
		{
			if (!acc->password.empty())
			{
				std::cout << "\b \b";
				acc->password.pop_back();   
			}
		}
		else
		{
			acc->password += c;
			std::cout << "*";
		}
	}

	sql::PreparedStatement* psSelectA = dbConn.prepareStatement("SELECT MAX(ACCOUNT_ID) AS aMaxID FROM Account");
	int aMaxID = 0;
	sql::ResultSet* rss = psSelectA->executeQuery();

	if (rss->next()) {
		aMaxID = rss->getInt("aMaxID");
	}

	int startingAccID = std::max(aMaxID + 1, 100001);

	acc->accID = startingAccID;
	rss->close();
	delete rss;

	AccountManager accManager;

	int status2 = accManager.addAccS(acc);

	if (status2 != 0)
		std::cout << "\nSuccessfully signed up for log in" << std::endl;
	else
		std::cout << "\nUnable to sign up for log in" << std::endl;
}

void AmInterface::TodaySalesReport()
{
	OrderManager orderManager;

	//OrderList* order = orderManager.getOrders();
	std::cout << "\n************************************************************************************************************";
	std::cout << "\n\t\t\t\t\tToday's Sales";
	std::cout << "\n************************************************************************************************************";
	std::cout << std::endl << setw(10) << "Menu ID" << setw(28) << "Menu Name" << setw(15) << "Total sales";
	std::cout << "\n************************************************************************************************************";
	MenuManager menuManager;
	Menu* menus = menuManager.getMenus();

	if (menus != NULL) //menu exists
	{
		Menu* menu = menus;
		do
		{
			std::cout << std::endl << menu->menu_id;
			std::cout << setw(28) << menu->name;
			int quantity = 0;

			OrderList* orders = orderManager.getOrders();

			if (orders != NULL)
			{
				OrderList* order = orders;
				do
				{
					std::tm storedTime = {};
					std::istringstream dateTimeStream(order->oDateTime);
					dateTimeStream >> std::get_time(&storedTime, "%Y-%m-%d %H:%M:%S");

					if (dateTimeStream.fail()) {
						std::cerr << "Failed to parse the stored date string." << std::endl;
						//return true;
					}

					// Get the current date
					auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					std::tm localTime;

					localtime_s(&localTime, &currentTime);

					//std::cout << storedTime.tm_year << " " << localTime.tm_year << storedTime.tm_mon << " " << localTime.tm_mon << storedTime.tm_mday << " " << localTime.tm_mday;
					// Compare only the year, month, and day components
					if (storedTime.tm_year == localTime.tm_year && storedTime.tm_mon == localTime.tm_mon &&
						storedTime.tm_mday == localTime.tm_mday)
					{
						//std::cout << "Today sales Date: " << std::put_time(&storedTime, "%Y-%m-%d") << std::endl;
						if (order->menuID == menu->menu_id)
						{
							quantity = quantity + order->quantity;
						}
						//order = order->next;
					}
					order = order->next;
				} while (order != NULL);
			}
			else
				std::cout << "\nNo order found";
			std::cout << setw(10) << quantity;
			menu = menu->next;
		} while (menu != NULL);
		std::cout << "\n************************************************************************************************************";
	}
	else
		std::cout << "\nSorry, no menu found." << std::endl;
}
void AmInterface::TodayOrders()
{
	OrderManager orderManager;

	//OrderList* order = orderManager.getOrders();
	std::cout << "\n***********************************************************************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\t\t\tToday's Orders";
	std::cout << "\n***********************************************************************************************************************************************************";
	std::cout << "\n" << std::setw(9) << "Order ID" << std::setw(9) << "Cust ID" << std::setw(8) << "Menu ID"
		<< std::setw(22) << "Food Name" << std::setw(9) << "Quantity" << std::setw(8) << "Price"
		<< std::setw(18) << "PickUp/Delivery" << std::setw(20) << "Payment Method" << std::setw(38) << "Delievery Address";
	std::cout << "\n***********************************************************************************************************************************************************";
	MenuManager menuManager;
	Menu* menus = menuManager.getMenus();

	/*if (menus != NULL) //menu exists
	{
		Menu* menu = menus;
		do
		{
			std::cout << std::endl << menu->menu_id;
			std::cout << setw(28) << menu->name;
			int quantity = 0;*/

			OrderList* orders = orderManager.getOrders();

			if (orders != NULL)
			{
				OrderList* order = orders;
				do
				{
					std::tm storedTime = {};
					std::istringstream dateTimeStream(order->oDateTime);
					dateTimeStream >> std::get_time(&storedTime, "%Y-%m-%d %H:%M:%S");

					if (dateTimeStream.fail()) {
						std::cerr << "Failed to parse the stored date string." << std::endl;
						//return true;
					}

					// Get the current date
					auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					std::tm localTime;

					localtime_s(&localTime, &currentTime);

					//std::cout << storedTime.tm_year << " " << localTime.tm_year << storedTime.tm_mon << " " << localTime.tm_mon << storedTime.tm_mday << " " << localTime.tm_mday;
					// Compare only the year, month, and day components
					if (storedTime.tm_year == localTime.tm_year && storedTime.tm_mon == localTime.tm_mon &&
						storedTime.tm_mday == localTime.tm_mday)
					{
						//std::cout << "Today sales Date: " << std::put_time(&storedTime, "%Y-%m-%d") << std::endl;
						std::cout << "\n" << std::setw(9) << order->orderID << std::setw(9) << order->custID << std::setw(8) << order->menuID;
						Menu* menu = menuManager.getMenu(order->menuID);
						std::cout << std::setw(22) << menu->name << std::setw(9) << order->quantity << std::setw(8) << order->tPrice
							 << std::setw(18) << order->delivery << std::setw(20) << order->payMethod << std::setw(38) << order->address;
						//order = order->next;
					}
					order = order->next;
				} while (order != NULL);
			}
			else
				std::cout << "\nNo order found";
			//std::cout << setw(10) << quantity;
			//menu = menu->next;
		//} while (menu != NULL);
		std::cout << "\n***********************************************************************************************************************************************************";
	//}
	//else
	//	std::cout << "Sorry, no menu found." << std::endl;
}

bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}


bool isValidDate(int year, int month) {
	// Get the current time
	std::time_t currentTime = std::time(nullptr);
	std::tm currentLocalTime;

	// Use localtime_s for safer local time retrieval
	if (localtime_s(&currentLocalTime, &currentTime) != 0) {
		// Error handling: Unable to retrieve local time
		return false;
	}

	// Check if the entered date is not in the future
	if (year > currentLocalTime.tm_year + 1900 ||
		(year == currentLocalTime.tm_year + 1900 && month > currentLocalTime.tm_mon + 1)) {
		return false;
	}

	// Check if the month and day are within valid ranges
	return (month >= 1 && month <= 12);
}

bool isValidDate(int year, int month, int day) {
	// Get the current time
	std::time_t currentTime = std::time(nullptr);
	std::tm currentLocalTime;

	// Use localtime_s for safer local time retrieval
	if (localtime_s(&currentLocalTime, &currentTime) != 0) {
		// Error handling: Unable to retrieve local time
		return false;
	}

	// Check if the entered date is not in the future
	if (year > currentLocalTime.tm_year + 1900 ||
		(year == currentLocalTime.tm_year + 1900 && month > currentLocalTime.tm_mon + 1) ||
		(year == currentLocalTime.tm_year + 1900 && month == currentLocalTime.tm_mon + 1 && day > currentLocalTime.tm_mday)) {
		return false;
	}

	// Check for valid month and day values based on month length
	if (month == 2) {
		// February: Handle leap year
		int maxDays = (isLeapYear(year)) ? 29 : 28;
		return day >= 1 && day <= maxDays;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		// Months with 30 days
		return day >= 1 && day <= 30;
	}
	else {
		// Months with 31 days
		return day >= 1 && day <= 31;
	}
	// Check if the month and day are within valid ranges
	//return (month >= 1 && month <= 12) && (day >= 1 && day <= 31);
}


void AmInterface::DailySales()
{
	OrderManager orderManager;
	int year, month, day;
	char again;
	do {
		std::system("cls");
		std::cout << "\n************************************************************************************************************";
		std::cout << "\n\t\t\t\t\tDaily Sales";
		std::cout << "\n************************************************************************************************************";
		std::cout << "\nClick '0' to go back to Main Menu. " << std::endl << std::endl;
		while (true) {

			try {
				std::cout << "\nPlease enter the date (YYYY MM DD): ";
				
				// Read each integer value separately for better control
				std::cin >> year;
				if (std::cin.fail()) {
					throw std::invalid_argument("Invalid year. Please enter a valid integer.");
				}
				if (year == 0)
				{
					return;
				}
				std::cin >> month;
				if (std::cin.fail()) {
					throw std::invalid_argument("Invalid month. Please enter a valid integer.");
				}
				std::cin >> day;
				if (std::cin.fail()) {
					throw std::invalid_argument("Invalid day. Please enter a valid integer.");
				}
				
				// Check for valid date format and range
				if (!isValidDate(year, month, day)) {
					throw std::invalid_argument("Invalid date or date in the future. Please enter a valid date in the YYYY MM DD format.");
				}

				break; // Valid date, exit the loop


			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what() << std::endl;

				//clear the error state
				std::cin.clear();

				//discard the invalid input
				std::cin.ignore(999, '\n');
		}
		}

		std::cout << "\n************************************************************************************************************";
		std::cout << "\n\t\t\t\t\tSales for " << year << "-" << month << "-" << day;
		std::cout << "\n************************************************************************************************************";
		std::cout << std::endl << setw(10) << "Menu ID" << setw(28) << "Menu Name" << setw(20) << "Total Quantity" << setw(20) << "Total sales (RM)" << std::setw(25) << "Sales Percentage (%)";
		std::cout << "\n************************************************************************************************************";
		MenuManager menuManager;
		Menu* menus = menuManager.getMenus();

		if (menus != NULL) //menu exists
		{
			Menu* menu = menus;
			int max = 0;
			double maxPrice = 0.0;
			std::string mostPopularMenu, name;

			double totalSales = 0.0;

			do
			{
				int quantitySold;
				double sales = orderManager.getDailySales(year, month, day, menu->menu_id, quantitySold);
				totalSales += sales;
				menu = menu->next;
			} while (menu != NULL);

			// Reset menu pointer for the second loop
			menu = menus;

			do
			{
				std::cout << std::endl << setw(10) << menu->menu_id;
				std::cout << setw(28) << menu->name;
				int quantitySold;
				
				double sales = orderManager.getDailySales(year, month, day, menu->menu_id, quantitySold);
				std::cout << setw(20) << quantitySold << setw(20) << sales;
				if (totalSales != 0)
				{
					double salesPercentage = (sales / totalSales) * 100;
					std::cout << std::setw(25) << std::fixed << std::setprecision(2) << salesPercentage;
				}
				//int roundedPercentage = static_cast<int>(std::round(salesPercentage));
				//std::cout << std::setw(20) << generatePercentageGraph(roundedPercentage);

				if (quantitySold > max)
				{
					max = quantitySold;
					mostPopularMenu = menu->menu_id;
					name = menu->name;
					maxPrice = sales;
				}

				menu = menu->next;
			} while (menu != NULL);

			std::cout << "\n************************************************************************************************************";
			if (!mostPopularMenu.empty())
			{
				std::cout << "\n\nThe Most PoPular Menu on this day: " << name << std::endl << "Menu ID: " << mostPopularMenu;
				std::cout << "\nTotal Quantity Sold: " << max << std::endl << "Total sales: RM " << maxPrice << std::endl;
				std::cout << "\n************************************************************************************************************";
			}
			else
				std::cout << "\nNo sales on this day" << std::endl;
		}
		else
			std::cout << "\nSorry, no menu found." << std::endl;
		do
		{
			std::cout << "\nDo you want to view daily report in other days? (Y/N): "; std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'n' && again != 'N');
		//std::system("cls");
	}while (again == 'Y' || again == 'y');
}

void AmInterface::chooseMonthlySales()
{
	OrderManager orderManager;
	std::string monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	char again, details;
	int month, year;
	std::system("cls");
	std::system("cls");
	std::cout << "\n************************************************************************************************************";
	std::cout << "\n\t\t\t\t\tMonthly Sales";
	std::cout << "\n************************************************************************************************************";
	std::cout << "\nClick '0' to go back to Main Menu. " << std::endl << std::endl;
	while (true) {

		try {
			std::cout << "\nPlease enter the date (YYYY MM): ";

			// Read each integer value separately for better control
			std::cin >> year;
			if (std::cin.fail()) {
				throw std::invalid_argument("Invalid year. Please enter a valid integer.");
			}
			if (year == 0)
			{
				return;
			}
			std::cin >> month;
			if (std::cin.fail()) {
				throw std::invalid_argument("Invalid month. Please enter a valid integer.");
			}

			// Check for valid date format and range
			if (!isValidDate(year, month)) {
				throw std::invalid_argument("Invalid date or date in the future. Please enter a valid date in the YYYY MM DD format.");
			}

			break; // Valid date, exit the loop

		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;

			//clear the error state
			std::cin.clear();

			//discard the invalid input
			std::cin.ignore(999, '\n');
		}
	}
	std::cout << "\n************************************************************************************************************";
	std::cout << "\n\t\t\t\t\tSales in " << monthNames[month - 1] << " of " << year;
	std::cout << "\n************************************************************************************************************";
	std::cout << std::endl << setw(10) << "Menu ID" << setw(28) << "Menu Name" << setw(20) << "Total Quantity" << setw(20) << "Total sales (RM)" << std::setw(20) << "Sales Percentage (%)";
	std::cout << "\n************************************************************************************************************";
	MenuManager menuManager;
	Menu* menus = menuManager.getMenus();

	if (menus != NULL) //menu exists
	{
		Menu* menu = menus;
		int max = 0;
		double maxPrice = 0.0;
		std::string mostPopularMenu, name;

		double totalSales = 0.0;

		do
		{
			int quantitySold;
			double sales = orderManager.SalesEachMonthbMenu(year, month, menu->menu_id, quantitySold);
			totalSales += sales;

			menu = menu->next;
		} while (menu != NULL);

		menu = menus;

		do
		{
			std::cout << std::endl << setw(10) << menu->menu_id;
			std::cout << setw(28) << menu->name;
			int quantitySold;

			double sales = orderManager.SalesEachMonthbMenu(year, month, menu->menu_id, quantitySold);
			std::cout << setw(20) << quantitySold << setw(20) << sales;
			if (totalSales != 0)
			{
				double salesPercentage = (sales / totalSales) * 100;
				std::cout << std::setw(20) << std::fixed << std::setprecision(2) << salesPercentage;
			}
			//int roundedPercentage = static_cast<int>(std::round(salesPercentage));
			//std::cout << std::setw(20) << generatePercentageGraph(roundedPercentage);

			if (quantitySold > max)
			{
				max = quantitySold;
				mostPopularMenu = menu->menu_id;
				name = menu->name;
				maxPrice = sales;
			}

			menu = menu->next;
		} while (menu != NULL);

		std::cout << "\n************************************************************************************************************";
		if (!mostPopularMenu.empty())
		{
			std::cout << "\n\nThe Most PoPular Menu in this month: " << name << std::endl << "Menu ID: " << mostPopularMenu << std::endl;
			std::cout << "Total Quantity Sold: " << max << std::endl << "Total sales: RM " << maxPrice << std::endl;
			std::cout << "\n************************************************************************************************************";
		}
		else
			std::cout << "\nNo sales on this month" << std::endl;
	}
	else
		std::cout << "\nSorry, no menu found." << std::endl;
	std::cout << std::endl;
	system("pause");
	do {
		std::cout << "Do you want to view daily sales in this month? (Y/N): "; std::cin >> details;
		if (details == 'Y' || details == 'y')
		{
			dailySalesinMonth(year, month);
		}
	} while (details != 'Y' && details != 'y' && details != 'N' && details != 'n');
}

void MonthlySales(int& year, int& month)
{
	OrderManager orderManager;
	std::string monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	char again;
		std::system("cls");
	
		std::cout << "\n************************************************************************************************************";
		std::cout << "\n\t\t\t\t\tSales in " << monthNames[month-1] << " of " << year;
		std::cout << "\n************************************************************************************************************";
		std::cout << std::endl << setw(10) << "Menu ID" << setw(28) << "Menu Name" << setw(20) << "Total Quantity" << setw(20) << "Total sales (RM)" << std::setw(20) << "Sales Percentage (%)";
		std::cout << "\n************************************************************************************************************";
		MenuManager menuManager;
		Menu* menus = menuManager.getMenus();

		if (menus != NULL) //menu exists
		{
			Menu* menu = menus;
			int max = 0;
			double maxPrice = 0.0;
			std::string mostPopularMenu, name;

			double totalSales = 0.0;

			do
			{
				int quantitySold;
				double sales = orderManager.SalesEachMonthbMenu(year, month, menu->menu_id, quantitySold);
				totalSales += sales;

				menu = menu->next;
			} while (menu != NULL);

			menu = menus;

			do
			{
				std::cout << std::endl << setw(10) << menu->menu_id;
				std::cout << setw(28) << menu->name;
				int quantitySold;

				double sales = orderManager.SalesEachMonthbMenu(year, month, menu->menu_id, quantitySold);
				std::cout << setw(20) << quantitySold << setw(20) << sales;
				if (totalSales != 0)
				{
					double salesPercentage = (sales / totalSales) * 100;
					std::cout << std::setw(20) << std::fixed << std::setprecision(2) << salesPercentage;
				}
				//int roundedPercentage = static_cast<int>(std::round(salesPercentage));
				//std::cout << std::setw(20) << generatePercentageGraph(roundedPercentage);

				if (quantitySold > max)
				{
					max = quantitySold;
					mostPopularMenu = menu->menu_id;
					name = menu->name;
					maxPrice = sales;
				}

				menu = menu->next;
			} while (menu != NULL);

			std::cout << "\n************************************************************************************************************";
			if (!mostPopularMenu.empty())
			{
				std::cout << "\n\nThe Most PoPular Menu in this month: " << name << std::endl << "Menu ID: " << mostPopularMenu << std::endl;
				std::cout << "Total Quantity Sold: " << max << std::endl << "Total sales: RM " << maxPrice << std::endl;
				std::cout << "\n************************************************************************************************************";
			}
			else
				std::cout << "\nNo sales on this month" << std::endl;
		}
		else
			std::cout << "\nSorry, no menu found." << std::endl;
		std::cout<<std::endl;
		system("pause");
}


void dailySalesinMonth(int& year, int& month)
{
	OrderManager orderManager;
	char again;
	std::string monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		std::system("cls");
		std::cout << "\n************************************************************************************************************";
		std::cout << "\n\t\t\t\t\tDaily Sales in " << monthNames[month - 1];
		std::cout << "\n************************************************************************************************************";
		std::cout << std::endl << setw(30) << "Date" << setw(45) << "Total Sales in each month (RM)";
		std::cout << "\n************************************************************************************************************\n" << std::endl;

		double max = 0.0;
		double total = 0.0;
		int highestDay;

		int maxDays = 31;  // Assume 31 days initially
		if (month == 2) {
			maxDays = (isLeapYear(year)) ? 29 : 28;  // Adjust for February
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11) {
			maxDays = 30;  // Months with 30 days
		}

		for (int day = 1; day <= maxDays; day++)
		{
			double sales = orderManager.getDailySales(year, month, day);
			std::cout << setw(25) << day << "-" << month << "-" << year << setw(40) << sales << endl;
			total += sales;
			if (sales > max)
			{
				max = sales;
				highestDay = day;
			}
		}
		std::cout << "\n************************************************************************************************************" << std::endl;
		if (total!= NULL)
		{
			std::cout << "Total Sales in " << monthNames[month-1] << ": RM " << total << std::endl;
			std::cout << "The highest sales month: " << highestDay << "-" << month << "-" << year  << std::endl;
			std::cout << "Sales on " << highestDay << "-" << month << "-" << year << ": RM " << max << std::endl;
			std::cout << "************************************************************************************************************" << std::endl;
		}
		else
		{
			std::cout << "\nNo sales in this year" << std::endl;
		}
		std::cout << std::endl;
		system("pause");
}

void AmInterface::YearlySales()
{
	OrderManager orderManager;
	int year;
	char again, details, seeDaily;
	std::string monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	do {
		std::system("cls");
		std::cout << "\n************************************************************************************************************";
		std::cout << "\n\t\t\t\t\tView Yearly Sales Report";
		std::cout << "\n************************************************************************************************************";
		std::cout << "\nClick '0' to go back to Main Menu. " << std::endl << std::endl;
		while (true) {
			try {
				std::cout << "\nPlease enter the year that you want to view the monthly sales: ";
				std::cin >> year;
					// Check if the input was successful
				if (std::cin.fail() || year < 1900 && year !=0 || year > 2024 && year != 0) {
						throw std::invalid_argument("Invalid input. Please enter a valid year.");
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			
				if (year == 0)
				{
					return;
				}
				// Input was successful, exit the loop
				break;
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what() << std::endl;
				//clear the error state
				std::cin.clear();

				//discard the invalid input
				//std::cin.ignore(999, '\n');
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		std::cout << "\n************************************************************************************************************";
		std::cout << "\n\t\t\t\t\tMonthly Sales Report in " << year;
		std::cout << "\n************************************************************************************************************";
		std::cout << std::endl << setw(15) << "Month" << setw(40) << "Total Sales in each month (RM)" << std::setw(30) << "Sales Percentage (%)";
		std::cout << "\n************************************************************************************************************\n" << std::endl;

		double max = 0.0;
		double total = 0.0;
		std::string highestMonth;
		int Hmonth;

		//calculate total sales first
		for (int month = 1; month <= 12; month++)
		{
			double sales = orderManager.getMonthlySales(year, month);
			total += sales;
		}

		for (int month = 1; month <= 12; month++)
		{
			double sales = orderManager.getMonthlySales(year, month);
			std::cout << std::endl << setw(15) << monthNames[month - 1] << setw(40) << sales;

			if (total != 0)
			{
				double salesPercentage = (sales / total) * 100;
				std::cout << std::setw(30) << std::fixed << std::setprecision(2) << salesPercentage;
			}

			//total += sales;
			if (sales > max)
			{
				max = sales;
				highestMonth = monthNames[month - 1];
				Hmonth = month;
			}
		}
		std::cout << "\n************************************************************************************************************" << std::endl;
		if (!highestMonth.empty())
		{
			std::cout << "Total Sales in " << year << ": RM " << total << std::endl;
			std::cout << "The highest sales month: " << highestMonth << std::endl;
			std::cout << "Sales in " << highestMonth << ": RM " << max << std::endl;
			std::cout << "************************************************************************************************************" << std::endl;
			std::cout << "\n\nMonthly Sales Details in " << highestMonth << " is loading. . ." << std::endl << std::endl;
			system("pause");
			MonthlySales(year, Hmonth);
			do {
				std::cout << "Do you want to view daily sales in the highest month? (Y/N): "; std::cin >> details;
				if (details == 'Y' || details == 'y')
				{
					dailySalesinMonth(year, Hmonth);
				}
			} while (details != 'Y' && details != 'y' && details != 'N' && details != 'n');
		}
		else
		{
			std::cout << "\nNo sales in this year" << std::endl;
		}
		do
		{
			std::cout << "\nDo you want to view yearly report of other years? (Y/N): "; std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'n' && again != 'N');
	} while (again == 'Y' || again == 'y');
}

void AmInterface::overallSales()
{
	std::cout << "\n************************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\t\t Sales Report";
	std::cout << "\n************************************************************************************************************";
	MenuManager menuManager;
	Menu* menus = menuManager.getMenus();

	if (menus != NULL) //menu exists
	{
		std::cout << std::endl << setw(10) << "Menu ID" << setw(30) << "Menu Name" << setw(18) << "Total Quantity" << setw(20) << "Total sales (RM)" << std::setw(25) << "Sales Percentage (%)";
		std::cout << "\n************************************************************************************************************";
		Menu* menu = menus;
		double maxSales = 0.0;
		int maxQtt = 0;
		std::string mostPopularMenu, menuName;
		double totalSales = 0.0;

		//calculate total sales first
		do
		{
			OrderManager orderManager;
			double sales = orderManager.getMenuSales(menu->menu_id);
			totalSales += sales;

			menu = menu->next;
		} while (menu != NULL);

		// Reset menu pointer for the second loop
		menu = menus;

		do
		{
			std::cout << std::endl << setw(10) << menu->menu_id << setw(30) << menu->name;
			int quantity = 0;
			double discount = 0.0;
			OrderManager orderManager;
			double sales = orderManager.getMenuSales(menu->menu_id);
			
			OrderList* orders = orderManager.getOrders();

			if (orders != NULL)
			{
				OrderList* order = orders;
				do
				{
					if (order->menuID == menu->menu_id)
					{
						quantity = quantity + order->quantity;
					}
					order = order->next;
				} while (order != NULL);
			}
			else
				std::cout << "No order found";
			std::cout << setw(18) << quantity << setw(20) << sales;

			// Calculate and display sales percentage
			if (totalSales != 0)
			{
				double salesPercentage = (sales / totalSales) * 100;
				std::cout << std::setw(25) << std::fixed << std::setprecision(2) << salesPercentage;
			}
			/*
			int roundedPercentage = static_cast<int>(std::round(salesPercentage));
			std::cout << std::setw(20) << generatePercentageGraph(roundedPercentage);
			*/
			// Check if the current menu has a higher quantity than the current maximum
			if (quantity > maxQtt)
			{
				maxQtt = quantity;
				mostPopularMenu = menu->menu_id;
				menuName = menu->name;
				maxSales = sales;
			}

			menu = menu->next;
		} while (menu != NULL);

		if (!mostPopularMenu.empty())
		{
			std::cout << "\n************************************************************************************************************";
			std::cout << "\n\nThe Most Popular Menu: " << menuName << std::endl;
			std::cout << "Menu ID: " << mostPopularMenu << std::endl;
			std::cout << "Total Sold Quantity: " << maxQtt << std::endl;
			std::cout << "Total Sales: RM " << maxSales << std::endl;
		}
		else
		{
			std::cout << "\nNo orders found for any menu." << std::endl;
		}

	}
	else
		std::cout << "\nSorry, no menu found." << std::endl;
	std::cout << "\n************************************************************************************************************";
}