#include <cstdlib>
#include <iostream>

using namespace std;

struct City {
    string name;
    City *nextCity;
    string message;
};

City buildNetwork() {
    City *head = NULL;

    for(int8_t n=0; n<10; n++) {
        City *nxc = new City;
        if(n==0)
            nxc->name = "Los Angeles";
        else if(n==1)
            nxc->name = "Phoenix";
        else if(n==2)
            nxc->name = "Denver";
        else if(n==3)
            nxc->name = "Dallas";
        else if(n==4)
            nxc->name = "St. Louis";
        else if(n==5)
            nxc->name = "Chicago";
        else if(n==6)
            nxc->name = "Atlanta";
        else if(n==7)
            nxc->name = "Washington, D.C.";
        else if(n==8)
            nxc->name = "New York";
        else if(n==9)
            nxc->name = "Boston";
        nxc->nextCity=head;
        head=nxc;
    }
    return *head;
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