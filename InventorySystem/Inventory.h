#pragma once
#include<unordered_map>
#include<memory>
#include<vector>
#include "StockTransaction.h"
class Product;
class Category;
class Supplier;


class Inventory
{
private:
	std::unordered_map<int, std::shared_ptr<Product>> products;
	std::unordered_map<int, std::shared_ptr<Category>> categories;
	std::unordered_map<int, std::shared_ptr<Supplier>> suppliers;
	std::vector<StockTransaction> sessionTransactions;

public:
	Inventory(std::unordered_map<int, std::shared_ptr<Product>> products_,
		std::unordered_map<int, std::shared_ptr<Category>> categories_,
		std::unordered_map<int, std::shared_ptr<Supplier>> suppliers_,
		std::vector<StockTransaction> sessionTransactions_);	

	bool addProduct(const std::shared_ptr<Product>& p);
	bool removeProduct(int productId);
	std::shared_ptr<Product> findProduct(int productId);
	std::vector<Product> listProducts();
	const std::unordered_map<int, std::shared_ptr<Product>>& getProducts() const;

	bool updateStock(int productId, int delta);
	bool assignCategory(int productId, int categoryId);
	bool assignSupplier(int productId, int supplierId);
	void recordTransaction(const StockTransaction& tx);

	bool addCategory(const std::shared_ptr<Category>& c);
	bool addSupplier(const std::shared_ptr<Supplier>& s);

};