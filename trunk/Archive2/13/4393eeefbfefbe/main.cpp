#include <cassert>
#include <limits>
#include <cstdint>
#include <iostream>
#include <array>

void addLine(std::vector<std::array<int>,3>& buses)
{
    int line;
    cout << "enter the line to add" << endl;
    cin >> line;
    cout << "enter the number of stops" << endl;
    int stops;
    cin >> stops;
    int durationOfRide;
    cout << "enter the duration of the ride" << endl;
    cin >> durationOfRide;
 
    buses.push_back({ line, stops, durationOfRide})
}

int main(){
}