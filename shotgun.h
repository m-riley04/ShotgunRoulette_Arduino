#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Arduino.h>
#include <cppQueue.h>

enum Shell {
    BLANK,
    LIVE
};

class Shotgun {
public:
    Shotgun();

    void load(int shells);
    void fire();
    void rack();
    void empty();
    Shell peek();
    String reveal();
    int getTotalShells();

    void setIsSawedOff(bool sawedOff);
    bool getIsSawedOff();

private:
    int shellsLive;
    int shellsBlank;
    bool isSawedOff;
    cppQueue magazine;
};

#endif // SHOTGUN_H
