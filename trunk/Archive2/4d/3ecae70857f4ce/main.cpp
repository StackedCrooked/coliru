#include <future>
#include <string>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
string reverse_string(const string& s)
{
    cout << "Reversing " << s << endl;
    string ss(s);
    reverse(ss.begin(), ss.end());
    return ss;
}
 
int main()
{
    future<string> f = async(launch::async, reverse_string, "Roma tibi subito motibus ibit amor");
    auto g = async(launch::async, reverse_string, "Anita lava la tina");
    auto h = async(launch::async, reverse_string, "A man, a plan, a canal: Panama");
     
    cout << "SHOWING RESULTS...." << endl;
     
    cout << "R1: " << f.get() << endl << endl;
    cout << "R2: " << g.get() << endl << endl;
    cout << "R3: " << h.get() << endl << endl;
}