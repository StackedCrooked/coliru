#include <iostream>
using namespace std;

// Funkcja main może mieć (z większością kompilatorów)
// jeden z trzech możliwych prototypów:
// int main();
// int main(int, char**);
// int main(int, char**, char**);
void main (int argc, char** argv) {
    cout << argc << endl;
    cout << argv[0] << endl;
    return 0;
}