#include "Item.h"

Item::Item() {
    this->name = "";
}

Item::Item(String name) {
    this->name = name;
}

void Item::use() {
    // TODO: Add override functionality
}

void Item::setName(String name) {
    this->name = name;
}

String Item::getName() {
    return this->name;
}