
#include "Bullet1.h"
#include <iostream>
using namespace std;
#define BulletWeapon1 100
#define BulletWeapon2 30
#define BulletWeapon3 50
enum Weapons
{
    Gun1,Gun2,Gun3

}CurrentWeapon;
template <class T>
class Gun
{
};
int main()
{
	Gun<Bullet1> g;
	return 0;
}
#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
