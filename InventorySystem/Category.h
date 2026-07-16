#pragma once
#include<string>

class Category
{
private:
	int categoryId;
	std::string name;
	std::string description;

public:
	Category(int categoryId, std::string name, std::string description){}

	int getCategoryId() const;

	std::string getName() const;

	std::string getDescription() const;


};