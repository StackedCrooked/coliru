#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    {
        fstream f("1.txt");
        string line;
        while (getline(f, line)) {
            cout << boolalpha << f.eof() << endl;
        }
    }
    {
        fstream f("1.txt");
        string line;
        assert((bool)getline(f, line) == true);
        assert((bool)getline(f, line) == false);
    }
    {
        fstream f("1.txt");
        string line;
        getline(f, line);
        getline(f, line);
        cout << endl << boolalpha << f.eof() << endl;
    }
    
    return 0;
}