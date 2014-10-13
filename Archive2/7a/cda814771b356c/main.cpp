struct fish {};
struct shark : public fish {};
struct trout : public fish {};

struct aquarium
{
    shark shark_;
    trout trout_;
};

fish aquarium::* pick_dinner(bool dangerous = true)
{
    //return dangerous ? static_cast<fish aquarium::*>(&aquarium::shark_) : static_cast<fish aquarium::*>(&aquarium::trout_);
    if (dangerous) 
        return &aquarium::shark_;
    else
        return &aquarium::trout_;
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