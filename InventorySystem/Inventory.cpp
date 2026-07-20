#include "Inventory.h"
#include"Product.h"
#include "Category.h"
#include "Supplier.h"
#include <utility>

Inventory::Inventory(std::unordered_map<int, std::shared_ptr<Product>> products_,
	std::unordered_map<int, std::shared_ptr<Category>> categories_,
	std::unordered_map<int, std::shared_ptr<Supplier>> suppliers_,
	std::vector<StockTransaction> sessionTransactions_)
	: products(std::move(products_)),
	categories(std::move(categories_)),
	suppliers(std::move(suppliers_)),
		sessionTransactions(sessionTransactions_){ }


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
const std::unordered_map<int, std::shared_ptr<Product>>& Inventory::getProducts() const {
	return products;
}

bool Inventory::updateStock(int productId, int delta)
{
	auto it = products.find(productId);
	if (it == products.end()) { return false; }
	it->second->updateQuantity(delta);
	return true;
}



bool Inventory::assignSupplier(int productId, int supplierId)
{
	auto prodIt = products.find(productId);
	if (prodIt == products.end()) {
		return false; 
	}

	auto suppIt = suppliers.find(supplierId);
	if (suppIt == suppliers.end()) {
		return false; 
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

bool Inventory::addCategory(const std::shared_ptr<Category>& c) {
	if (!c || categories.find(c->getId()) != categories.end()) return false;
	categories[c->getId()] = c;
	return true;
}
bool Inventory::addSupplier(const std::shared_ptr<Supplier>& s) {
	if (!s || suppliers.find(s->getId()) != suppliers.end()) return false;
	suppliers[s->getId()] = s;
	return true;
}



