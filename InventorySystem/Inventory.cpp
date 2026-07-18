#include "Inventory.h"
#include"Product.h"

Inventory::Inventory(std::unordered_map<int, std::shared_ptr<Product>> products_,
	std::unordered_map<int, std::shared_ptr<Category>> categories_,
	std::unordered_map<int, std::shared_ptr<Supplier>> suppliers_,
	std::vector<StockTransaction> sessionTransactions_)
	: products(std::move(products_)),
	categories(std::move(categories_)),
	suppliers(std::move(suppliers_)),
		sessionTransactions(sessionTransactions){ }



bool Inventory::addProduct(const std::shared_ptr<Product>& p)
{
	int id = p->getProductId();

	if (products.find(id) != products.end()) { return false; }

	products[id] = p;
	return true;
}

bool Inventory::removeProduct(int productId)
{
	auto it = products.find(productId);

	if (it == products.end()) { return false; }

	products.erase(it);

	return true;

}

std::shared_ptr<Product> Inventory::findProduct(int productId)
{
	auto it = products.find(productId);
	if (it == products.end()) { return nullptr; }

	return it->second;
}

std::vector<Product> Inventory::listProducts()
{
	std::vector<Product> listProducts;

	listProducts.reserve(products.size());
	
	for (const auto& [key,value]:products)
	{
		listProducts.push_back(*value);                
	}

	return listProducts;
}

bool Inventory::updateStock(int productId, int delta)
{
	auto it = products.find(productId);

	if (it == products.end()) { return false; }

	it->second->updateQuantity(delta);
}

bool Inventory::assignSupplier(int productId, int supplierId)
{
	auto prodIt = products.find(productId);
	if (prodIt == products.end()) {
		return false; // Product not found
	}

	auto suppIt = suppliers.find(supplierId);
	if (suppIt == suppliers.end()) {
		return false; // Supplier not found
	}

	prodIt->second->setSupplier(suppIt->second);

	return true;
}

bool Inventory::assignCategory(int productId, int categoryId)
{
	auto prodIt = products.find(productId);
	if (prodIt == products.end()) { return false; }

	auto catIt = categories.find(categoryId);
	if (catIt == categories.end()) { return false; }

	prodIt->second->setCategory(catIt->second);

	return true;
}

void Inventory::recordTransaction(const StockTransaction& tx)
{
	sessionTransactions.push_back(tx);
}




