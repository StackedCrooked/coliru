#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unistd.h>
 
struct Player
{
    Player(std::string name, const int hp, const int strength, const int attackspeed)
        : name(name)
        , hp(hp)
        , strength(strength)
        , attackspeed(attackspeed)
    {}
    
    void dmg(int dmg)
    {
        hp -= dmg;
    }
    
    bool ask_dead()
    {
        return hp < 0;
    }
    
    friend void dueler(Player& player, Player& enemy);
    
private:
    std::string name;
    int hp, strength, attackspeed;
};


std::mutex mux1;
 
void dueler(Player& player, Player& enemy)
{
    do {
        usleep(player.attackspeed);
        mux1.lock();
        std::cout << player.name << " hit " << enemy.name << " for " << player.strength << " damage!" << std::endl;
        enemy.dmg(player.strength);
        mux1.unlock();
    } while (!enemy.ask_dead() && !player.ask_dead());
}

int main()
{
    Player p1("kasper", 100, 5, 200);
    Player p2("Bagger", 150, 8, 3000);
    
    std::thread dueler1(dueler, std::ref(p1), std::ref(p2));
    std::thread dueler2(dueler, std::ref(p2), std::ref(p1));
    
    dueler1.join();
    dueler2.join();
    
    std::cout << std::endl << "battle is over!";
}
