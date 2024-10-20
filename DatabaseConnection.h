#include <string>
#include <mysql/jdbc.h>

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

class DatabaseConnection
{
private:
	sql::Connection* connection;

public: 
	DatabaseConnection(); //constructor to create the connection
	~DatabaseConnection(); //destroy an object from memory
	sql::PreparedStatement* prepareStatement(std::string query); //so the MenuManager use the databaseconnection to get the preparedstatement object
};

#endif

#pragma once
//no need to open and close