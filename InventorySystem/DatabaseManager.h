#pragma once
#include<mysqlx/xdevapi.h>
#include<string>
#include<memory>
#include<vector>

class Product;
class Category;
class Supplier;
class StockTransaction;

class DatabaseManager
{
private:
	std::string connectionString;
	std::unique_ptr<mysqlx::Session> session;
	std::unique_ptr<mysqlx::Schema> db;
	
public:
	DatabaseManager(std::string connectionString_, std::unique_ptr<mysqlx::Schema> db_);

	bool connect();
	void disconnect();


	std::shared_ptr<Category> loadCategory(int id_);
	std::shared_ptr<Supplier> loadSupplier(int id_);
	std::shared_ptr<Product> loadProduct(int id_);

	void saveCategory(const Category& c);
	void saveSupplier(const Supplier& s);
	void saveProduct(const Product& p);

	std::vector<std::shared_ptr<Product>> loadAllProducts();

	void saveTransaction(const StockTransaction& tx);


};