#ifndef ITEM_H
#define ITEM_H

#include <Arduino.h>

class Item {
public:
    Item();
    Item(String name);

    virtual void use();
    void setName(String name);
    String getName();

private:
    String name;
};

#endif // ITEM_H
