#include <iostream>
#include <string>

using namespace std;

struct Hallgato {
    string nev;
};

string monogram (Hallgato h3) {
    string mono;
    for (int i = 0; i < h3.nev.size(); i++) {
        if('a' > h3.nev[i] && h3.nev[i] != '')
            mono = mon + h3.nev[i];
    }
    
    return mono;
}

int main()
{
    Hallgato h { "Goretity Arpad" };
    std::cout << monogram(h) std::endl;
	return 0;
}