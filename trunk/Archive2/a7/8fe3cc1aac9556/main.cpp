#include <iostream>
#include <sstream>

using namespace std;

class Flight
{
    string flightno, destination, departure, gateno;
    public:
    void print(){cout << flightno << ';' << destination << ';' << departure << ';' << gateno << endl;}
    friend std::istream& operator>>(std::istream& is, Flight& flight);
};

std::istream& operator>>(std::istream& is, Flight& flight)
{
    is >> flight.flightno >> flight.destination >> flight.departure >> flight.gateno;
    return is;
}

int main() {
    istringstream foo{"AA223 LAS VEGAS 21:15 A3"};
    Flight bar;

    foo >> bar;
    bar.print();
}    
