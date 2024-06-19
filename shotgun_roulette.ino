#include <List.hpp>
#include <cppQueue.h>
#include "item.h"
#include "player.h"
#include "shotgun.h"

#define PIN_TRIGGER 7
#define PIN_PLAYER_1 10
#define PIN_PLAYER_2 11

String items[] = {
  "Magnifying Glass",
  "Cigarettes",
  "Beer",
  "Handsaw",
  "Handcuffs",
  "Burner Phone",
  "Inverter"
};

class Game {
  public:
    Game(int max_rounds = 3) {
      this->max_rounds = max_rounds;
    }

    void start() {
      for (int round = 1; round <= max_rounds; round++) {
        // Initialize the round
        switch (round) {
          case (1):
            this->initialize_round(2, 0);
            break;
          case (2):
            this->initialize_round(4, 2);
            break;
          case (3):
            this->initialize_round(5, 4);
            break;
          default:
            this->initialize_round(2, 0);
        }

        // Run turns
        bool isPlayer1Turn = true;
        Player &weilder = p1;
        Player &target = p2;
        bool handcuffsOn = false;
        while (p1.getLives() > 0 && p2.getLives() > 0) {
          // TODO: Check for items/interactions

          // TODO: Check if user switches targets

          // Check for trigger pull
          if (digitalRead(PIN_TRIGGER) == HIGH) {
            this->shotgun.fire(); // Fire the shotgun

            // Deal damage
            int damage = 1 + (1*shotgun.getIsSawedOff());
            if (weilder == target) weilder.setLives(weilder.getLives()-damage);
            else target.setLives(target.getLives()-damage);

            // TODO: Check the lives of each player

            // TODO: Check for any item interactions

            // Switch the wielder
            if (handcuffsOn) {
              // Do not switch the weilder and target
            } else if (weilder == p1) {
              weidler = p2;
              target = p1

              digitalWrite(PIN_PLAYER_1, LOW);
              digitalWrite(PIN_PLAYER_2, HIGH);
            }
            else { 
              weilder = p1;
              target = p2;

              digitalWrite(PIN_PLAYER_1, HIGH);
              digitalWrite(PIN_PLAYER_2, LOW);
            }

          }
        }
      }
    }

    void initialize_round(int lives, int items) {
      // Set lives
      p1.setLives(lives);
      p2.setLives(lives);

      // Give items
      p1.addRandomItems(items);
      p2.addRandomItems(items);
    }

  private:
    int max_rounds;
    Shotgun shotgun;
    Player p1 = Player(1, 3);
    Player p2 = Player(2, 3);
};

void setup() {
  randomSeed(analogRead(0));
  // Set random seed

  Serial.begin(9600);

  // Setup pins
  pinMode(PIN_TRIGGER, INPUT);
  pinMode(PIN_PLAYER_1, OUTPUT);
  pinMode(PIN_PLAYER_2, OUTPUT);
}

void loop() {
  Game game(3);

  // TODO: Check if the trigger was pulled to start the game
  if (digitalRead(PIN_TRIGGER) == HIGH) {
    game.start();
  }
}

