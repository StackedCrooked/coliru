#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class weatherDay {
    int dayNum;
    int maxT;
    int minT;
    
    public:
    weatherDay(int day=-1, int max=-1, int min=-1) : 
        dayNum(day),
        maxT (max),
        minT (min)
        {}
    
    friend ostream& operator << (ostream &o, weatherDay wd) {
        o << "Day: " << wd.dayNum << "\tMaxT: " << wd.maxT << "\tMinT" << wd.minT << endl;
        return o;
    }
};

class weatherMonth {
    float maxAv;
    float minAv;
    weatherDay wd[30];
};

int main() {
    
    ifstream infile;
    string sLine = "";
    infile.open("weather.dat");
    
    if (!infile) {
        cout << "Weather data file not found\n";
        exit (3);
    }
    
    while (!infile.eof()) {
        getline (infile, sLine);
        cout << sLine;
    }   
}
    