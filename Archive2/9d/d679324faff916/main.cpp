#include <cstdlib>
#include <iostream>

using namespace std;

struct City {
    string name;
    City *nextCity;
    string message;
};

City buildNetwork() {
    City *cityList = NULL;
    City *head;

    for(int8_t n=0; n<10; n++) {
        City *nxc = new City;
        head = nxc;
        nxc->name = "Los Angeles";
        nxc->nextCity=head;
        head=nxc;
    }
    return *cityList;
}

void printPath(City *head) {
    City *nCity;
    nCity = head;
    while(nCity != NULL) {
        cout<<nCity->name<<endl;
        nCity = nCity->nextCity;
    }
}

int main() {
    City *builtList = new City;
    *builtList = buildNetwork();
    printPath(builtList);
}