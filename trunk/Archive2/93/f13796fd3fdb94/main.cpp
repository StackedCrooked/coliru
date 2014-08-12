#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int const argc, char const * const * const argv) {
        string head1;
        getline (ifstream{argv[1]}, head1);
        cout << head1 << endl;
}
