#include <iostream>
#include <string>
#include <vector>

#define BulletWeapon1 100
#define BulletWeapon2 30
#define BulletWeapon3 50

class Bullet1 {};

enum Weapons { Gun1,Gun2,Gun3 } CurrentWeapon;

template <class T>
class Gun {};

int main() {
	Gun<Bullet1>();
	return 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (auto& el : vec) {
        os << el << ' ';
    }
    return os;
}
