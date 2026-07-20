#include "InventoryService.h"
#include "StockTransaction.h"
#include "Product.h"
#include <ctime>
#include <utility>

InventoryService::InventoryService(Inventory&& inventory_, DatabaseManager&& db_)
	:inventory(std::move(inventory_)), db(std::move(db_)){ }



void InventoryService::addNewProduct(const std::shared_ptr<Product>& product) {
    try {

          db.saveProduct(*product);
          inventory.addProduct(product);

    }
    catch (const std::exception& e) {
        throw std::runtime_error("error addNewProduct" + std::string(e.what()));
    }
}

void InventoryService::updateProductStock(int id, int delta, const std::string& note) {
    inventory.updateStock(id, delta);

    db.updateProductStock(id, delta);

    std::string type = (delta > 0) ? "RESTOCK" : "SALE"; 
    time_t currentTime = std::time(nullptr);

    StockTransaction tx(0, id, currentTime, delta, type, note);

    inventory.recordTransaction(tx);
    db.saveTransaction(tx);
}

void InventoryService::loadFromDatabase() {
    try {
        std::vector<std::shared_ptr<Supplier>> dbSuppliers = db.loadAllSuppliers();
        for (const std::shared_ptr<Supplier>& supplier : dbSuppliers) {
            if (supplier) {
                inventory.addSupplier(supplier);
            }
        }

        std::vector<std::shared_ptr<Category>> dbCategories = db.loadAllCategories();
        for (const std::shared_ptr<Category>& category : dbCategories) {
            if (category) {
                inventory.addCategory(category);
            }
        }

        std::vector<std::shared_ptr<Product>> dbProducts = db.loadAllProducts();
        for (const std::shared_ptr<Product>& product : dbProducts) {
            if (product) {
                inventory.addProduct(product);
            }
        }

        std::vector<StockTransaction> dbTransactions = db.loadAllTransactions();
        for (const StockTransaction& tx : dbTransactions) {
            inventory.recordTransaction(tx);
        }

    }
    catch (const std::exception& e) {

        throw std::runtime_error("Error during loading " + std::string(e.what()));
    }
}

std::vector<std::shared_ptr<Product>> InventoryService::generateReorderList() const {
    std::vector<std::shared_ptr<Product>> reorderList;

    for (const auto& [id, productPtr] : inventory.getProducts()) {
        if (productPtr && productPtr->isLowStock()) {
            reorderList.push_back(productPtr);
        }
    }

    return reorderList;
}