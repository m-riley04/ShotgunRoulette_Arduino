#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include <List.hpp>
#include "Item.h"

class Player {
public:
    Player(int id, int lives);

    void addItem(Item& item);
    void addRandomItems(int itemCount);
    Item& getRandomItem();
    void useItem(int index);

    int getId();
    int getLives();
    void setLives(int lives);

    bool operator==(const Player &other) const;

private:
    int id;
    int lives;
    List<Item> items;
};

#endif // PLAYER_H