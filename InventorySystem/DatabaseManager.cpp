#include<iostream>
#include "Product.h"
#include "DatabaseManager.h"
#include "Category.h"
#include "Supplier.h"
#include "StockTransaction.h"

DatabaseManager::DatabaseManager(std::string connectionString_, std::unique_ptr<mysqlx::Schema> db_)
	:connectionString(connectionString_),db(nullptr), session(nullptr){ }

bool DatabaseManager::connect()
{
    try
    {
        session = std::make_unique<mysqlx::Session>(connectionString);
        db = std::make_unique<mysqlx::Schema>(session->getSchema("UniversitySystem"));
        return true;
    }
    catch (const mysqlx::Error& e)
    {
        std::cerr << "Database connection failed " << e.what() << '\n';
        exit(1);
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
        mysqlx::SqlResult result = session->sql("SELECT name, description FROM category WHERE category_id = ?").
            bind(id_).execute();

        auto row = result.fetchOne();

        auto category = std::make_shared<Category>();
        category->setId(id_);
        category->setName(row[0].get<std::string>());
        category->setDescription(row[1].get<std::string>());

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

        auto supplier = std::make_shared<Supplier>();
        supplier->setId(id_);
        supplier->setName(row[0].get<std::string>());
        supplier->setContactEmail(row[1].get<std::string>());
        supplier->setPhone(row[2].get<std::string>());
        supplier->setAddress(row[3].get<std::string>());

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
        mysqlx::SqlResult result = session->sql("SELECT name,description,quantity,price,reorderd_level,"
            "category_id,supplier_id FROM products where products_id = ? ").bind(id_).execute();

        mysqlx::Row row = result.fetchOne();
        if (!row) { return nullptr; }



        auto product = std::make_shared<Product>();

        product->setName(row[0].get<std::string>());
        product->setDescription(row[1].get<std::string>());
        product->setQuantity(row[2].get<int>());
        product->setPrice(row[3].get<double>());
        product->setReorderLevel(row[4].get<int>());
        product->setCategory(loadCategory(row[5].get<int>()));
        product->setSupplier(loadSupplier(row[6].get<int>()));

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
            "FROM products"
        ).execute();

        std::vector<std::shared_ptr<Product>> allProducts;

        for (mysqlx::Row row : rows)
        {
            auto product = std::make_shared<Product>();

            product->setId(row[0].get<int>());
            product->setName(row[1].get<std::string>());
            product->setDescription(row[2].get<std::string>());
            product->setQuantity(row[3].get<int>());
            product->setPrice(row[4].get<double>());
            product->setReorderLevel(row[5].get<int>());

            product->setCategory(loadCategory(row[6].get<int>()));
            product->setSupplier(loadSupplier(row[7].get<int>()));

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
        session->sql("INSERT INTO supplier VALUES(id,name,contact_email,phone,address)")
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
            "price, reorder_level, category_id, supplier_id)VALUES(? , ? , ? , ? , ? , ? , ? , ? ").
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


