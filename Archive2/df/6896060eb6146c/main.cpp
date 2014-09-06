#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>

using namespace std;
void fightdragon();
void gameover();

class Player {
    public:
        string name = "Player";
        //Stat
        int hp = 100;
        int energy = 50;
        //Attribute
        int agility = 5;
        int speed = 5;
        int strength = 5;
}; Player player;

class Dragon {
    public:
        string name = "Dragon";
        //Stat
        int hp = 200;
        int energy = 50;
        //Attribute
        int agility = 1;
        int speed = 3;
        int strength = 10;
}; Dragon dragon;

class DragonBackup {
    public:
        string name = "Dragon";
        //Stat
        int hp = 200;
        int energy = 50;
        //Attribute
        int agility = 1;
        int speed = 3;
        int strength = 10;
}; DragonBackup dragonbackup;

int main() {
    fightdragon();
    srand( (unsigned)time( NULL ) );
}

void clearscreen() {
    if(system ("CLS")) system("clear");
}

void fightdragon() {
    string events = "The Dragon stands before your eyes!";
    string action;
    //Enemy
    cout << "==========================================" << endl;
    cout << dragon.name << endl;
    cout << "HP: " << dragon.hp << endl;
    cout << "Energy: " << dragon.energy << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << events << endl;
    cout << endl;
    //Player
    cout << "==========================================" << endl;
    cout << player.name << endl;
    cout << "HP: " << player.hp << endl;
    cout << "Energy: " << player.energy << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "Select Action:" << endl;
    cout << "(A) Attack, (M) Magic, (I) Items: "; cin >> action;
    if(action == "a") {
        if(player.hp < 1) {
            gameover();
        }

        else if(dragon.hp < 1) {
            clearscreen();
            cout << "You've slayed the " << dragon.name << endl;
        }
        clearscreen();
        dragon.hp = dragon.hp - (player.strength * 1.5);
        events = "You and dragon took damage";
        player.hp = player.hp - (dragon.strength * 1.5);
        fightdragon();


    }
}

void gameover() {
    clearscreen();
    cout << "Game Over!" << endl;
}