#include<iostream>
#include "Product.h"
#include "DatabaseManager.h"
#include "Category.h"
#include "Supplier.h"
#include "StockTransaction.h"

DatabaseManager::DatabaseManager(std::string connectionString_)
	:connectionString(connectionString_), session(nullptr), db(nullptr){ }

bool DatabaseManager::connect()
{
    try
    {
        session = std::make_unique<mysqlx::Session>(connectionString);
        db = std::make_unique<mysqlx::Schema>(session->getSchema("InventorySystem"));
        return true;
    }
    catch (const mysqlx::Error& e)
    {
        std::cerr << "Database connection failed " << e.what() << '\n';
        return false;
    }
}
void DatabaseManager::disconnect()
{
    db = nullptr;

    if (session)
    {
        try
        {
            session->close();
        }
        catch (const mysqlx::Error& e)
        {
            std::cerr << "Warning during explicit session close " << e.what() << '\n';
        }
        session = nullptr;
    }
}


std::shared_ptr<Category> DatabaseManager::loadCategory(int id_)
{
    try
    {
        mysqlx::SqlResult result = session->sql("SELECT name, description FROM category WHERE id = ?").
            bind(id_).execute();

        auto row = result.fetchOne();
        if (!row) { return nullptr; }

        auto category = std::make_shared<Category>(id_, row[0].get<std::string>(), row[1].get<std::string>());

        return category;

    }

    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("Error during load category " + std::string(error.what()));
    }
}
std::shared_ptr<Supplier> DatabaseManager::loadSupplier(int id_)
{
    try
    {
        mysqlx::RowResult result = session->sql("SELECT name,contact_email,phone,address FROM supplier  "
            "WHERE id = ?").bind(id_).execute();

        auto row = result.fetchOne();
        if (!row) { return nullptr; }

        auto supplier = std::make_shared<Supplier>(id_, row[0].get<std::string>(), row[1].get<std::string>(),
            row[2].get<std::string>(), row[3].get<std::string>());

        return supplier;

    }

    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("Error during load supplier " + std::string(error.what()));
    }
}
std::shared_ptr<Product> DatabaseManager::loadProduct(int id_)
{

    try
    {
        mysqlx::SqlResult result = session->sql("SELECT name,description,quantity,price,reorder_level,"
            "category_id,supplier_id FROM products where products_id = ? ").bind(id_).execute();

        mysqlx::Row row = result.fetchOne();
        if (!row) { return nullptr; }



        auto product = std::make_shared<Product>(id_,row[0].get<std::string>(), row[1].get<std::string>(),
            row[2].get<int>(), row[3].get<double>(), row[4].get<int>(), loadCategory(row[5].get<int>()),
            loadSupplier(row[6].get<int>()));

        return product;
    }

    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("Error during loadProduct" + std::string(error.what()));
    }
}
std::vector<std::shared_ptr<Product>> DatabaseManager::loadAllProducts()
{
    try
    {
        mysqlx::RowResult rows = session->sql(
            "SELECT id, name, description, quantity, price, reorder_level, category_id, supplier_id "
            " FROM products"
        ).execute();

        std::vector<std::shared_ptr<Product>> allProducts;

        for (mysqlx::Row row : rows)
        {
            auto product = std::make_shared<Product>(row[0].get<int>(),row[1].get<std::string>(), row[2].get<std::string>(),
                row[3].get<int>(), row[4].get<double>(), row[5].get<int>(), loadCategory(row[6].get<int>()),
                loadSupplier(row[7].get<int>()));
            allProducts.push_back(product);
        }

        return allProducts;
    }
    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("Error during loading products: " + std::string(error.what()));
    }
}


void DatabaseManager::saveCategory(const Category& c)
{
    try
    {
        session->sql("INSERT INTO category(id,name,description)"
            "VALUES (?,?,?)").bind(c.getId(), c.getName(), c.getDescription()).execute();
        
    }

    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("Error during saving category " + std::string(error.what()));
    }
}
void DatabaseManager::saveSupplier(const Supplier& s)
{
    try
    {
        session->sql("INSERT INTO supplier (id,name,contact_email,phone,address)  VALUES(?,?,?,?,?)")
            .bind(s.getId(), s.getName(), s.getContactEmail(), s.getPhone(), s.getAddress())
            .execute();
    }
    
    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("Error during saving supplier" + std::string(error.what()));
    }
}
void DatabaseManager::saveProduct(const Product& p)
{
    try
    {
        session->sql("INSERT INTO products (product_id, name, description, quantity,"
            "price, reorder_level, category_id, supplier_id)VALUES(? , ? , ? , ? , ? , ? , ? , ? )").
            bind(p.getProductId(), p.getName(), p.getDescription(), p.getQuantity(), p.getPrice(),
                p.getReorderLevel(), p.getCategoryId(), p.getSupplierId()).execute();

    }

    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("Database failure in saveProduct:" + std::string(error.what()));
    }

}
void DatabaseManager::saveTransaction(const StockTransaction& tx)
{
    try
    {
        session->sql("INSERT INTO transactions(tx_id,product_id,date,quantity,type,notes)"
            " VALUES(?,?,NOW(),?,?,?)").bind(tx.getTxId(), tx.getProductId(), tx.getQuantity(),
                tx.getType(), tx.getNotes()).execute();

    }

    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("Error during saving transaction " + std::string(error.what()));
    }
}
void DatabaseManager::updateProductStock(int id, int delta)
{
    try
    {
        session->sql("UPDATE products SET quantity = quantity + ? WHERE id = ?")
            .bind(delta, id).execute();
    }

    catch (const mysqlx::Error& error)
    {
        throw std::runtime_error("error during updating stock " + std::string(error.what()));
    }
}


std::vector<std::shared_ptr<Category>> DatabaseManager::loadAllCategories() {
    std::vector<std::shared_ptr<Category>> result;
    auto rows = db->getTable("category").select().execute();
    for (auto row : rows) {
        result.push_back(std::make_shared<Category>(
            row[0].get<int>(), row[1].get<std::string>(), row[2].get<std::string>()));
        
    }
    return result;
}
std::vector<std::shared_ptr<Supplier>> DatabaseManager::loadAllSuppliers() {
    std::vector<std::shared_ptr<Supplier>> result;
    auto rows = db->getTable("supplier").select().execute();
    for (auto row : rows) {
        result.push_back(std::make_shared<Supplier>(
            row[0].get<int>(), row[1].get<std::string>(), row[2].get<std::string>(), row[3].get<std::string>(), row[4].get<std::string>()));
        
    }
    return result;
}
std::vector<StockTransaction> DatabaseManager::loadAllTransactions() {
    std::vector<StockTransaction> result;
    auto rows = db->getTable("transactions").select().execute();
    for (auto row : rows) {
        result.emplace_back(row[0].get<int>(), row[1].get<int>(), row[2].get<time_t>(), row[3].get<int>(), row[4].get<std::string>(), row[5].get<std::string>());
    }
    return result;
}