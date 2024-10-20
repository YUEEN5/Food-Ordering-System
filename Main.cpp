#include <iostream>
#include <cstring>
#include <conio.h> //for password encrypt
#include <cstdlib>
#include <ctime>
#include <limits> //for clear buffer
#include <chrono> //for delay
#include <thread> //for delay
#include <windows.h> //for color

#include "CustManager.h"
#include "CustInterface.h"
#include "AmInterface.h"
#include "MenuManager.h"
#include "StaffManager.h"
//#include "Customer.h"
#include <mysql/jdbc.h>
//using namespace sql;

//#define GREEN   "\033[32m" //for color

//function declaration for basic function
int main();
void ClearScreen();
void displayWelcome();
void displayEnd();
void displayPayInfo();
//function declaration for register, login, and menu
void Registration();
void LogIn();
void AdminMenu();
void CustomerMenu(int custID);


void ClearScreen()
{
	std::system("cls");
}

void displayPayInfo()
{
	std::cout << "\n========================================================================================================" << std::endl;
	std::cout << "\t\t\t\tOnline Transfer information\n";
	std::cout << "========================================================================================================" << std::endl;
	std::cout << "\nBank Account: \n9304849542 \nHong Leong Bank \nJoanne Lim Jia Jia"
		<< "\n\nTng Ewallet: 012 904 5934" << std::endl;
	std::cout << "========================================================================================================" << std::endl;
	std::cout << "\t\t\t\tPick Up information\n";
	std::cout << "========================================================================================================" << std::endl;
	std::cout << "\nPick Up Point: No.10, Jalan Wawa 2, Taman Bahagia Wawa, Melaka.";
	std::cout << "\nPick Up Time: 12.00pm to 1.00pm";
	std::cout << "\n========================================================================================================" << std::endl;
	system("pause");
}

void displayWelcome()
{
	std::cout << "\n=====================================================================================================================\n";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	std::cout << "\n\n\t\t\t\t\tWelcome to Lucky's Food Ordering System\n\n";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "\n=====================================================================================================================\n";
	/*std::cout << "1. Sign Up" << std::endl;
	std::cout << "2. Log in" << std::endl;
	std::cout << "3. Exit" << std::endl;*/
}

void displayEnd()
{
	std::cout << "\n==================================================================================================================\n\n";
	std::cout << "\n\t\t\t\t\tThank you and Goodbye!\n\n";
	std::cout << "\n==================================================================================================================\n\n";
	std::chrono::seconds duration(2);
	std::this_thread::sleep_for(duration);
	ClearScreen();
}

void viewReport()
{
	AmInterface amInterface;
	CustInterface custInterface;
	int choice;
	char again;
	do {
		ClearScreen();
		std::cout << "\n***********************************************************************************************************";
		std::cout << "\n\t\t\t\t\tLucky's Food Sales Report";
		std::cout << "\n***********************************************************************************************************";
		std::cout << std::endl << std::endl;
		std::cout << " 1. View all Orders" << std::endl;
		std::cout << " 2. View Customer's Feedback" << std::endl;
		std::cout << " 3. View Daily Report" << std::endl;
		std::cout << " 4. View Monthly Report" << std::endl;
		std::cout << " 5. View Yearly Report" << std::endl;
		std::cout << " 6. View Overall Report" << std::endl;
		std::cout << " 7. Back to Staff's Menu" << std::endl;
		std::cout << "\n***********************************************************************************************************";
		while (true) {
			try {
				std::cout << "\nPlease select your choice (1-7): "; std::cin >> choice;
				std::cin.ignore();
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
				std::cin.ignore(999, '\n');
			}
		}
		switch (choice)
		{
		case 1:
			ClearScreen();
			amInterface.viewOrders();
			break;
		case 2:
			ClearScreen();
			custInterface.viewFeedback();
			break;
		case 3:
			ClearScreen();
			amInterface.DailySales();
			break;
		case 4:
			ClearScreen();
			amInterface.chooseMonthlySales();
			break;
		case 5:
			ClearScreen();
			amInterface.YearlySales();
			break;
		case 6:
			ClearScreen();
			amInterface.overallSales();
			break;
		case 7:
			return;
		default:
			std::cout << "Invalid option. Please select again (1-5): ";
			break;
		}
		do {
			std::cout << "\nDo you still want to view other report details? (Y/N): ";
			std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	} while (again == 'Y' || again == 'y');
}

void manageCust()
{
	AmInterface amInterface;
	CustInterface custInterface;
	CustManager custManager;
	int choice, custID;
	char again;
	do {
		ClearScreen();
		std::cout << "\n***********************************************************************************************************";
		std::cout << "\n\t\t\t\t\t\tManage Customer";
		std::cout << "\n***********************************************************************************************************";
		std::cout << std::endl << std::endl;
		std::cout << " 1. Add Customer" << std::endl;
		std::cout << " 2. Delete Customer" << std::endl;
		std::cout << " 3. Update Customer's Profile" << std::endl;
		std::cout << " 4. View all Customer" << std::endl;
		std::cout << " 5. Back to Staff's Menu" << std::endl;
		std::cout << "\n***********************************************************************************************************";
		while (true) {
			try {
				std::cout << "\nPlease select your choice (1-5): "; std::cin >> choice;
				//std::cin.ignore();
				// Check if the input was successful
				if (std::cin.fail() || choice < 1 || choice > 5) {
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
				std::cin.ignore(999, '\n');
			}
		}
		switch (choice)
		{
		case 1:
			ClearScreen();
			std::cout << "\n***********************************************************************************************************";
			std::cout << "\n\t\t\t\t\t\tAdd Customer";
			std::cout << "\n***********************************************************************************************************";
			std::cout << "\nClick 'q' to go back to Main Menu. " << std::endl << std::endl;
			
			custInterface.SignUpCust(custID);
			break;
		case 2:
			ClearScreen();
			amInterface.viewAllCustID();
			amInterface.deleteC();
			break;
		case 3:
			ClearScreen();
			amInterface.viewAllCustID();
			std::cout << "\nClick '0' to go back to Main Menu. " << std::endl << std::endl;
			do {
				while (true) {
					try {
						std::cout << "\nPlease enter the customer ID that you want to update: ";
						std::cin >> custID;
						std::cin.ignore();
						// Check if the input was successful
						if (std::cin.fail()) {
							std::cerr << "Invalid input. Please enter a valid number." << std::endl;

							// Clear the error state
							std::cin.clear();

							// Discard the invalid input
							//custID = 0;
							std::cin.ignore();
							continue;  // Continue the loop after handling the error
						}
						if (custID == 0)
						{
							return;
						}
						break;
					}
					catch (const std::exception& e) {
						// Catch and display any exceptions that might occur
						std::cerr << "Error: " << e.what() << std::endl;
						std::cin.ignore();
					}
				}
				if (custManager.custExists(custID))//menu exists 
				{
					custInterface.UpdateProfile(custID);
					break;
				}
				else
					std::cout << "Customer not found";
			} while (!custManager.custExists(custID));
			break;
		case 4:
			ClearScreen();
			amInterface.viewCust();
			break;
		case 5:
			return;
		default:
			std::cout << "Invalid option. Please select again (1-5): ";
			break;
		}
		do {
			std::cout << "\nDo you still want to manage customer's info? (Y/N): ";
			std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	} while (again == 'Y' || again == 'y');
}

void manageMenu()
{
	AmInterface amInterface;
	CustInterface custInterface;
	int choice;
	char again;
	do {
		ClearScreen();
		std::cout << "\n***********************************************************************************************************";
		std::cout << "\n\t\t\t\t\t\tManage Menu";
		std::cout << "\n***********************************************************************************************************";
		std::cout << std::endl << std::endl;
		std::cout << " 1. Add Menu" << std::endl;
		std::cout << " 2. Delete Menu" << std::endl;
		std::cout << " 3. Update Menu" << std::endl;
		std::cout << " 4. View all Menu" << std::endl;
		std::cout << " 5. View Customer's Feedback" << std::endl;
		std::cout << " 6. Back to Staff's Menu" << std::endl;
		std::cout << "\n***********************************************************************************************************";
		while (true) {
			try {
				std::cout << "\nPlease select your choice (1-6): "; std::cin >> choice;
				//std::cin.ignore();
				// Check if the input was successful
				if (std::cin.fail() || choice < 1 || choice > 6) {
					throw std::invalid_argument("Invalid input. Please enter a valid number. (1-6)");
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
		switch (choice)
		{
		case 1:
			ClearScreen();
			amInterface.viewMenu();
			amInterface.addNewMenu();
			break;
		case 2:
			ClearScreen();
			amInterface.viewMenu();
			amInterface.deleteM();
			break;
		case 3:
			ClearScreen();
			amInterface.viewMenu();
			amInterface.updateM();
			break;
		case 4:
			ClearScreen();
			amInterface.viewMenu();
			break;
		case 5:
			ClearScreen();
			custInterface.viewFeedback();
			break;
		case 6:
			return;
		default:
			std::cout << "Invalid option. Please select again (1-6): ";
			break;
		}
		do {
			std::cout << "\nDo you still want to manage menu's info? (Y/N): ";
			std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	} while (again == 'Y' || again == 'y');
}

void manageStaff(int staffID)
{

	AmInterface amInterface;
	//CustInterface custInterface;
	StaffManager staffManager;
	Staff* staff = staffManager.getStaff(staffID);
	int choice, ID;
	char again;
	do {
		ClearScreen();
		std::cout << "\n***********************************************************************************************************";
		std::cout << "\n\t\t\t\t\t\tManage Profile";
		std::cout << "\n***********************************************************************************************************";
		std::cout << std::endl << std::endl;
		std::cout << " 1. View Profile" << std::endl;
		std::cout << " 2. Update Profile" << std::endl;
		std::cout << " 3. Update Staff's Profile (ADMIN only)" << std::endl;
		std::cout << " 4. Delete Staff (ADMIN only)" << std::endl;
		std::cout << " 5. View all Staff's Profile (ADMIN only)" << std::endl;
		std::cout << " 6. Back to Staff's Menu" << std::endl;
		std::cout << "\n***********************************************************************************************************";
		while (true) {
			try {
				std::cout << "\nPlease select your choice (1-6): "; std::cin >> choice;
				//std::cin.ignore();
				// Check if the input was successful
				if (std::cin.fail() || choice < 1 || choice > 6) {
					throw std::invalid_argument("Invalid input. Please enter a valid number. (1-6)");
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
		switch (choice)
		{
		case 1:
			ClearScreen();
			std::cout << "*************************************************************************************************\n\n";
			std::cout << "\t\t\t\t\tYour Profile\n\n";
			std::cout << "*************************************************************************************************\n\n";
			amInterface.selectOneStaff(staffID);
			break;
		case 2:
			ClearScreen();
			amInterface.editStaffProfile(staffID);
			break;
		case 3:
			if (staff->role == "ADMIN")
			{
				do {
					ClearScreen();
					amInterface.viewAllStaff();
					std::cout << "\nClick '0' to go back to Main Menu. " << std::endl << std::endl;
					while (true) {
						try {
							std::cout << "\n\nPlease enter the staff ID that you want to update: ";
							std::cin >> ID;
							//std::cin.ignore();
							// Check if the input was successful
							if (std::cin.fail()) {
								throw std::invalid_argument("Invalid input. Please enter a valid number. (1-6)");
							}
							if (ID == 0)
							{
								return;
							}
							// Input was successful, exit the loop
							break;
						}
						catch (const std::invalid_argument& e) {
							std::cout << e.what() << std::endl;
							std::cin.clear();
							std::cin.ignore(999, '\n');
						}
					}
					if (staffManager.staffExists(ID))
					{
						ClearScreen();
						amInterface.editStaffProfile(ID);
					}
					else
					{
						std::cout << "Staff not found!";
						system("pause");
					}
				} while (!staffManager.staffExists(ID));
			}
			else if (staff->role == "STAFF")
			{
				std::cout << "\n\nonly ADMIN can update other staff's profile . . . \n" << std::endl;
				system("pause");
			}
			break;
		case 4:
			if (staff->role == "ADMIN")
			{
				ClearScreen();
				amInterface.deleteS();
			}
			else if (staff->role == "STAFF")
			{
				std::cout << "\n\nonly ADMIN can delete staff . . .\n " << std::endl;
				system("pause");
			}
			break;
		case 5:
			if (staff->role == "ADMIN")
			{
				ClearScreen();
				amInterface.viewAllStaff();
			}
			else if (staff->role == "STAFF")
			{
				std::cout << "\n\nonly ADMIN can view all staff . . .\n " << std::endl;
				system("pause");
			}
			break;
		case 6:
			return;
		default:
			std::cout << "Invalid option. Please select again (1-5): ";
			break;
		}
		do {
			std::cout << "\nDo you still want to manage profile's info? (Y/N): ";
			std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	} while (again == 'Y' || again == 'y');
}

void AdminMenu(int staffID) 
{
	AmInterface amInterface;
	CustInterface custInterface;
	CustManager custManager;
	StaffManager staffManager;
	Staff* staff = staffManager.getStaff(staffID);
	Customer* cust = new Customer();
	int custID=0;
	int choice;
		char again;
		do{
		std::cout << "\n========================================================================================================\n";
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		std::cout << "\n\t\t\t\t\t\tSTAFF MAIN MENU" << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "\n========================================================================================================\n";
		std::cout << std::endl;
		std::cout << " 1. Manage Menu" << std::endl;
		std::cout << " 2. Manage Customer" << std::endl;
		std::cout << " 3. View Today's Order" << std::endl;
		std::cout << " 4. View Report" << std::endl;
		std::cout << " 5. Manage Profile" << std::endl;
		std::cout << " 6. Log out" << std::endl;
		std::cout << "\n========================================================================================================\n";
			//do {
				while (true) {
					try {
						std::cout << "Please select your choice (1-6): "; std::cin >> choice;
						//std::cin.ignore();
						// Check if the input was successful
						if (std::cin.fail() || choice < 1 || choice > 6) {
							throw std::invalid_argument("Invalid input. Please enter a valid number. (1-6)");
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
				//std::cout << "Please select your choice: "; std::cin >> choice;

				switch (choice)
				{
				case 1:
					//ClearScreen();
					manageMenu();
					break;
				case 2:
				//	ClearScreen();
					manageCust();
					break;
				case 3:
					ClearScreen();
					//amInterface.TodaySalesReport();
					amInterface.TodayOrders();
					break;
				case 4:
					//ClearScreen();
					
					if (staff->role == "ADMIN")
					{
						viewReport();
					}
					else if (staff->role == "STAFF")
					{
						std::cout << "only ADMIN can view the report . . . " << std::endl;
						system("pause");
					}
					break;
				case 5:
					manageStaff(staffID);
					break;
				case 6:
					ClearScreen();
					std::cout << "\n*************************************************************************************************\n";
					std::cout << "\n\t\t\t\t. . . . . .Logging out. . . . . ." << std::endl;
					std::cout << "\n*************************************************************************************************\n";
					std::chrono::seconds duration(3);
					std::this_thread::sleep_for(duration);
					ClearScreen();
					displayEnd();
					main();
					break;
				default:
					std::cout << "Invalid option. Please select again (1-5): ";
					break;
				}
	
				std::cout << "\n\n***** Click 'Y' to Staff's Main Menu, Click 'N' to Log out *****" << std::endl;
				do {
					std::cin.clear();
					std::cout << "\nDo you want to go back to the Staff's Menu? (Y/N): "; std::cin >> again;
				} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
			std::cin.ignore();
			ClearScreen();
		} while (again == 'Y' || again == 'y');
		ClearScreen();
		std::cout << "\n*************************************************************************************************\n";
		std::cout << "\n\t\t\t\t. . . . . .Logging out. . . . . ." << std::endl;
		std::cout << "\n*************************************************************************************************\n";
		std::chrono::seconds duration(3);
		std::this_thread::sleep_for(duration);
		ClearScreen();
		displayEnd();
		ClearScreen();
		main();
} 

void Order(int custID)
{
	CustInterface custInterface;
	int choice;
	char yes, again, lucky;
	do {
		ClearScreen();
		std::cout << "\n***********************************************************************************************************";
		std::cout << "\n\t\t\t\t\t\tOrder Manager";
		std::cout << "\n***********************************************************************************************************";
		std::cout << std::endl << std::endl;
		std::cout << " 1. Place Order" << std::endl;
		std::cout << " 2. View Your Order" << std::endl;
		std::cout << " 3. Get Your Discount Code" << std::endl;
		std::cout << " 4. Give Feedback on your last order" << std::endl;
		std::cout << " 5. Back to Customer's Menu" << std::endl;
		std::cout << "\n***********************************************************************************************************";
		while (true) {
			try {
				std::cout << "\nPlease select your choice (1-5): "; std::cin >> choice;
				//std::cin.ignore();
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
				std::cin.ignore(999, '\n');
			}
		}
		switch (choice)
		{
		case 1:
			ClearScreen();
			custInterface.viewMenu();
			custInterface.PlaceOrder(custID);
			do {
				std::cout << "\n\nDo you want to make other order? (Y/N): "; std::cin >> yes;
				if (yes == 'Y' || yes == 'y')
				{
					ClearScreen();
					custInterface.viewMenu();
					custInterface.PlaceOrder(custID);
				}
				else if (yes == 'N' || yes == 'n')
					break;
				else
					std::cout << "Invalid input. Please type again (Y or N).";
			} while (yes != 'Y' && yes != 'y' && yes != 'N' && yes != 'n');
			//displayPayInfo();
			break;
		case 2:
			ClearScreen();
			custInterface.viewOrderbyUser(custID);
			displayPayInfo();
			break;
		case 3:
			ClearScreen();
			custInterface.viewCode(custID);
			break;
		case 4:
			ClearScreen();
			custInterface.doFeedback(custID);
			break;
		case 5:
			return;
		default:
			std::cout << "Invalid option. Please select again (1-5): ";
			break;
		}
		do {
			std::cout << "\nDo you still want to manage your order? (Y/N): ";
			std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	} while (again == 'Y' || again == 'y');
}

void viewInfo(int custID)
{
	
	CustInterface custInterface;
	int choice;
	char again;
	do {
		ClearScreen();
		std::cout << "\n***********************************************************************************************************";
		std::cout << "\n\t\t\t\t\t\tView Lucky's Information";
		std::cout << "\n***********************************************************************************************************";
		std::cout << std::endl << std::endl;
		std::cout << " 1. View Menu" << std::endl;
		std::cout << " 2. View Comments" << std::endl;
		std::cout << " 3. View Online Transfer and Pick up Information" << std::endl;
		std::cout << " 4. Back to Customer's Menu" << std::endl;
		std::cout << "\n***********************************************************************************************************";
		while (true) {
			try {
				std::cout << "\nPlease select your choice (1-4): "; std::cin >> choice;
				//std::cin.ignore();
				// Check if the input was successful
				if (std::cin.fail() || choice < 1 || choice > 4) {
					throw std::invalid_argument("Invalid input. Please enter a valid number. (1-4)");
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
		switch (choice)
		{
		case 1:
			ClearScreen();
			custInterface.viewMenu();
			break;
		case 2:
			ClearScreen();
			custInterface.viewFeedback();
			break;
		case 3:
			ClearScreen();
			displayPayInfo();
			break;
		case 4:
			return;
		default:
			std::cout << "Invalid option. Please select again (1-5): ";
			break;
		}
		do {
			std::cout << "\nDo you still want to view lucky's info? (Y/N): ";
			std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	} while (again == 'Y' || again == 'y');
}

void manageProfile(int custID)
{
	CustInterface custInterface;
	int choice;
	char again;
	do {
		ClearScreen();
		std::cout << "\n***********************************************************************************************************";
		std::cout << "\n\t\t\t\t\t\tManage Profile";
		std::cout << "\n***********************************************************************************************************";
		std::cout << std::endl << std::endl;
		std::cout << " 1. View Profile" << std::endl;
		std::cout << " 2. Update Profile" << std::endl;
		std::cout << " 3. Back to Customer's Menu" << std::endl;
		std::cout << "\n***********************************************************************************************************";
		while (true) {
			try {
				std::cout << "\nPlease select your choice (1-3): "; std::cin >> choice;
				//std::cin.ignore();
				// Check if the input was successful
				if (std::cin.fail() || choice < 1 || choice > 3) {
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
				std::cin.ignore(999, '\n');
			}
		}
		switch (choice)
		{
		case 1:
			ClearScreen();
			std::cout << "*************************************************************************************************\n\n";
			std::cout << "\t\t\t\t\tYour Profile\n\n";
			std::cout << "*************************************************************************************************\n";
			custInterface.selectOneCust(custID);
			break;
		case 2:
			ClearScreen();
			custInterface.UpdateProfile(custID);
			break;
		case 3:
			return;
		default:
			std::cout << "Invalid option. Please select again (1-5): ";
			break;
		}
		do {
			std::cout << "\nDo you still want to manage your profile? (Y/N): ";
			std::cin >> again;
		} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	} while (again == 'Y' || again == 'y');
}

void CustomerMenu(int custID)
{
	CustInterface custInterface;
	int choice;
	char again, yes, lucky;
		do{
		std::cout << "\n========================================================================================================\n";
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		std::cout << "\n\t\t\t\t\tCUSTOMER MAIN MENU" << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "\n========================================================================================================\n";
		std::cout << std::endl;
		//std::cout << "\nCust ID: " << custID;
		std::cout << " 1. Grab Your Lucky Menu Now" << std::endl;
		std::cout << " 2. View Lucky's Information" << std::endl;
		std::cout << " 3. Manage Profile" << std::endl;
		std::cout << " 4. Manage Order" << std::endl;
		std::cout << " 5. Log out" << std::endl;
		std::cout << "\n========================================================================================================\n";
			//do
			//{
				while (true) {
					try {
						std::cout << "Please select your choice (1-5): "; std::cin >> choice;
						//std::cin.ignore();
						//std::cout << "Value: " << choice;
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
						std::cin.ignore(99, '\n');
					}
				}
				switch (choice)
				{
				case 1:
					ClearScreen();
					custInterface.viewRandMenu();
					do {
						std::cout << "\n\nDo you want to place order of this lucky's meal? (Y/N): ";
						std::cin >> lucky;
						if (lucky == 'Y' || lucky == 'y')
						{
							custInterface.PlaceOrder(custID);
						}
						else if (lucky == 'N' || lucky == 'n')
							std::cout << "Of course you can have other meal choice.";
						else
							std::cout << "Invalid input. Please type Y or N only.";
					} while (lucky != 'Y' && lucky != 'y' && lucky != 'N' && lucky != 'n');
					break;
				case 2:
					ClearScreen();
					viewInfo(custID);
					break;
				case 3:
					ClearScreen();
					manageProfile(custID);
					break;
				case 4:
					ClearScreen();
					Order(custID);
					break;
				case 5:
					ClearScreen();
					std::cout << "\n*************************************************************************************************\n";
					std::cout << "\n\t\t\t\t. . . . . .Logging out. . . . . ." << std::endl;
					std::cout << "\n*************************************************************************************************\n";
					std::chrono::seconds duration(3);
					std::this_thread::sleep_for(duration);
					displayEnd();
					main();
					break;
				default:
					std::cout << "Invalid option.";
				}
			//} while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7' && choice != '8');
				std::cout << "\n\n***** Click 'Y' to Staff's Main Menu, Click 'N' to Log out *****" << std::endl;
				do {
					std::cin.clear();
					std::cout << "\nDo you want to go back to the Customer's Menu? (Y/N): "; std::cin >> again;
					
				} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
			//std::cin.ignore();
			ClearScreen();
		} while (again == 'Y' || again == 'y');
		ClearScreen();
		std::cout << "\n*************************************************************************************************\n";
		std::cout << "\n\t\t\t\t. . . . . .Logging out. . . . . ." << std::endl;
		std::cout << "\n*************************************************************************************************\n";
		std::chrono::seconds duration(3);
		std::this_thread::sleep_for(duration);
		//ClearScreen();
		displayEnd();
		ClearScreen();
		main();
}

void Registration()
{
	CustInterface custInterface;
	AmInterface amInterface;
	std::string userCode;
	char c, ctnC, ctnS;
	int custID, staffID;

	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\tRegistration";
	std::cout << "\n*************************************************************************************************";
	std::cout << "\nClick 'q' to go back to Main Menu. ";
	do {
		std::cout << "\n\nEnter the code (type 'x' only if you are customer): \n";
		while ((c = _getch()) != '\r') //while the input is not 'enter'
		{
			if (c == '\b') // Check for backspace
			{
				if (!userCode.empty())
				{
					std::cout << "\b \b"; // Move the cursor back and erase the character
					userCode.pop_back();   // Remove the last character from the password
				}
			}
			else
			{
				userCode += c;
				std::cout << "*";
			}
		}
		if (userCode == "q" || userCode == "Q") {
			ClearScreen();
			main();
			return;
		}
		else if (userCode == "stafflucky99")
		{
			std::cout << "\n*************************************************************************************************";
			std::cout << "\n\t\t\t\t\tStaff Registration";
			std::cout << "\n*************************************************************************************************";
			amInterface.SignUpStaff(staffID);
			std::cout << "Do you want to continue to Staff Menu? (Y/N): ";
			std::cin >> ctnS;
			ClearScreen();
			if (ctnS == 'y' || ctnS == 'Y')
				AdminMenu(staffID);
			else if (ctnS == 'n' || ctnS == 'N')
			{
				displayEnd();
				main();
			}
		}
		else if (userCode == "x" || userCode == "X")
		{
			//ClearScreen();
			std::cout << "\n*************************************************************************************************";
			std::cout << "\n\t\t\t\t\tCustomer Registration";
			std::cout << "\n*************************************************************************************************";
			custInterface.SignUpCust(custID);
			//int id = custID;
			std::cout << "Do you want to continue to Customer Menu? (Y/N): ";
			std::cin >> ctnC;
			ClearScreen();
			if (ctnC == 'y' || ctnC == 'Y')
			{
				CustomerMenu(custID);
			}
			else if (ctnC == 'n' || ctnC == 'N')
			{
				displayEnd();
				main();
			}
		}
		else
		{
			std::cout << "Invalid code. Please try again or type 'x' to register as a customer.";
			userCode = "";
		}

	} while (userCode != "stafflucky99" && userCode != "x" && userCode != "X" && userCode != "q" && userCode != "Q");
}

void LogIn()
{
	CustInterface custInterface;
	AmInterface amInterface;
	std::string userName, accId, password;
	char p;
	bool wrong;
	do{
	std::cout << "\n*************************************************************************************************";
	std::cout << "\n\t\t\t\t\tLog In";
	std::cout << "\n*************************************************************************************************";
	std::cout << "\nClick 'q' to go back to Main Menu. ";
		std::cout << "\n\nPlease enter your username: "; 
		std::cin >> userName;
		if (userName == "q" || userName == "Q") {
			ClearScreen();
			main();
			return;
		}
		std::cout << "Please enter your password: ";
		//to encrypt the password
		while ((p = _getch()) != '\r')
		{
			if (p == '\b') // Check for backspace
			{
				if (!password.empty())
				{
					std::cout << "\b \b"; // Move the cursor back and erase the character
					password.pop_back();   // Remove the last character from the password
				}
			}
			else
			{
				password += p;
				std::cout << "*";
			}
		}

		sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
		sql::Connection* connection = driver->connect("tcp://127.0.0.1::3306", "root", ""); // or use tcp://127.0.0.1:3306

		connection->setSchema("fos_ws1");

		sql::PreparedStatement* ps = connection->prepareStatement("SELECT * FROM ACCOUNT WHERE USERNAME = ? AND PASSWORD = ?");

		ps->setString(1, userName); //index always start at 1 for sql
		ps->setString(2, password);

		sql::ResultSet* rs = ps->executeQuery(); //resultset is tabulate format
		//check if the same

		//rs->next(); //ask result to check, to go to the next line, if can return true, if cannot return false

		if (rs->next())
		{
			ClearScreen();

			std::cout << "\nHello " << rs->getString("USERNAME") << ", welcome to the food ordering system.\n";
			//the 3 in () is to get the third column value, or just direct type the column name, put ""

			if (rs->getBoolean("ADMINROLE") == 0)
			{
				int custID = rs->getInt("CUST_ID");
				CustManager custManager;
				Customer* custs = custManager.getIC(custID);

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

				if (birthMonth == currentMonth && birthDay == currentDay)
				{
					std::cout << "\n********************************************************************************************************\n";
					cout << "\n\tIt's your birthday today! Happy birthday! You will get 10% discount on your purchase!" << std::endl;
					std::cout << "\n********************************************************************************************************\n\n";
				}
				CustomerMenu(custID);
			}
			else if (rs->getBoolean("ADMINROLE") == 1)
			{
				int staffID = rs->getInt("STAFF_ID");
				AdminMenu(staffID);
			}
			wrong = false;
		}
		else
		{
			//char response;
			std::cout << "\n\n\nInvalid username or password. Please try again.\n";
			system("pause");
			//std::chrono::seconds duration(3);
			//std::this_thread::sleep_for(duration);
			//std::cin >> response;
			//if (response == 't')
			//{
				ClearScreen();
				// Clear entered username and password for the next attempt using empty string
				userName = "";
				password = "";
			//}
			//else if (response != 't')
			//{
			//	displayEnd();
			//	break;
		//	}
				wrong = true;
			
		}

		rs->close(); //close the result and clean the resource?
		ps->close();
		connection->close();

	//open first, close last (first in last out)

	//optional, delete object is not necessary
		delete rs;
		delete ps;
		delete connection;
	} while (wrong);
}

int main()
{	
	AmInterface amInterface;
	CustInterface custInterface;
	//amInterface.viewOrders();
	//custInterface.viewFeedback();
	//amInterface.YearlySales();
	//amInterface.TodayOrders();
	//std::string choice;
	//amInterface.viewAllCustID();
	int choice;
	bool invalid = true;
	displayWelcome();
	std::cout << "\n=====================================================================================================================";
	std::cout << "\n\t\t\t1. Register";
	std::cout << "\n\t\t\t2. Log In";
	std::cout << "\n\t\t\t3. Exit";
	std::cout << "\n=====================================================================================================================";
	
	while (invalid)
	{

		while (true) {
			try {
				std::cout << "\nEnter your choice (1-3): "; std::cin >> choice;
				// Check if the input was successful
				if (std::cin.fail() || choice < 1 || choice > 3) {
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

		switch (choice)
		{
		case 1:
			ClearScreen();
			Registration();
			invalid = false;
			break;

		case 2:
			ClearScreen();
			LogIn();
			invalid = false;
			break;

		case 3:
			ClearScreen();
			displayEnd();
			invalid = false;
			break;

		default:
			std::cout << "Invalid option. Please enter your choice again. (1-3)";
			invalid = true;
			break;
		}
	}

	return 0;
}