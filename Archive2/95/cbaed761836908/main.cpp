#include <iostream>
#include <fstream>
#include <utility>
#include <memory>
using namespace std;

auto make_closure = [](auto f)
{
    return [=](auto x)
    {
        *f << "logging: " << x << endl;
    };
};

auto fire = []
{
    auto f = make_shared<ofstream>("log.txt");
    *f << "starting" << endl;
    auto result = make_closure(f);
    *f << "continuing" << endl;
    return result;
};

int main()
{
    {
        auto log = fire();
        log("Elbereth");
        log(42);
    } // file is closed here
}