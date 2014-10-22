#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

struct Gunman
{
    std::string name;
    unsigned hitOneInEvery;
    bool aliveStatus;
    unsigned kills;
    unsigned wins;
};

bool aimAndShoot(Gunman &shooter, Gunman &target1, Gunman &target2);

int main()
{
    std::srand(std::time(nullptr));
    
    unsigned const rounds = 10000u;
    
    //you could use an array here if you want
    //the name parameter isn't as useful without array but oh well
    Gunman aaron{"aaron", 3u, true, 0u, 0u};
    Gunman bob{"bob", 2u, true, 0u, 0u};
    Gunman charlie{"charlie", 1u, true, 0u, 0u};
    
    for(unsigned round = 0u; round < rounds; ++round)
    {
        aaron.aliveStatus = true;
        bob.aliveStatus = true;
        charlie.aliveStatus = true;
        
        unsigned totalAlive = 3u;
        //if you don't want total alive you could alternatively do (aaron.aliveStatus && bob.aliveStatus) || (aaron.aliveStatus && charlie.aliveStatus) || (bob.aliveStatus && charlie.aliveStatus)
        while(totalAlive > 1) //2 or 3 are alive
        {
            totalAlive -= aimAndShoot(aaron, charlie, bob);
            totalAlive -= aimAndShoot(bob, charlie, aaron);
            totalAlive -= aimAndShoot(charlie, bob, aaron);
        }
        aaron.wins += aaron.aliveStatus;
        bob.wins += bob.aliveStatus;
        charlie.wins += charlie.aliveStatus;
    }
    
    std::cout << "\tAaron\tBob\tCharlie\n"
    "Ratio:\t" << static_cast<double>(aaron.wins) / rounds << '\t' << static_cast<double>(bob.wins) / rounds << '\t' << static_cast<double>(charlie.wins) / rounds
    << "\nWins:\t" << aaron.wins << '\t' << bob.wins << '\t' << charlie.wins
    << "\nKills:\t" << aaron.kills << '\t' << bob.kills << '\t' << charlie.kills << std::endl;
    
    return 0;
}

bool aimAndShoot(Gunman &shooter, Gunman &target1, Gunman &target2) //returns if they killed anyone
{
    bool missed = true;
    if(shooter.aliveStatus)
    {
        missed = rand() % shooter.hitOneInEvery;
        if(!missed)
        {
            ++shooter.kills;
            if(target1.aliveStatus) //bob is alive
            {
                target1.aliveStatus = false;
            }
            else
            {
                target2.aliveStatus = false;
            }
        }
    }
    return !missed;
}
        
        