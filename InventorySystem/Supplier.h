#pragma once
#include<string>

class Supplier
{
private:
	int supplierId;
	std::string name;
	std::string contactEmail;
	std::string phone;
	std::string address;

public:
	Supplier(int supplierId, std::string name,
		std::string contactEmail, std::string phone,
		std::string address);
	int getSupplierId() const;
	std::string getName() const;
	std::string getContactEmail() const;
	std::string getPhone() const;
	std::string getAddress() const;

	void setContactEmail(const std::string& email);
	void setPhone(const std::string& phone);

	void printDetails() const;
};