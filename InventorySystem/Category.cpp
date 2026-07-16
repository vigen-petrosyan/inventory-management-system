#include "Category.h"

Category::Category(int categoryId, std::string name, std::string description) :
	categoryId(categoryId), name(name), description(description){ }

int Category::getCategoryId() const { return categoryId; }

std::string Category::getDescription() const { return description; }

std::string Category::getName() const { return name; }
