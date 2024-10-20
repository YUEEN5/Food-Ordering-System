//#include<iostream>
//#include<iomanip>
//#include<ctime>
//#include<sstream>
//#include <cstdlib> 
#include <iomanip> //for setw //for time
#include <conio.h>	//for password error handling  _getch()
#include <chrono> //for delay
#include <thread> //for delay
#include <mysql/jdbc.h> //connect database
#include <regex> //for ic, phoneNum format

#include "CustInterface.h"
#include "OrderList.h"
#include "OrderManager.h"
#include "MenuManager.h"
#include "CustManager.h"
#include "AccountManager.h"
#include "PaymentManager.h"
#include "FbManager.h"
#include "DatabaseConnection.h"

void ClrSn()
{
	std::system("cls");
}

void CustInterface::viewRandMenu()
{
	//int custID;
	MenuManager menuManager;

	Menu* menu = menuManager.getRandMenu();
	std::cout << "*************************************************************************************************\n\n";
	std::cout << "\t\t\t\tGrab Your Lucky's meal Now!\n\n";
	std::cout << "*************************************************************************************************\n";
	if (menu != NULL)
	{
		std::cout << std::endl << "Menu ID: " << menu->menu_id << std::endl;
		std::cout << "Menu Name: " << menu->name << std::endl;
		std::cout << "Menu Description: " << menu->description << std::endl;
		std::cout << "Menu Price: " << menu->price << std::endl;
		std::cout << "*************************************************************************************************\n\n";
		menu = menu->next;
	}
	else
		std::cout << "Menu cannot found.";
	return;
}

void CustInterface::viewMenu()
{
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\tLucky's Food Menu";
	std::cout << "\n*************************************************************************************************";
	MenuManager menuManager;
	Menu* menus = menuManager.getcustMenus();

	if (menus != NULL) //menu exists
	{
		Menu* menu = menus;
		do
		{
			std::cout << std::endl << "Menu ID: " << menu->menu_id << std::endl;
			std::cout << "Menu Name: " << menu->name << std::endl;
			std::cout << "Menu Description: " << menu->description << std::endl;
			std::cout << "Menu Price: " << menu->price << std::endl;
			menu = menu->next;
		} while (menu != NULL);

	}
	else
		std::cout << "\n\nSorry, no menu found." << std::endl;
		std::cout << "\n*************************************************************************************************\n\n";
}

//display after confirming, cannot edit already
void dplyOrder(int orderID)
{
	//char confirm;
	OrderManager orderManager;
	OrderList* order = orderManager.getOrder(orderID);
	std::cout << "\n========================================================================================================" << std::endl;
	std::cout << std::endl << "\t\t\t\tOrder ID: " << order->orderID << std::endl;
	std::cout << "\n========================================================================================================" << std::endl;
	std::cout << "Customer ID: " << order->custID << std::endl;
	std::cout << "Menu ID: " << order->menuID << std::endl;

	MenuManager menuManager;
	Menu* menu = menuManager.getMenu(order->menuID);
	std::cout << "Menu Name: " << menu->name << std::endl;
	//std::cout << "Menu Description: " << menu->description << std::endl;
	std::cout << "Menu Single Price: " << menu->price << std::endl;
	std::cout << "Quantity: " << order->quantity << std::endl;
	std::cout << "Total Purchase: RM " << order->tPrice << std::endl;
	std::cout << "Your remark: " << order->remark << std::endl;
	std::cout << "Discount: " << order->discount*100 << "%" << std::endl;
	std::cout << "Payment Method: " << order->payMethod << std::endl;
	std::cout << "Delivery Method: " << order->delivery << std::endl;
	if (order->delivery == "Delivery")
	{
		//std::cout << "Delivery Method: Delivery" << std::endl;
		std::cout << "Delivery to: " << order->address << std::endl;
	}
	std::cout << "Order Date and Time: " << order->oDateTime << std::endl;
	std::cout << "========================================================================================================" << std::endl;
	//makePayment(order->orderID);
}

/*void makePayment(int orderid, int& startingPayID)
{
	DatabaseConnection dbConn;
	PaymentManager paymentManager;
	Payment* pay = new Payment();
	std::string buffer;
	std::getline(std::cin, buffer);
	//auto generated order ID
	sql::PreparedStatement* psSelect = dbConn.prepareStatement("SELECT MAX(PAYMENT_ID) AS MaxID FROM PAYMENT");
	int MaxID = 0;
	sql::ResultSet* rs = psSelect->executeQuery();

	if (rs->next()) 
	{
		MaxID = rs->getInt("MaxID");
	}

	startingPayID = std::max(MaxID + 1, 20001);

	pay->paymentID = startingPayID;
	rs->close();
	delete rs;

	pay->orderID = orderid;
	std::cout << "Payment ID: " << pay->orderID;
	char pMethod;
	OrderManager orderManager;
	OrderList* order = orderManager.getOrder(orderid);
	do {
		std::cout << "Payment method (C = Cash / T = Tng Ewallet / B = Online Banking): ";
		std::cin >> pMethod;
	} while (pMethod != 'C' && pMethod != 'c' && pMethod != 'T' && pMethod != 't' && pMethod != 'b' && pMethod != 'B');
	if (pMethod == 'C' || pMethod == 'c') {
		pay->method = "Cash";
		//pay->status = 0;
	}
	else if (pMethod == 'T' || pMethod == 't') {
		pay->method = "Tng Ewallet";
	}
	else {
		pay->method = "Online Banking";
	}
	char delivery;
	double price = 0.0;
	std::cout << "Delivery/Pick Up (D/P): "; std::cin >> delivery;
	if (delivery == 'D' || delivery == 'd')
	{
		pay->delivery = "Delivery";
		price = order->tPrice + 2;
		std::cout << "Please ensure your address is correct.";
	}
	else if (delivery == 'P' || delivery == 'p')
	{
		pay->delivery = "Pick Up";
		price = order->tPrice;
		std::cout << "We are here: No.10, Jalan Wawa 2, Taman Bahagia Wawa, Melaka."
			<< "Please come here to pick your meal at 1.00 pm. Thank you.";
	}

	FbManager fbManager;
	bool correct;
	int fbId;
	do {
		std::cout << "Please enter you feedback id to get 5% discount on this purchase (click '0' if no feedback id): ";
		std::cin >> fbId;
		if (fbId == 0)
		{
			pay->discount = 0.0;
			pay->discountCode = 0.0;
			correct = true;
		}
		else if (fbManager.fbExists(fbId)) {
			Feedback* fb = fbManager.getFb(fbId);
			if (!paymentManager.fbExists(fbId) && order->custID == fb->custID) {
				pay->discount = 0.05;
				pay->discountCode = fbId;
				correct = true;
			}
			else {
				pay->discount = 0.0;
				std::cout << "Your discount code has been use or this may not be your discount code. Please try again.";
				pay->discountCode = 0.0;
				correct = false;
			}
			Feedback* fb = fbManager.getFb(fbId);
		}
		else
		{
			std::cout << "Invalid Feedback ID. Please try again" << std::endl;
			pay->discountCode = 0.0;
			correct = false;
		}
	} while (!correct);

	pay->fPrice = price * (1 - pay->discount);

	//std::string codePayment;
	//std::cout << "Please enter the code has been sent via SMS: ";
	//std::cin >> codePayment;
	//if (codePayment == "")
	//PaymentManager paymentManager; //use this to add menu to database
	int status = paymentManager.addPayment(pay);

	if (status != 0)
		std::cout << "Successfully paid" << std::endl;
	else
		std::cout << "Unable to pay" << std::endl;
}*/

//CUSTOMER CANNOT DELETE AND UPDATE ORDER AFTER CONFIRMING(SAVING INTO DATABASE), SO NO NEED DELETE N UPDATE IN ORDERMANAGER

void updateO(int& custid, std::string& MenuID, std::string& Remark, int& Quantity, char& pMethod, char& delivery, double& price, std::string& address)
{
	MenuManager menuManager;
	CustManager custManager;
	bool correct;
	double purchase=0.0;
	std::string buffer;
	char update;
	std::cout << "\n\nPlease select the details of the order that you want to change: " << std::endl;
	std::cout << "==================================================================";
	std::cout << "\n1. Menu ID";
	std::cout << "\n2. Remark";
	std::cout << "\n3. Quantity";
	std::cout << "\n4. Payment Method";
	std::cout << "\n5. Delivery";
	std::cout << "\n6. Address";
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
			do {
				std::cout << "Update Menu ID: ";
				std::getline(std::cin, MenuID);
				if (menuManager.menuExists(MenuID)) {
					Menu* menu = menuManager.getMenu(MenuID);
					if (menu->status == "available")
					{
						correct = true;
						price = menu->price;
					}
					else
					{
						std::cout << "\nThe menu is unavailable now." << std::endl;
						correct = false;
					}
				}
				else
				{
					std::cout << "\nInvalid menu ID. Please try again.\n";
					// Clear entered menuid for the next attempt using empty string
					MenuID = "";
					correct = false;
				}
			} while (!correct);
			break;
		case 2:
			std::cout << "Update Remark: ";
			std::getline(std::cin, Remark);
			break;
		case 3:
		//	Menu * menu = menuManager.getMenu(MenuID);
			while (true) {
				try {
					Menu* menu = menuManager.getMenu(MenuID);
					std::cout << "Update Quantity: ";
					std::cin >> Quantity;
					std::cin.ignore();
					// Check if the input was successful
					if (std::cin.fail()) {
						throw std::invalid_argument("Invalid input. Please enter a valid number.");
					}
					price = menu->price * Quantity;
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
				std::cout << "Payment method (C = Cash / T = Tng Ewallet / B = Online Banking): ";
				std::cin >> pMethod;
				std::cin.ignore();
			} while (pMethod != 'C' && pMethod != 'c' && pMethod != 'T' && pMethod != 't' && pMethod != 'b' && pMethod != 'B');
			break;
		case 5:

			char change;
			do {
				std::cout << "Update Delivery Method (D = Delivery /P = PickUp): ";
				std::cin >> delivery;
				std::cin.ignore();
				if (delivery == 'D' || delivery == 'd')
				{
					//price = price + 2;
					Customer * custs = custManager.getCust(custid);
					Customer* cust = custs;
					std::cout << "\nPlease ensure your address is correct: " << cust->address;
					do {
						std::cout << "\nDo you want to change your address for this time purchase? (Y/N): ";
						std::cin >> change;
						std::cin.ignore();
						if (change == 'Y' || change == 'y')
						{
							std::cout << "Please enter your address for this order: ";
							std::getline(std::cin, address);
							//std::cin.ignore();
						}
						else
						{
							address = cust->address;
						}
					} while (change != 'Y' && change != 'y' && change != 'N' && change != 'n');
					std::cout << "\nPlease be informed that RM2 will be charged for the delivery fee.\n";
				}
				else if (delivery == 'P' || delivery == 'p')
				{
					//price = purchase;
					address = "NULL";
					std::cout << "\nWe are here: No.10, Jalan Wawa 2, Taman Bahagia Wawa, Melaka."
						<< "\nPlease come here to pick your meal from 12.00 pm to 1.00 pm. Thank you.\n";
				}
			} while (delivery != 'D' && delivery != 'd' && delivery != 'P' && delivery != 'p');
			break;
		case 6:
			if (delivery == 'D' || delivery == 'd')
			{
				std::cout << "Update Address: ";
				std::getline(std::cin, address);
			}
			else if (delivery == 'P' || delivery == 'p')
			{
				std::cout << "Your delivery method is pick up. You don't have to change address.";
				//break;
			}
			break;
		case 7:
			std::cout << "Update cancelled";
			return;
		default:
			std::cout << "Invalid choice. Please choose again.";
			return;
		}
		std::cout << "\nDo you still want to make changes on your order? (Y/N): ";
		std::cin >> update;
	} while (update == 'y' || update == 'Y');
	std::cout << "Your order is saving. . ." << std::endl;
}

//before confirming, still can update, delete, haven't save into database
void displayO(int& startingOrderID, int& custid, std::string& MenuID, std::string& Remark, int& Quantity, double& totalPurchase, char& pMethod, char& delivery, double& discount, int& discountCode, std::string address)
{
	OrderManager orderManager;
	OrderList* order = new OrderList();
	int confirm;
	int status = 0;
	std::cout << "\n========================================================================================================" << std::endl;
	std::cout << "\n\t\t\t\tOrder ID: " << startingOrderID << std::endl;
	std::cout << "\n========================================================================================================" << std::endl;
	std::cout << "Customer ID: " << custid << std::endl;
	std::cout << "Menu ID: " << MenuID << std::endl;
	
	//date:
	time_t currentDateTime = time(0);

	std::tm localTime;
#ifdef _MSC_VER
	localtime_s(&localTime, &currentDateTime);
#else
	localtime_r(&currentDateTime, &localTime);
#endif
	//std::cout << "Order Date and Time: " << std::put_time(&localTime, "%d/%m/%Y %H:%M:%S") << std::endl;
	std::stringstream dateTimeStream;
	dateTimeStream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

	MenuManager menuManager;
	Menu* menu = menuManager.getMenu(MenuID);
	std::cout << "Menu Name: " << menu->name << std::endl;
	std::cout << "Menu Description: " << menu->description << std::endl;
	std::cout << "Menu Single Price: " << menu->price << std::endl;
	std::cout << "Quantity: " << Quantity << std::endl;
	std::cout << "Total Price (exclude delivery fee): " << totalPurchase << std::endl;
	std::cout << "Your remark: " << Remark << std::endl;
	std::cout << "Payment Method: " << pMethod << std::endl;
	//std::cout << "Delivery Method: " << delivery << std::endl;
	if (delivery == 'D' || delivery == 'd')
	{
		std::cout << "Delivery Method: Delivery" << std::endl;
		std::cout << "Delivery to: " << address << std::endl;
	}
	else if (delivery == 'P' || delivery == 'p')
	{
		std::cout << "Delivery Method: Pick Up" << std::endl;
	}
	//std::cout << "Order Date and Time: " << std::put_time(&localTime, "%d/%m/%Y %H:%M:%S") << std::endl;
	std::cout << "========================================================================================================" << std::endl;
	std::cout << "\nPlease check your order.";
	std::cout << "\n========================================================================================================" << std::endl;
	std::cout << "\n1. Confirm your order.";
	std::cout << "\n2. Make changes on your order.";
	std::cout << "\n3. Delete your order.";
	std::cout << "\n========================================================================================================" << std::endl;
		while (true) {
			try {
				std::cout << "Please choose (1-3): "; std::cin >> confirm;
				//std::cin.ignore();
				// Check if the input was successful
				if (std::cin.fail() || confirm < 1 || confirm > 3) {
					throw std::invalid_argument("Invalid input. Please enter a valid number. (1-3)");
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
		switch (confirm) {
		case 1:
			order->custID = custid;
			order->tPrice = totalPurchase;
			order->orderID = startingOrderID;
			order->oDateTime = dateTimeStream.str();
			order->menuID = MenuID;
			order->remark = Remark;
			order->quantity = Quantity;
			order->discount = discount;
			if (pMethod == 'C' || pMethod == 'c') {
				order->payMethod = "Cash";
				//pay->status = 0;
			}
			else if (pMethod == 'T' || pMethod == 't') {
				order->payMethod = "Tng Ewallet";
			}
			else {
				order->payMethod = "Online Banking";
			}
			//double price = 0.0;
			if (delivery == 'D' || delivery == 'd')
			{
				order->delivery = "Delivery";
				order->tPrice = totalPurchase + 2;
			}
			else if (delivery == 'P' || delivery == 'p')
			{
				order->delivery = "Pick Up";
				order->tPrice = totalPurchase;
			}
			order->disCode = discountCode;
			order->address = address;
			//OrderManager orderManager;
			status = orderManager.addOrder(order);

			if (status != 0)
			{
				std::cout << "\nSuccessfully placed an order" << std::endl;

				std::cout << "\n\nYour order slip is printing. . . Please wait. . . ." << std::endl;
				std::chrono::seconds duration(5);
				std::this_thread::sleep_for(duration);
				ClrSn();
				dplyOrder(order->orderID);
			}
			else
				std::cout << "Sorry, unable to place an order. Please try again." << std::endl;
			std::cout << "\nPlease take a screenshot of the slip as a prove when picking up your meal.Thank you!" << std::endl;
			//std::cout << "\nThen, please press any key to continue.";
			system("pause");
			//std::chrono::seconds duration(5);
			//std::this_thread::sleep_for(duration);
			break;
		case 2:
			updateO(custid, MenuID, Remark, Quantity, pMethod, delivery, totalPurchase, address);
			order->custID = custid;
			order->tPrice = totalPurchase;
			order->orderID = startingOrderID;
			order->oDateTime = dateTimeStream.str();
			order->menuID = MenuID;
			order->remark = Remark;
			order->discount = discount;
			order->quantity = Quantity;
			if (pMethod == 'C' || pMethod == 'c') {
				order->payMethod = "Cash";
				//pay->status = 0;
			}
			else if (pMethod == 'T' || pMethod == 't') {
				order->payMethod = "Tng Ewallet";
			}
			else {
				order->payMethod = "Online Banking";
			}
			//std::cout << "Delivery/Pick Up (D/P): "; std::cin >> delivery;
			if (delivery == 'D' || delivery == 'd')
			{
				order->delivery = "Delivery";
				order->tPrice = totalPurchase + 2;
			}
			else if (delivery == 'P' || delivery == 'p')
			{
				order->delivery = "Pick Up";
				//order->tPrice = totalPurchase;
			}
			order->disCode = discountCode;
			order->address = address;
			//OrderManager orderManager;
			status = orderManager.addOrder(order);

			if (status != 0)
			{
				std::cout << "Successfully placed an order" << std::endl;
				std::cout << "\n\nYour order slip is printing. . . Please wait. . . .";
				std::chrono::seconds duration(5);
				std::this_thread::sleep_for(duration);
				ClrSn();
				//makePayment(order->orderID);
				dplyOrder(order->orderID);
			}
			else
				std::cout << "Sorry, unable to place an order. Please try again." << std::endl;
			std::cout << "\nPlease take a screenshot of the slip as a prove when picking up your meal.Thank you!";
			system("pause");
			break;
		case 3:
			//means no need save into database
			std::cout << "\nYour order has been deleted." << endl;
			break;
		default:
			std::cout << "Invalid input.Please choose again (1-3).";
			break;
		}
}

void CustInterface::PlaceOrder(int custid)
{
	DatabaseConnection dbConn;
	MenuManager menuManager;

	OrderList* order = new OrderList();
	int Quantity;
	std::string buffer, MenuID, Remark;
	std::getline(std::cin, buffer);
	bool correct;
	char want;
	//char confirm;
	//auto generated order ID
	sql::PreparedStatement* psSelect = dbConn.prepareStatement("SELECT MAX(ORDER_ID) AS MaxID FROM Orderlist");
	int MaxID = 0;
	sql::ResultSet* rs = psSelect->executeQuery();

	if (rs->next()) {
		MaxID = rs->getInt("MaxID");
	}

	int startingOrderID = std::max(MaxID + 1, 800001);

	//order->orderID = startingOrderID;
	rs->close();
	delete rs;

	//order->custID = custid;
	//std::cout << order->custID;
//	do {
		std::cout << "\nClick 'q' to go back to Customer Menu." <<std::endl;
		//std::cout << "Please type your order details below. Thank you!" << std::endl;
		do {
			std::cout << "Menu ID: ";
			std::getline(std::cin, MenuID);
			if (MenuID == "q" || MenuID == "Q")
			{
				return;
			}
			else if (menuManager.menuExists(MenuID)) {
				Menu* menu = menuManager.getMenu(MenuID);
				if (menu->status == "AVAILABLE" )
				{
					correct = true;
				}
				else
				{
					std::cout << "\nThe menu is unavailable now." << std::endl;
					correct = false;
				}
			}
			else
			{
				std::cout << "\nInvalid menu ID. Please try again.\n";
				// Clear entered menuid for the next attempt using empty string
				MenuID = "";
				correct = false;
			}
		} while (correct == false);

		std::cout << "Remark (if any): ";
		std::getline(std::cin, Remark);

		while (true) {
			try {
				std::cout << "Quantity: ";
				std::cin >> Quantity;
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

		double discount = 0.0;
		CustManager custManager;
		Customer* custs = custManager.getIC(custid);

		Customer* cust = custs;

		std::string birthdateString = cust->custIC.substr(2, 4);
		int birthMonth, birthDay;

		stringstream(birthdateString.substr(0, 2)) >> birthMonth;
		stringstream(birthdateString.substr(2, 2)) >> birthDay;

		time_t currentDateTime = time(0);
		//order->oDateTime = currentDateTime;

		std::tm localTime;
#ifdef _MSC_VER
		localtime_s(&localTime, &currentDateTime);
#else
		localtime_r(&currentDateTime, &localTime);
#endif

		int currentMonth = localTime.tm_mon + 1;
		int currentDay = localTime.tm_mday;

		Menu* menus = menuManager.getMenu(MenuID);

		Menu* menu = menus;
		double totalPurchase = 0;
		double dis;
		do
		{
			if (birthMonth == currentMonth && birthDay == currentDay) 
			{
				std::cout << "\n*************************************************************************************************\n";
				cout << "\n\t\t***** Happy birthday! You will get 10% discount today *****" << std::endl;
				std::cout << "\n*************************************************************************************************\n\n";
				dis = 0.10;
				totalPurchase += menu->price * Quantity * 0.9;
			}
			else {
				totalPurchase += menu->price * Quantity;
				dis = 0.0;
			}
			menu = menu->next;
		} while (menu != NULL);

		char pMethod;
		do {
			std::cout << "Payment method (C = Cash / T = Tng Ewallet / B = Online Banking): ";
			std::cin >> pMethod;
		} while (pMethod != 'C' && pMethod != 'c' && pMethod != 'T' && pMethod != 't' && pMethod != 'b' && pMethod != 'B');
		char delivery, change;
		std::string address;
		//double price = 0.0;
		do {
			Customer* custs = custManager.getCust(custid);
			Customer* cust = custs;
			std::cout << "Delivery/Pick Up (D/P): "; std::cin >> delivery;
			if (delivery == 'D' || delivery == 'd')
			{
				//order->delivery = "Delivery";
				//price = totalPurchase + 2;
				std::cout << "\nPlease ensure your address is correct: " << cust->address; 
				do {
					std::cout << "\nDo you want to change your address for this time purchase? (Y/N): ";
					std::cin >> change;
					std::cin.ignore();
					if (change == 'Y' || change == 'y')
					{
						do {
							std::cout << "\nPlease enter your address for this order: ";
							std::getline(std::cin, address);
						} while (address.empty());
					}
					else
					{
						address = cust->address;
					}
				} while (change != 'Y' && change != 'y' && change != 'N' && change != 'n');
				std::cout<< "\nPlease be informed that RM2 will be charged for the delivery fee.\n";
			}
			else if (delivery == 'P' || delivery == 'p')
			{
				//order->delivery = "Pick Up";
				//price = totalPurchase;
				address = "NULL";
				std::cout << "\nWe are here: No.10, Jalan Wawa 2, Taman Bahagia Wawa, Melaka."
					<< "\nPlease come here to pick your meal from 12.00 pm to 1.00 pm. Thank you.\n";
			}
		} while (delivery != 'D' && delivery != 'd' && delivery != 'P' && delivery != 'p');
		do {
			std::cout << "\nDo you want to view the discount code you can use? (Y/N): "; std::cin >> want;
			if (want == 'Y' || want == 'y')
			{
				viewCode(custid);
				break;
			}
		}while (want != 'Y' && want != 'y' && want != 'N' && want != 'n');
		
		OrderManager orderManager;
		FbManager fbManager;
		bool correctFBID=false;
		int fbId, discountCode;
		do {
			while (true) {
				try {
					std::cout << "\nPlease enter you feedback id to get 5% discount on this purchase (click '0' if no feedback id): ";
					std::cin >> fbId;
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
			if (fbId == 0)
			{
				discount = 0.0;
				discountCode = 0;
				correctFBID = true;
			}
			else if (fbManager.fbExists(fbId)) {
				Feedback* fb = fbManager.getFb(fbId);
				if (!orderManager.fbExists(fbId) && fb->custID == custid) {
					//std::cout << fb->fbID;
					discount = 0.05;
					discountCode = fbId;
					correctFBID = true;
				}
				else {
					discount = 0.0;
					std::cout << "Your discount code has been use or this may not be your discount code. Please try again.";
					discountCode = 0;
					correctFBID = false;
				}
			}
			else
			{
				std::cout << "Invalid Feedback ID. Please try again" << std::endl;
				discountCode = 0;
				correctFBID = false;
			}
		} while (!correctFBID);

		totalPurchase = totalPurchase * (1 - discount);
		discount = discount + dis;
		//order->tPrice = totalPurchase;

		//std::cout << "Total Purchase: " << totalPurchase << std::endl;

		// Display the formatted order date and time
		//std::cout << "Order Date and Time: " << std::put_time(&localTime, "%d/%m/%Y %H:%M:%S") << std::endl;
		std::stringstream dateTimeStream;
		dateTimeStream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
		ClrSn();
		displayO(startingOrderID, custid, MenuID, Remark, Quantity, totalPurchase, pMethod, delivery, discount, discountCode, address);
}

void CustInterface::viewCode(int custid)
{
	OrderManager orderManager;
	FbManager fbManager;
	std::cout << "\n*************************************************************************************************\n\n";
	std::cout << "\t\t\t\tGet Your Code here to get discount\n";
	std::cout << "\n*************************************************************************************************\n\n";
	
	Feedback* fb = fbManager.getFbforCust(custid);
	if (fb != NULL)
	{
		std::cout << "\t\t\tThese codes can be used to get 5% discount on your purchase." << std::endl << std::endl;
		do
		{
			if (!orderManager.fbExists(fb->fbID) && fb->custID == custid)
			{
				std::cout << "\t\t\t\t\t\t" << fb->fbID << std::endl;

			}
			fb = fb->next;
		} while (fb != NULL);
	}
	else
		std::cout << "\n\n\t\tSorry, you don't have any discount code yet. Go comment to collect your code!\n\n";
	system("pause");
}

void CustInterface::viewFeedback()
{
	MenuManager menuManager;
	std::cout << "\n************************************************************************************************************************************************************\n";
	std::cout << "\t\t\t\t\t\t\t\tComments and Review";
	std::cout << "\n************************************************************************************************************************************************************\n\n";

	Menu* menus = menuManager.getAllMenuID();

	if (menus != NULL) //menu exists
	{
		Menu* menu = menus;
		do
		{
			std::cout << "\n************************************************************************************************************************************************************";
			std::cout << std::endl << "\nMenu ID: " << menu->menu_id << std::endl;
			std::cout << "Menu Name: " << menu->name << std::endl;
			
			OrderManager orderManager;
			OrderList* orders = orderManager.getOrderswifMenuID(menu->menu_id);

			if (orders != NULL)
			{
				OrderList* order = orders;
				do
				{
					//if (order->orderID != 0) {
						//std::cout << std::endl << "Feedback ID: " << order->orderID;
						
						FbManager fbManager;
						Feedback* fb = fbManager.getFbbasedOrder(order->orderID);
						if (fb != NULL)
						{
							//Feedback* fb = fbs;
							//do
							//{
							std::cout << std::endl << "Feedback ID: " << fb->fbID
								<< "\tCustomer ID: " << fb->custID;
								std::cout << "\tRating: " << std::string(fb->rating, '*');
								std::cout << std::setw(15) << "\tComments: " << fb->comment;
							//std::cout << std::endl << "Feedback ID: " << fb->fbID << setw(5) << "\tRating: " << fb->rating << setw(10) << "\tComments: " << fb->comment << setw(10) << "\tCustomer ID: " << fb->custID;
							//} while (fb != NULL);
							fb = fb->next;
						}
						//else
							//std::cout << "\nNo feedback yet";
						
					//}
					//else
						//std::cout << " ";
					order = order->next;
				} while (order != NULL);
			}
			else
				std::cout << "No order yet.";
			
			menu = menu->next;
		} while (menu != NULL);
	}
	else
		std::cout << "Sorry, no menu found." << std::endl;
	std::cout << "\n************************************************************************************************************************************************************\n\n";
}

void CustInterface::doFeedback(int custid)
{
	DatabaseConnection dbConn;
	Feedback* fb = new Feedback();
	bool correct;
	int orderid;
	FbManager fbManager;
	OrderManager orderManager;
	std::cout << "*************************************************************************************************";
	std::cout << "\n                                       Feedback";
	std::cout << "\n*************************************************************************************************";
	do {
		while (true) {
			try {
				std::cout << "\nPlease enter your order id (click '0' to go back): "; std::cin >> orderid;
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
		//std::cout << "\nPlease enter your order id (click '0' to go back): "; std::cin >> orderid;
		OrderList* order = orderManager.getOrder(orderid);
		if (orderid == 0)
		{
			return;
		}
		else if (orderManager.orderExists(orderid)) {
			if (!fbManager.odExists(orderid) && order->custID == custid)
			{
				fb->orderID = orderid;
				correct = true;
			}
			else
			{
				std::cout << "\nThis order has been rated before. Please try again.";
				correct = false;
			}
		}
		else {
			std::cout << "\nInvalid order ID. Please try again.";
			correct = false;
		}
	} while (!correct);
	fb->custID = custid;
	sql::PreparedStatement* psSelect = dbConn.prepareStatement("SELECT MAX(FEEDBACK_ID) AS MaxID FROM FEEDBACK");
	int MaxID = 0;
	sql::ResultSet* rs = psSelect->executeQuery();

	if (rs->next()) {
		MaxID = rs->getInt("MaxID");
	}

	int startingFeedbackID = std::max(MaxID + 1, 900001);

	fb->fbID = startingFeedbackID;
	rs->close();
	delete rs;
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\nFeedback ID: " << fb->fbID << std::endl;
	while (true) {
		try {
			std::cout << "Rating (1-5): ";
			std::cin >> fb->rating;
			std::cin.ignore();
			// Check if the input was successful
			if (std::cin.fail() || fb->rating < 1 || fb->rating > 5) {
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
			std::cin.ignore(999, '\n');
		}
	}
	std::cout << "Comments: "; std::getline(std::cin, fb->comment);
	std::cout << "\n*************************************************************************************************";

	int status = fbManager.addFb(fb);

	if (status != 0)
		std::cout << "\nSuccessfully added feedback on your order " << fb->orderID << ". \nYou can use this feedback ID to get 5% dicount on your next purchase." << std::endl;
	else
		std::cout << "\n to add feedback" << std::endl;
}

void CustInterface::selectmultiple()
{
	int minPrice;
	MenuManager menuManager;

	std::cout << "Minimum Price: "; std::cin >> minPrice;

	Menu* menus = menuManager.getMenu(minPrice);

	if (menus != NULL) //menu exists
	{
		Menu* menu = menus;
		do
		{
			std::cout << std::endl << "Menu ID: " << menu->menu_id << std::endl;
			std::cout << "Menu Name: " << menu->name << std::endl;
			std::cout << "Menu Description: " << menu->description << std::endl;
			std::cout << "Menu Price: " << menu->price << std::endl;
			menu = menu->next;
		} while (menu != NULL);
	}
	else
		std::cout << "Menu cannot found." << std::endl;
}

void CustInterface::SignUpCust(int& custid)
{
	DatabaseConnection dbConn; 
	Customer* cust = new Customer();
	Account* acc = new Account();
	std::string buffer, UN;
	char c;
	bool repeated = true;

	std::getline(std::cin, buffer);
	// Retrieve the maximum customer ID from the database
	sql::PreparedStatement* psSelect = dbConn.prepareStatement("SELECT MAX(Cust_id) AS MaxID FROM Customer");
	int maxID = 0;
	sql::ResultSet* rs = psSelect->executeQuery();

	if (rs->next()) 
	{
		maxID = rs->getInt("MaxID");
	}

	// Determine the starting point for custID
	int startingID = std::max(maxID + 1, 300001);

	// Set the custID for the new customer
	cust->custID = startingID;

	// Close the result set
	rs->close();
	delete rs;

	std::cout << "\nCustomer ID:" << cust->custID << std::endl;
	//custid = cust->custID;

	std::cout << "Name: ";
	std::getline(std::cin, cust->name);
	if (cust->name == "q" || cust->name == "Q")
	{
		return;
	}
	do {
		std::cout << "Ic Number (XXXXXX-XX-XXXX): ";
		std::getline(std::cin, cust->custIC);
	}while (!std::regex_match(cust->custIC, std::regex(R"(\d{6}-\d{2}-\d{4})")));

	int lastDigit = cust->custIC.back() - '0';
	cust->gender = (lastDigit % 2 == 0) ? "Female" : "Male";

	do {
		std::cout << "Phone Number (XXX-XXX XXXX): ";
		std::getline(std::cin, cust->phoneNo);
	} while (!std::regex_match(cust->phoneNo, std::regex(R"(\d{3}-\d{3} \d{4}|\d{3}-\d{4} \d{4})")));

	std::cout << "Email: ";
	std::getline(std::cin, cust->email);

	std::cout << "Address: ";
	std::getline(std::cin, cust->address);

	std::cout << "Gender: " << cust->gender;

	CustManager custManager;
	int status1 = custManager.addCust(cust);

	if (status1 != 0)
		std::cout << "\nSuccessfully signed up" << std::endl;
	else
		std::cout << "\nSorry, unable to sign up. Please contact seller for further information." << std::endl;

	std::cout << "\nPlease enter your username and password for everytime log in:" << std::endl;
	//auto generated account ID
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

	custid = cust->custID;
	acc->custID = cust->custID;
	acc->adminRole = 0;
	std::cout << "Account ID: " << acc->accID << std::endl;
	do
	{
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
		//std::getline(std::cin, acc->password);
		while ((c = _getch()) != '\r')
		{
			if (c == '\b') // Check for backspace
			{
				if (!acc->password.empty())
				{
					std::cout << "\b \b"; // Move the cursor back and erase the character
					acc->password.pop_back();   // Remove the last character from the password
				}
			}
			else
			{
				acc->password += c;
				std::cout << "*";
			}
		}


	AccountManager accManager;

	int status2 = accManager.addAccC(acc);
	if (status2 != 0)
		std::cout << "\nSuccessfully signed up for log in" << std::endl;
	else
		std::cout << "\nUnable to sign up for log in" << std::endl;
}

void CustInterface::selectOneCust(int custid)
{
	//int custID;
	CustManager custManager;
	//std::cout << "Please enter the customer ID to view the menu." << std::endl;
	//std::cout << "\nCust ID: ";
	//std::cin >> custID;
	Customer* cust = custManager.getCust(custid);
	cust->custID = custid;

	if (cust != NULL)
	{
		std::cout << std::endl << "Customer ID: " << cust->custID << std::endl;
		std::cout << "Name: " << cust->name << std::endl;
		std::cout << "IC Number: " << cust->custIC << std::endl;
		std::cout << "Phone Number: " << cust->phoneNo << std::endl;
		std::cout << "Email Address: " << cust->email << std::endl;
		std::cout << "Address: " << cust->address << std::endl;
		std::cout << "Gender: " << cust->gender << std::endl << std::endl;
		std::cout << "*************************************************************************************************\n\n";
		cust = cust->next;
	}
	else
		std::cout << "Customer cannot found.";
	return;
}

void CustInterface::editPw(int custID, int& status)
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
		else if (accManager.pwCorrectC(pw))
		{
			//if (acc->staffID == staffID)
			//{
			acc->custID = custID;
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
		}
		else
		{
			std::cout << "\n\nInvalid Old Password.Please try again or click 'q' to cancel update." << std::endl;
			pw.clear();
			//std::cin.ignore();
			change = false;
		}
	} while (!change);

	int status1 = accManager.updateAccPwC(acc);
	status = status1;
}

void CustInterface::UpdateProfile(int custid)
{
	CustManager custManager;
	Customer* cust = new Customer();
	char update;
	int status, success;
	std::string buffer;
	std::cout << std::endl;
	std::cout << "*************************************************************************************************";
	std::cout << "\n                                       Update Profile";
	std::cout << "\n*************************************************************************************************";
	cust->custID = custid;
	//std::cout << "\n\nCustomer ID: " << cust->custID;
	//ClrSn();
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\tProfile Details";
	std::cout << "\n*************************************************************************************************\n";
	selectOneCust(custid);
	if (cust->custID != 0) 
	{
		std::cout << "\n\nPlease select the details of the menu that you want to update: " << std::endl;
		std::cout << "==================================================================";
		std::cout << "\n1. Name";
		std::cout << "\n2. IC Number";
		std::cout << "\n3. Address";
		std::cout << "\n4. Email address";
		std::cout << "\n5. Phone number";
		std::cout << "\n6. Password";
		std::cout << "\n7. Cancel Update";
		std::cout << "\n==================================================================";
		do {
			int choice;
			int lastDigit;
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
				std::getline(std::cin, cust->name);
				break;
			case 2:
				do{
				std::cout << "Update IC Number (XXXXXX-XX-XXXX): ";
				std::getline(std::cin, cust->custIC);
				} while (!std::regex_match(cust->custIC, std::regex(R"(\d{6}-\d{2}-\d{4})")));
				lastDigit = cust->custIC.back() - '0';
				cust->gender = (lastDigit % 2 == 0) ? "Female" : "Male";
				break;
			case 3:
				std::cout << "Update Address: ";
				std::getline(std::cin, cust->address);
				break;
			case 4:
				std::cout << "Update Email Address: ";
				std::getline(std::cin, cust->email);
				break;
			case 5:
				do {
					std::cout << "Update Phone Number (XXX-XXX XXXX): ";
					std::getline(std::cin, cust->phoneNo);
				} while (!std::regex_match(cust->phoneNo, std::regex(R"(\d{3}-\d{3} \d{4}|\d{3}-\d{4} \d{4})")));
				break;
			case 6:
				editPw(custid, success);
				break;
			case 7:
				std::cout << "Update cancelled";
				return;
			default:
				std::cout << "Invalid choice. Please choose again.";
				return;
			}

			CustManager custManager; //use this to add menu to databasex
			if (choice != 6)
				status = custManager.updateCust(cust);
			else if (choice == 6)
				status = success;
			if (status != 0)
				std::cout << "\n\nSuccessfully updated your profile." << std::endl;
			else
				std::cout << "\n\nSorry, unable to update your profile." << std::endl;
			do {
				std::cout << "Do you still want to update other attributes of your profile? (Y/N): ";
				std::cin >> update;
			} while (update != 'Y' && update != 'y' && update != 'N' && update != 'n');
			std::cin.ignore(); //so that this won't bring to the next quetion
		} while (update == 'y' || update == 'Y');
	}
	else std::cout << "User not found";

	std::cout << "*************************************************************************************************";
	std::cout << "  \n                                Updated Profile Details";
	std::cout << "\n*************************************************************************************************";
	selectOneCust(custid);
	system("pause");
	return;
}

void CustInterface::viewOrderbyUser(int custid)
{
	OrderManager orderManager;
	OrderList* orders = orderManager.getCustOrders(custid);
	MenuManager menuManager;

	std::cout << "\n****************************************************************************************************************************************************";
	std::cout << "\n\t\t\t\t\t\t\t\t\t\tYour Order";
	std::cout << "\n****************************************************************************************************************************************************";
	std::cout << "\n" << std::internal << std::setw(10) << "Order ID" << std::setw(10) << "Menu ID"
		<< std::setw(25) << "Food Name" << std::setw(10) << "Quantity" << std::setw(10) << "Price" << std::setw(10) << "Discount"
		<< std::setw(25) << "Order Date" << std::setw(20) << "Pick Up/Delivery" << std::setw(20) << "Payment Method";
	std::cout << "\n****************************************************************************************************************************************************";
	if (orders != NULL) {
		OrderList* order = orders;

		do
		{
			std::cout << "\n" << std::internal << std::setw(10) << order->orderID << std::setw(10) << order->menuID;
			Menu* menu = menuManager.getMenu(order->menuID);
			std::cout << std::internal << std::setw(25) << menu->name << std::setw(10) << order->quantity << std::setw(10) << order->tPrice << std::setw(10) << order->discount
				<< std::setw(25) << order->oDateTime << std::setw(20) << order->delivery << std::setw(20) << order->payMethod;
			order = order->next;
		} while (order != NULL);
	}
	else
	{
		std::cout << "\nEmpty. Try and make some orders to try our food!\n";
	}
	std::cout << "\n****************************************************************************************************************************************************";
}

