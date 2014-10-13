struct fish {};
struct shark : public fish {};
struct trout : public fish {};

struct aquarium
{
    shark shark;
    trout trout;
};

fish aquarium::* pick_dinner(bool dangerous = true)
{
    return dangerous ? &aquarium::shark : &aquarium::trout;
}

#include <iostream>

void cook(fish&)
{
    std::cerr << "Do it yourself\n";
}

int main()
{
    aquarium spherical, hexagonal;
    fish aquarium::*ingredient = pick_dinner();
    cook(spherical.*ingredient);
    cook(hexagonal.*ingredient);
}