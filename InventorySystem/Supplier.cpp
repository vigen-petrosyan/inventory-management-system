#include "Supplier.h"
#include <iostream>

Supplier::Supplier(int supplierId, std::string name,
    std::string contactEmail, std::string phone, std::string address) :
    supplierId(supplierId), name(name), contactEmail(contactEmail),
    phone(phone), address(address){ }
   

std::string Supplier::getAddress() const { return this->address; }
std::string Supplier::getContactEmail() const { return this->contactEmail; }
std::string Supplier::getName() const { return this->name; }
std::string Supplier::getPhone() const { return this->phone; }

int Supplier::getSupplierId() const { return this->supplierId; }

void Supplier::setContactEmail(const std::string& email) { this->contactEmail = email; }
void Supplier::setPhone(const std::string& phone) { this->phone = phone; }

void Supplier::printDetails() const
{
    std::cout << "Supplier ID --- " << supplierId << '\n' <<
        "Name --- " << name << '\n' << "Contact email --- " <<
        contactEmail << '\n' << "Phone --- " << phone << '\n' <<
        "Address --- " << address << '\n';

}
