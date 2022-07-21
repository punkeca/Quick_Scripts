#include <iostream>
#include <vector>
#include "item.h"
using namespace std;

#ifndef MYRPG_H
#define MYRPG_H
int nPlayers{ 0 };
int nMonsters{ 0 };

vector<string> playerClasses{ "Rogue", "Warrior", "Spellcaster" };
vector<string> playerRaces{ "Dwarf", "Human", "Elf" , "Orc"};
vector<string> monsterTypes{ "Fire Dragon", "Common Creature", "Water Snake" , "Earth Worm", "Air Spirit"};


class Being {
protected:
    string name{};
    unsigned int level{ 0 };
    unsigned int health{ 0 };
    string background{};
    unsigned int damage{ 0 };

public:
    Being(): Being("NewBeing", 1, 1, "System Generated Being.",1){ }
    Being(string, unsigned int, unsigned int, string, unsigned int);
    void evolve();
    void updateBackground(string newBg) { this->background = newBg;}
    void show(); //used for testing.
    virtual ~Being() {cout << name << " has passed away." << endl;}
    virtual void attack(Being& enemy);
    virtual void getDamage(int value);
};

class Player : public Being {
protected:
    string playerRace{};
    string playerClass{};
    vector<item> inventory{};

public:
    Player():Player("Nameless",1,1,"A faceless champion.",1,"Human","Warrior",{}){}
    Player(string, unsigned int, unsigned int, string, unsigned int, string,string, vector<item>);
    ~Player(){}
    void accquireItem(item &newItem);
    void throwAway(item&); //is erasing all items without meaning to.
    void useItem(item& it);
    void showInventory();
}; //end player


class Monster : public Being {
protected:
    string type{};
public:
    Monster() :Monster("Ordinary Monster",1,1,"An ordinary lost creature. It is scared.",1,"Common Creature") {}
    Monster(string, unsigned int, unsigned int, string, unsigned int, string);
    ~Monster(){}
};//end monster


#endif
