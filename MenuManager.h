#include"Menu.h"

//#include<string>
#include<ctime>
//using namespace std;

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

class MenuManager
{
public:
	//can add, delete, update
	int addMenu(Menu* menu);
	int updateMenu(Menu* menu);
	int deleteMenu(Menu* menu);
	bool menuExists(std::string menu_id);
	//Menu* getPrice(std::string menu_id);
	//can get one or select many
	Menu* getRandMenu();
	Menu* getMenu(std::string menu_id);
	//Menu* getMenuDetails(const std::string& menuId, Menu& menu);
	Menu* getMenuN(std::string name);
	Menu* getMenus();
	Menu* getcustMenus();
	Menu* getAllMenuID();
	Menu* getMenu(double minPrice);
	Menu* getMenus(double maxPrice);
	//can overload(same name diff datatype)
	//these all r overloading also coz using same function name: getMenu, if want to change to getMenuById, getMenuByName also can
};

#endif
#pragma once
