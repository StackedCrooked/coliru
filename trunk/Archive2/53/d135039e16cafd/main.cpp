#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
 
int main()
{    
    microseconds no_cast = seconds(1) / 7;
    microseconds cast = microseconds(seconds(1)) / 7;
    
    cout << "No Cast: " << no_cast.count() << endl;
    cout << "Cast   : " << cast.count() << endl;
}