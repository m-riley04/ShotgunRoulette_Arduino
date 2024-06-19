#include "Player.h"
#include "Item.h"

Player::Player(int id, int lives) : items(true) {
    this->id = id;
    this->lives = lives;
}

void Player::addItem(Item& item) {
    items.add(item);
}

void Player::addRandomItems(int itemCount) {
    for (int i = 0; i < itemCount; i++) {
        Item item = getRandomItem();
        addItem(item);
    }
}

Item& Player::getRandomItem() {
    String itemName = "Item";//items[random(0, 6)];
    Item item = Item(itemName);
    return item;
}

void Player::useItem(int index) {
    if (index < 7) {//items.size()) {
        Item item;
        item = items.get(index);
        item.use();
    }
}

int Player::getId() {
  return this->id;
}

int Player::getLives() {
    return this->lives;
}

void Player::setLives(int lives) {
    this->lives = lives;
}

bool Player::operator==(const Player &other) const {
  return this->id == other.id;
}