#include "Supplier.h"
#include <iostream>

Supplier::Supplier(int id_, std::string name,
    std::string contactEmail, std::string phone, std::string address) :
    id(id_), name(name), contactEmail(contactEmail),
    phone(phone), address(address){ }
   

std::string Supplier::getAddress() const { return this->address; }
std::string Supplier::getContactEmail() const { return this->contactEmail; }
std::string Supplier::getName() const { return this->name; }
std::string Supplier::getPhone() const { return this->phone; }
int Supplier::getId() const { return id; }


void Supplier::setId(int id_) { id = id_; }
void Supplier::setName(const std::string& name_) { name = name_; }
void Supplier::setAddress(const std::string& address_) { address = address_; }
void Supplier::setContactEmail(const std::string& email) { contactEmail = email; }
void Supplier::setPhone(const std::string& phone_) { phone = phone_; }

void Supplier::printDetails() const
{
    std::cout << "Supplier ID --- " << id << '\n' <<
        "Name --- " << name << '\n' << "Contact email --- " <<
        contactEmail << '\n' << "Phone --- " << phone << '\n' <<
        "Address --- " << address << '\n';

}
