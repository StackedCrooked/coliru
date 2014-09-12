#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int main() {
    //Variables + installations  
    time_t current = time(0);
    string dayHolder = ctime(&current);
    std::string day(dayHolder.begin(), dayHolder.begin() + 3);

    cout << ctime(&current) << endl;
    cout << dayHolder << endl;
    cout << day << endl;

    return 0;
}