#include "StockTransaction.h"

StockTransaction::StockTransaction(int txId_, int productId_, time_t date_, int quantity_, std::string type_, std::string notes_, std::shared_ptr<Product> product_):
	txId(txId_), productId(productId_), date(date_), quantity(quantity_), type(type_), notes(notes_), product(product_){ }
