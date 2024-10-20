/*#include<string>
using namespace std;*/
#ifndef MENU_H
#define MENU_H

class Menu
{
public :
	std::string menu_id, name, description, status;
	double price;
	Menu* next; //the next variable can point to the another data
};

#endif
#pragma once
