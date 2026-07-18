#pragma once
#include<ctime>
#include<string>
#include<memory>

class Product;

class StockTransaction
{
private:
	int txId;
	int productId;
	time_t date;
	int quantity;
	std::string type;
	std::string notes;
	std::shared_ptr<Product> product;

public:
	StockTransaction(int txId_, int productId_, time_t date_, int quantity_,
		std::string type_, std::string notes_, std::shared_ptr<Product> product_);
};