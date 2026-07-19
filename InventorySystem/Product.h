#pragma once
#include<string>
#include<memory>

class Supplier;
class Category;

class Product
{
private:
	int id;
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

	std::string getName() const;

	std::string getDescription() const;

	int getQuantity() const;

	double getPrice() const;

	int getReorderLevel() const;

	int getCategoryId() const;

	int getSupplierId() const;

	void setId(int productId_);

	void setName(std::string name_) ;

	void setDescription(std::string description_) ;

	void setQuantity(int quantity_);

	void setPrice(double price);
	
	void setReorderLevel(int reorderdLevel_);

	void setSupplier(std::shared_ptr<Supplier> newSupplier);

	void setCategory(std::shared_ptr<Category> newCategory);

	void updateQuantity(int delta);

	void updatePrice(double newPrice);

	bool isLowStock() const;



};