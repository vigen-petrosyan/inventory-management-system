#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(std::string connectionString_, std::unique_ptr<mysqlx::Session> session_)
	:connectionString(connectionString_)
{
}
