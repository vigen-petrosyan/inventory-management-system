#pragma once
#include"Inventory.h"
class InventoryServise
{
private:
	Inventory inventory;

};


//  this is my UML diagram but I want to make some changes at first I want that all fields be private then I think all should have constructors then I think it will be better to have TransactionManager that will handle the transactions and transactions are connected to the databaseManager so I can store them in SQL . In my mind there should be connection from inventory servise to the handleTransaction so each time  I do sell or buy some product in service it should instantly do transactions also then update inventory which will cause updating in databaseManager // all is only my opinion if it wrong do your way but explalin it to me // 