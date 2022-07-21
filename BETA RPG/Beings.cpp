#include "Beings.h"
#include <stdexcept>
//smarter design would be to create a system object class and have being and item derive from it.
//this was not done since this is a practice program and prototype.

Being::Being(string n, unsigned int lvl, unsigned int hlth, string bkgd, unsigned int dam) {
    name = n;
    level = lvl;
    health = hlth;
    background = bkgd;
    damage = dam;
}
void Being::evolve()
{
    this->level++;
    this->health = level * ++health;
    this->damage = 2 * damage;
}
void Being::show() {
    cout << "-----------------------------" << endl;
    cout << "Name: " << name << endl;
    cout << "Lvl: " << level << endl;
    cout << "HP: " << health << endl;
    cout << "Damage: " << damage << endl;
    cout << "-----------------------------" << endl;
}

void Being::attack(Being& enemy)
{
    enemy.getDamage(this->damage);
}

void Being::getDamage(int value)
{
    this->health -= value;
    if (health == 0)
        this->~Being();
}

Monster::Monster(string n, unsigned int lvl, unsigned int hp, string str, unsigned int dam, string tp)
    :Being::Being(n,lvl,hp,str,dam)
{
    type = tp;
}


Player::Player(string n , unsigned int lvl, unsigned int hp, string story, unsigned int dam, string race , string clss, vector<item> inventory)
    : Being::Being(n, lvl, hp, story,dam)
{   
    try {
        if (!isValid(race, playerRaces) || !isValid(clss, playerClasses))
            throw invalid_argument("Invalid race or class.Race and Class set to default.");
        playerRace = race;
        playerClass = clss;
    }
    catch (invalid_argument &err) {
        playerRace = "Human";
        playerClass = "Warrior";
        cerr << err.what();
    }
}

void Player::accquireItem(item &newItem) 
{
    try {
        if (inventory.size() >= 10)
            throw(0);
            this->inventory.push_back(newItem);
    }
    catch (int err) {
        cerr << "Full Inventory!." << endl;
    }
}

void Player::throwAway(item &myItem) {
    try {
        if (inventory.size() == 0)
            throw(0);
        for (auto &x: inventory){
            if (myItem.getName() == x.getName()) {
                x.updateQuantity(-1);
            }
        }
          
    }
    catch (int err) {
        cerr << "Empty Inventory!." << endl;
    }
}

void Player::useItem(item &it)
{
    try {
        if (inventory.size() == 0)
            throw;
        string comp = it.getName();
        if(comp == "Health Potion")
            this->health += 1;
        if (comp == "Health Potion")
            this->damage += 1;
        if (comp == "Health Potion")
            this->damage += 2;
        throwAway(it); //this function is not working properly.
    }
    catch (...) {
        cerr << "Empty Inventory or invalid position." << endl;
    }
}

void Player::showInventory()
{   
    cout << "=========== INVENTORY ==========" << endl;
    for (auto &x : inventory) {
        cout << x << endl;
    }
}


