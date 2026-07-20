#pragma once
#include<string>
#include <ctime>

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

public:
	StockTransaction(int txId_, int productId_, time_t date_, int quantity_,
		std::string type_, std::string notes_);

	void setTxId(int txId_);
	void setProductId(int productId_);
	void setQuantity(int quantity_);
	void setType(const std::string& type_);
	void setNotes(const std::string& notes);

	int getTxId() const;
	int getProductId() const;
	int getQuantity() const;
	std::string getType() const;
	std::string getNotes() const;
};