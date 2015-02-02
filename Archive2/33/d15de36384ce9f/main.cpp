#include <cstdlib>
#include <iostream>

using namespace std;

struct City {
    string name;
    City *nextCity;
    string message;
};

City buildNetwork() {
    City *cityList;
    City *newCity;
    City *head;

    newCity = new City;
    head = newCity;

    for(int8_t n=0; n<10; n++) {
        City *nxc = new City;
        nxc->name = "Los Angeles";
        nxc->nextCity=cityList;
        //newCity->nextCity=nxc;
        cityList = nxc;
    }
    return cityList;
}

int main() {
    City *builtList;
    builtList = buildNetwork();
}