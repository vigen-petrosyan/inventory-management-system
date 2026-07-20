#pragma once
#include "Inventory.h"
#include "DatabaseManager.h"

class InventoryService
{
private:
	Inventory inventory;
	DatabaseManager db;

public:
	InventoryService(Inventory&& inventory_,
		DatabaseManager&& db_);

	void addNewProduct(const std::shared_ptr<Product>& product_);
	void updateProductStock(int id, int delta, const std::string& note);

	std::vector<std::shared_ptr<Product>> generateReorderList() const;
	void loadFromDatabase();
};