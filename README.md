# C++ Inventory Management System

A robust, object-oriented inventory management system built in C++17. This application tracks products, categories, suppliers, and stock transactions, featuring real-time persistence using the MySQL X DevAPI.

## Features

* **Product Management:** Add, update, and track products including pricing and stock quantities.
* **Supplier & Category Categorization:** Organize products by category and link them directly to supplier profiles.
* **Transaction Logging:** Keep a historical record of all stock changes (incoming/outgoing) with timestamps and notes.
* **Automated Stock Alerts:** Identify items that fall below custom reorder levels using `generateReorderList()`.
* **Database Persistence:** Seamless MySQL integration using `mysqlx` for robust data storage.

## Project Structure

* `DatabaseManager`: Handles all MySQL X DevAPI connections, queries, and data mapping.
* `InventoryService`: The core business logic layer coordinating memory state and database synchronization.
* `Inventory`: In-memory data store using fast `std::unordered_map` lookups for products, categories, and suppliers.
* **Domain Models:** `Product`, `Category`, `Supplier`, `StockTransaction`.

## Prerequisites

To compile and run this project, you will need:
* A C++17 compatible compiler (GCC, Clang, or MSVC)
* [MySQL Server](https://dev.mysql.com/downloads/mysql/) (v8.0+ recommended)
* [MySQL Connector/C++](https://dev.mysql.com/downloads/connector/cpp/) (Ensure X DevAPI support is installed)

## Database Setup

1. Log into your MySQL server as root or an admin user.
2. Run the following SQL script to create the `InventorySystem` database and required tables:

```sql
-- 1. Create and use the schema referenced in DatabaseManager::connect()
CREATE DATABASE IF NOT EXISTS InventorySystem;
USE InventorySystem;

-- 2. Create the Category table
CREATE TABLE category (
    id INT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT
);

-- 3. Create the Supplier table
CREATE TABLE supplier (
    id INT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    contact_email VARCHAR(255),
    phone VARCHAR(50),
    address TEXT
);

-- 4. Create the Products table
CREATE TABLE products (
    id INT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    quantity INT DEFAULT 0,
    price DECIMAL(10, 2) NOT NULL,
    reorder_level INT DEFAULT 0,
    category_id INT,
    supplier_id INT,
    FOREIGN KEY (category_id) REFERENCES category(id),
    FOREIGN KEY (supplier_id) REFERENCES supplier(id)
);

-- 5. Create the Transactions table
CREATE TABLE transactions (
    tx_id INT PRIMARY KEY,
    product_id INT,
    date DATETIME,
    quantity INT NOT NULL,
    type VARCHAR(50) NOT NULL,
    notes TEXT,
    FOREIGN KEY (product_id) REFERENCES products(id)
);
