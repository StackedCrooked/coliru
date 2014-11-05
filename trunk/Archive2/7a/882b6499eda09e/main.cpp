#include <utility>
#include <tuple>
#include <string>
#include <iostream>

using namespace std;

auto calcSpeed(double distance, double time)
{ return make_pair(distance / time, std::to_string(distance) + " / " + std::to_string(time)); }

int main() {
    double speed;
    std::string formula;
    std::tie(speed, formula) = calcSpeed(0.5, 0.2);
    
    cout << speed << endl;
    cout << formula << endl;
}
