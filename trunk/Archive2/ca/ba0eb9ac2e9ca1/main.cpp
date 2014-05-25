#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
int main(int argc, char** argv) {

    string sentence = "this is a long sentence";

    int i=0;
    for (auto c : sentence) {
        cout << ++i << c << '\n';
    }
    cout << '\n';

    return 0;
}
