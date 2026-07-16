#pragma once
#include<string>

class Product
{
private:
	int productId;
	std::string name;
	std::string description;
	int quantity;
	double price;
	int reorderLevel;

public:
	Product(int productId_, std::string name_, std::string description_,
		int quantity_, double price_, int reorderLevel_) { }

	void updateQuantity(int delta);

	void updatePrice(double newPrice);

	bool isLowStock();



}