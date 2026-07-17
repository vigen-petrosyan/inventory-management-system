#pragma once
#include<ctime>
#include<string>

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

};