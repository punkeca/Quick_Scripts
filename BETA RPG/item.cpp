#include "item.h"


item::item(string n, double p, unsigned int qt, string dpt)
{	
	try {
		if (!isValid(n, itemType)|| qt > 5)
			throw invalid_argument("Invalid item type or quantity. 1 garbage Item was generated.");
		name = n;
		price = p;
		quantity = qt;
		description = dpt;
	}
	catch (invalid_argument &err) {
		item();
		cerr << err.what();
	}
}

void item::updateQuantity(int difference) //updates quantity, doesn't allow negative or quantities over 10 items
{
	int balance = this->quantity + difference; //accepts negative values for difference
	try {
		if (balance == 0){
			this->~item(); //this is probably not working
			return;
		}
			
		if (balance < 0)
			throw invalid_argument("Invalid request. Item quantity not updated.");
		if (balance > 10) //more items than max allowed.
			balance = 10; //sets items to max value
		this->quantity = balance;
	}
	catch (invalid_argument &err) {
		cerr << err.what();

	}
}

ostream& operator<<(ostream& out, item& obj)
{
	out << "-------------- ITEM --------------" << endl;
	out << obj.name << endl;
	out << obj.price << endl;
	out << obj.quantity << endl;
	out << obj.description << endl;
	out << "---------------------------------" << endl;
	return out;
}
