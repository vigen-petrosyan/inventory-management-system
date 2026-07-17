#pragma once
#include<unordered_map>

class Product;
class Category;
class Supplier;
class StockTransaction; 

class Inventory
{
private:
	std::unordered_map<int, Product> products;
	std::unordered_map<int, Category> categories;
	std::unordered_map<int, Supplier> suppliers;

public:
	Inventory(std::unordered_map<int, Product> products_, std::unordered_map<int, Category> categories_,
		std::unordered_map<int, Supplier> suppliers_);

	bool addProduct(Product p);
	bool removeProduct(int productId);
	Product findProduct(int productId);
	std::vector<Product> listProducts();
	bool updateStock(int productId, int delta);
	bool assignCategory(int productId, int categoryId);
	bool assignSupplier(int productId, int supplierId);
	void recordTransaction(const StockTransaction& tx);
};