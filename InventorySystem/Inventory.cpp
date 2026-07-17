#include "Inventory.h"
#include"Product.h"

Inventory::Inventory(std::unordered_map<int, Product> products_, std::unordered_map<int, 
	Category> categories_, std::unordered_map<int, Supplier> suppliers_):
	products(products_), categories(categories_), suppliers(suppliers_){ }

bool Inventory::addProduct(const Product& p)
{
	int id = p.getProductId();

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

std::optional<Product> Inventory::findProduct(int productId)
{
	auto it = products.find(productId);
	if (it == products.end()) { return std::nullopt; }

	return it->second;
}

std::vector<Product> Inventory::listProducts()
{
	std::vector<Product> result;

	result.reserve(products.size());
	
	for (const auto& [key,value]:products)
	{
		result.push_back(value);
	}
	return result;
}

bool Inventory::updateStock(int productId, int delta)
{
	auto it = products.find(productId);

	if (it == products.end()) { return false; }

	it->second.updateQuantity(delta);
}

//bool Inventory::assignCategory(int productId, int categoryId)
//{
//	auto it = products.find(productId);
//
//	if (it == products.end()) { return false; }
//
//	it->second.setCategory(categoryId);
//
//	return true;
//}
//
//bool Inventory::assignSupplier(int productId, int supplierId)
//{
//	auto it = products.find(productId);
//
//	if (it == products.end()) { return false; }
//
//	it->second.setSupplier(supplierId);
//
//	return true;
//}
