#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <Arduino.h>
#include <cppQueue.h>

enum Shell {
    BLANK,
    LIVE,
    ERROR = -1
};

class Shotgun {
public:
    Shotgun();

    void load(int shells);
    int fire();
    int rack();
    void empty();
    Shell peek();
    String reveal();
    int getTotalShells();
    int getLiveShells();
    int getBlankShells();

    void setIsSawedOff(bool sawedOff);
    bool getIsSawedOff();

private:
    int shellsLive;
    int shellsBlank;
    bool isSawedOff;
    cppQueue magazine;
};

#endif // SHOTGUN_H
