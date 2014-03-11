#include <string>
#include <iostream>

using namespace std;

int main(){
    try {
        throw string("test");
    } catch (string && s) {
        cout << s << endl;
    }
    return 0;
}