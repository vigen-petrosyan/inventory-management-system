#pragma once
#include<string>

class Category
{
private:
	int id;
	std::string name;
	std::string description;

public:
	Category(int id_, std::string name_, std::string description_);

	int getId() const;

	std::string getName() const;

	std::string getDescription() const;

	void setId(int categoryId_);

	void setName(std::string name_);

	void setDescription(std::string description_);




};