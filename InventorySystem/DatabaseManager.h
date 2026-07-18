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
	
public:
	DatabaseManager(std::string connectionString_, std::unique_ptr<mysqlx::Session> session_);

	bool connect();

	void disconnect();

	bool saveProduct(Product p);

	std::shared_ptr<Product> loadProduct(int productId);

	bool saveCategory(Category c);

	bool saveSupplier(Supplier s);

	std::vector<Product> loadAllProducts();

	bool saveTransaction(StockTransaction tx);


};