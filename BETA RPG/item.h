#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
#ifndef ITEM_H
#define ITEM_H

bool isValid(string str, vector<string> database) {
	for (auto x : database) {
		if (x == str)
			return true;
	}
	return false;
}//end is valid


vector<string> itemType{ "Health Potion", "Poison", "Magical Scroll", "Garbage"};

class item{
	private:
		string name{};
		double price {0};
		unsigned int quantity{ 0 };
		string description {};
	public:
		item() : item("Garbage",0.0,1,"this strange item does absolutely nothing.") {};
		item(string n, double p, unsigned int qt, string dpt);
		//change quantity and price
		void updateQuantity (int difference);
		string getName() { return name; }
		friend ostream& operator<<(ostream& out, item& obj);
};

#endif