#include "Shotgun.h"

Shotgun::Shotgun() : magazine(sizeof(Shell), 10, FIFO) {
    this->shellsLive = 0;
    this->shellsBlank = 0;
    this->isSawedOff = false;
}

void Shotgun::load(int shells) {
    this->magazine = cppQueue(sizeof(Shell), shells, FIFO);

    for (int i = 0; i < shells; i++) {
        Shell isLive = (Shell)random(0, 2); // random(0, 2) to get 0 or 1
        this->magazine.push(&isLive);

        if (isLive == LIVE) {
            this->shellsLive++;
        }
        else {
            this->shellsBlank++;
        }
    }
}

void Shotgun::fire() {
    // TODO: Play a sound when the shotgun is fired

    // Rack the gun
    this->rack();

    // TODO: Automatically make shotgun un-sawed (?)
}

void Shotgun::rack() {
    Shell shell;
    magazine.pop(&shell);

    if (shell == LIVE) {
        this->shellsLive--;
    }
    else {
        this->shellsBlank--;
    }

    // TODO: Play rack sound
}

void Shotgun::empty() {
    this->magazine.flush();
    this->shellsLive = 0;
    this->shellsBlank = 0;
}

Shell Shotgun::peek() {
    Shell shell;
    this->magazine.peek(&shell);
    return shell;
}

String Shotgun::reveal() {
    String _string = "";

    for (int i = 0; i < this->magazine.getCount(); i++) {
        Shell shell;
        this->magazine.peekIdx(&shell, i);
        _string += (shell == LIVE ? "LIVE" : "BLANK");
        if (i < this->magazine.getCount() - 1) {
            _string += ", ";
        }
    }

    return _string;
}

int Shotgun::getTotalShells() {
    return shellsLive + shellsBlank;
}

void Shotgun::setIsSawedOff(bool sawedOff) {
    this->isSawedOff = sawedOff;
}

bool Shotgun::getIsSawedOff() {
    return this->isSawedOff;
}
