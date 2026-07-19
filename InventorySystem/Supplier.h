#pragma once
#include<string>

class Supplier
{
private:
	int id;
	std::string name;
	std::string contactEmail;
	std::string phone;
	std::string address;

public:
	Supplier(int id_, std::string name_,
		std::string contactEmail_, std::string phone_,
		std::string address_);

	int getId() const;
	std::string getName() const;
	std::string getContactEmail() const;
	std::string getPhone() const;
	std::string getAddress() const;

	void setId(int id_);
	void setName(const std::string& name_);
	void setContactEmail(const std::string& contactEmail_);
	void setPhone(const std::string& phone_);
	void setAddress(const std::string& address_);

	void printDetails() const;
	
};