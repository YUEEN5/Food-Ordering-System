#include "DatabaseConnection.h"

DatabaseConnection::DatabaseConnection()
{
	sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
	//sql::Connection* 
	connection = driver->connect("tcp://127.0.0.1:3306", "root", "");

	connection->setSchema("fos_ws1");
}

DatabaseConnection::~DatabaseConnection()
{
	connection->close();

	delete connection;
}

sql::PreparedStatement* DatabaseConnection::prepareStatement(std::string query)
{
	return connection->prepareStatement(query);
}

//if want to change database, attribute from 1 server to 1 server or change username or server
//just need to change in databaseconnection, no need to change in many places