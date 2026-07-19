#include "Product.h"
#include "Category.h"
#include "Supplier.h"

Product::Product(int productId_, std::string name_, std::string description_,
	int quantity_, double price_, int reorderLevel_) :
	productId(productId_), name(name_), description(description_),
	quantity(quantity_), price(price_), reorderLevel(reorderLevel_){ }


std::string Product::getName() const { return name; }

std::string Product::getDescription() const { return description; }

int Product::getQuantity() const { return quantity; }

double Product::getPrice() const { return price; }

int Product::getReorderLevel() const { return reorderLevel; }

int Product::getCategoryId() const { return category->getId(); }

int Product::getSupplierId() const { return supplier->getId(); }

int Product::getProductId() const { return productId; }

void Product::setId(int id_) { id = id_; }

void Product::setName(std::string name_) { name = name_; }

void Product::setPrice(double price_) { price = price_; }

void Product::setQuantity(int quantity_) { quantity = quantity_; }

void Product::setReorderLevel(int reorderLevel_) { reorderLevel = reorderLevel_; }

void Product::setDescription(std::string description_) { description = description_; }

void Product::setSupplier(std::shared_ptr<Supplier> newSupplier) {
	supplier = std::move(newSupplier);
}

void Product::setCategory(std::shared_ptr<Category> newCategory)
{
	category = std::move(newCategory);
}

bool Product::isLowStock() const { return quantity <= reorderLevel; }

void Product::updatePrice(double newPrice) { price = newPrice; }



void Product::updateQuantity(int delta) { quantity += delta; }
