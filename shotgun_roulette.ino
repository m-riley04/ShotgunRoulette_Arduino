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
            Serial.println("-ROUND 1-");
            this->initialize_round(2, 0, 4);
            break;
          case (2):
            Serial.println("-ROUND 2-");
            this->initialize_round(4, 2, 5);
            break;
          case (3):
            Serial.println("-ROUND 3-");
            this->initialize_round(5, 4, 8);
            break;
          default:
            Serial.println("ROUND ?");
            this->initialize_round(2, 0, 4);
        }

        // Run turns
        bool isLive;
        bool isRedTurn = true;
        Player &wielder = this->p1;
        Player &target = this->p2;
        bool handcuffsOn = false;
        digitalWrite(PIN_PLAYER_1, HIGH);
        digitalWrite(PIN_PLAYER_2, LOW);
        while (this->p1.getLives() > 0 && this->p2.getLives() > 0) {
          // TODO: Check for items/interactions

          // TODO: Check if user switches targets

          // Check for trigger pull
          if (digitalRead(PIN_TRIGGER) == HIGH && isReady) {
            Serial.print("== Player ");
            Serial.print(wielder.getId());
            Serial.println("'s turn ==");
            Serial.print("Target: Player ");
            Serial.println(target.getId());
            
            // Check for errors
            if (this->shotgun.isEmpty()) {
              Serial.println("ERROR: The shotgun is empty.");
              continue;
            }

            isReady = false;
            isLive = this->shotgun.peek();
            this->shotgun.fire();

            // Deal damage
            int damage = (int)isLive + (1*shotgun.getIsSawedOff());
            if (wielder == target) wielder.setLives(wielder.getLives()-damage);
            else target.setLives(target.getLives()-damage);

            // TODO: Check for any item interactions

            // Check whether to give wielder another turn
            if (handcuffsOn || (isLive && target == wielder)) Serial.println("Giving the wielder another turn.");
            else {
              // Switch the wielder
              if (!isRedTurn) {
                wielder = this->p2;
                target = this->p1;

                digitalWrite(PIN_PLAYER_1, LOW);
                digitalWrite(PIN_PLAYER_2, HIGH);
              }
              else { 
                wielder = this->p1;
                target = this->p2;

                digitalWrite(PIN_PLAYER_1, HIGH);
                digitalWrite(PIN_PLAYER_2, LOW);
              }

              isRedTurn = !isRedTurn;
              Serial.println("");
            }

            // Log
            Serial.print("Player Red: ");
            Serial.print(this->p1.getLives());
            Serial.print("  Player Blue: ");
            Serial.println(this->p2.getLives());
            Serial.print("Shells Left: ");
            Serial.println(this->shotgun.getTotalShells());

            Serial.print("It is now Player ");
            Serial.print(wielder.getId());
            Serial.println("'s turn.");

          }
          
          if (digitalRead(PIN_TRIGGER) == LOW) {
            isReady = true;
          }

          // Check if the shotgun needs to be reloaded
          if (shotgun.isEmpty()) {
            shotgun.load(6);
          }
        }
      }
    }

    void initialize_round(int lives, int items, int shells) {
      // Set lives
      p1.setLives(lives);
      p2.setLives(lives);
      Serial.println("LIVES RESET.");

      // Give items
      p1.addRandomItems(items);
      p2.addRandomItems(items);
      Serial.println("ITEMS GIVEN.");

      // Load the shotgun
      shotgun.load(shells);
    }

  private:
    int max_rounds;
    Shotgun shotgun;
    Player p1 = Player(1, 3);
    Player p2 = Player(2, 3);
    bool isReady = true;
};

void setup() {
  Serial.begin(9600);

  // Set random seed
  randomSeed(analogRead(0));
  
  // Setup pins
  pinMode(PIN_TRIGGER, INPUT);
  pinMode(PIN_PLAYER_1, OUTPUT);
  pinMode(PIN_PLAYER_2, OUTPUT);
}

Game game(3);
void loop() {

  // Check if the trigger was pulled to start the game
  if (digitalRead(PIN_TRIGGER) == HIGH) {
    Serial.println("== GAME STARTED ==");
    delay(1000);
    game.start();
  }
}

