#pragma once
#include<string>
#include<memory>

class Supplier;
class Category;

class Product
{
private:
	int productId;
	std::string name;
	std::string description;
	int quantity;
	double price;
	int reorderLevel;
	std::shared_ptr<Category> category;
	std::shared_ptr<Supplier> supplier;

public:
	Product(int productId_, std::string name_, std::string description_,
		int quantity_, double price_, int reorderLevel_) {
	}

	int getProductId() const;

	void setSupplier(std::shared_ptr<Supplier> newSupplier);

	void setCategory(std::shared_ptr<Category> newCategory);

	void updateQuantity(int delta);

	void updatePrice(double newPrice);

	bool isLowStock() const;



};