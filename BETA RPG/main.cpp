#include "Beings.cpp"
#include "item.cpp"
int main() {
	Player pl1;
	Monster m1;
	item it1{ "Health Potion",1,1,"Restores Health" };
	item it2{};
	item it3{};

	pl1.evolve();
	pl1.show();
	m1.show();
	pl1.accquireItem(it1);
	pl1.accquireItem(it2);
	pl1.accquireItem(it3);
	pl1.useItem(it1); // is working but wont erase item.
	pl1.showInventory();
	pl1.show();
	return 0;
}//end main