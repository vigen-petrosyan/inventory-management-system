#include "StockTransaction.h"

StockTransaction::StockTransaction(int txId_, int productId_,
	time_t date_, int quantity_,std::string type_, std::string notes_):
	txId(txId_), productId(productId_), date(date_),
	quantity(quantity_), type(type_), notes(notes_){ }

void StockTransaction::setTxId(int txId_) { txId = txId_; }
void StockTransaction::setProductId(int productId_) { productId = productId_; }
void StockTransaction::setQuantity(int quantity_) { quantity = quantity_; }
void StockTransaction::setType(const std::string& type_) { type = type_; }
void StockTransaction::setNotes(const std::string& notes_) { notes = notes_; }

int StockTransaction::getTxId() const { return txId; }
int StockTransaction::getProductId() const { return productId; }
int StockTransaction::getQuantity() const { return quantity; }
std::string StockTransaction::getType() const { return type; }
std::string StockTransaction::getNotes() const { return notes; }
