#include "Category.h"

Category::Category(int id_, std::string name_, std::string description_) :
	id(id_), name(name_), description(description_){ }

int Category::getId() const { return id; }

std::string Category::getDescription() const { return description; }
std::string Category::getName() const { return name; }

void Category::setId(int id_) { id = id_; }
void Category::setName(std::string name_) { name = name_; }
void Category::setDescription(std::string description_) { description = description_; }
