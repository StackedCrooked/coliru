#include <iostream>

// #include <stdlib.h>
#include <cstdlib> // if needed

// #include <time.h>
#include <ctime> // if needed

#include <string>

using namespace std;

class BunnyInfo{
public:
    static string Sex[];
    static string Color[];
    static int Age[];
    static string Name[];
    // BunnyInfo(); //
};

string BunnyInfo::Sex[] = {"Male", "Female"};
string BunnyInfo::Color[] = {"White", "Brown", "Black", "Spotted"};
int BunnyInfo::Age[] = {0,1,2,3,4,5,6,7,8,9,10};
string BunnyInfo::Name[] = {"Ness", "Lope", "Fad", "Butt", "Nutt", "Dell","Fell", "Hag", "Chan","Gal"};


int main(){
    BunnyInfo bunny;
    cout<<bunny.Name[1];
}
