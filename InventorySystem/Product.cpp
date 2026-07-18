#include "Product.h"

Product::Product(int productId_, std::string name_, std::string description_,
	int quantity_, double price_, int reorderLevel_) :
	productId(productId_), name(name_), description(description_),
	quantity(quantity_), price(price_), reorderLevel(reorderLevel_){ }

bool Product::isLowStock() const { return quantity <= reorderLevel; }

void Product::updatePrice(double newPrice) { price = newPrice; }

int Product::getProductId() const { return productId; }

void Product::setSupplier(std::shared_ptr<Supplier> newSupplier) {
	supplier = std::move(newSupplier);
}

void Product::setCategory(std::shared_ptr<Category> newCategory)
{
	category = std::move(newCategory);
}

void Product::updateQuantity(int delta) { quantity += delta; }
