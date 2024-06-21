#include "Shotgun.h"

Shotgun::Shotgun() : magazine(sizeof(Shell), 10, FIFO) {
    this->shellsLive = 0;
    this->shellsBlank = 0;
    this->isSawedOff = false;
}

void Shotgun::load(int shells) {
    this->magazine = cppQueue(sizeof(Shell), shells, FIFO);

    // Clear out the magazine before loading
    this->magazine.flush();

    int median = shells / 2;
    for (int i = 0; i < shells; i++) {
        Shell isLive;
        // Ensure there are no 0-shells
        if (this->shellsBlank >= median-1) {
          isLive = LIVE;
          this->magazine.push(&isLive);
          this->shellsLive++;
          continue;
        } else if (this->shellsLive >= median-1) {
          isLive = BLANK;
          this->magazine.push(&isLive);
          this->shellsBlank++;
          continue;
        }

        // Randomly set round state
        isLive = (Shell)random(0, 2); // random(0, 2) to get 0 or 1
        this->magazine.push(&isLive);


        if (isLive == LIVE) this->shellsLive++;
        else this->shellsBlank++;
    }
}

int Shotgun::fire() {
    // TODO: Play a sound when the shotgun is fired

    // Check if the gun is empty
    if (this->magazine.isEmpty()) {
      return -1;
    }

    Serial.print("Gun fired: ");
    Serial.println(this->peek() ? "LIVE" : "BLANK");

    // Rack the gun
    this->rack();

    // TODO: Automatically make shotgun un-sawed (?)

    return 0;
}

int Shotgun::rack() {
    Shell shell;
    if (!magazine.pop(&shell)) return -1; // Check for error

    // Remove the shell
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
    if (this->magazine.peek(&shell)) return shell;
    else return -1;
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

int Shotgun::getLiveShells() {
  return shellsLive;
}

int Shotgun::getBlankShells() {
  return shellsBlank;
}

void Shotgun::setIsSawedOff(bool sawedOff) {
    this->isSawedOff = sawedOff;
}

bool Shotgun::getIsSawedOff() {
    return this->isSawedOff;
}
