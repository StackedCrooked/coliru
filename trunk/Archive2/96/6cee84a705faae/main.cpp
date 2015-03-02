#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Pieces{
    Pieces(){} // default c'tor
    Pieces(const string& t)
        : traits(t) {}

    string traits;

    //friend ostream& operator<< (ostream& stream, const Pieces& p);
};

// overload the output stream operator for convenience
ostream& operator<< (ostream& stream, const Pieces& p)
{
    stream << p.traits;
    return stream;
}


int main()
{
    Pieces p1("WSHR");  // neater if you write a constructor overload that inits the contents
    Pieces p2("BSHR");
    Pieces p3("WTHR");
    Pieces p4("BTHR");

    Pieces available[4] = { p1, p2, p3, p4 };
    // Or you could init the elements directly in the array; 
    Pieces a2[1] = { Pieces("WSHR") };

    cout << available[0] << endl; 

    // This is my favorite way to declare and init the array
    vector<Pieces> avail = { Pieces("WSHR"), Pieces("BSHR"), Pieces("WTHR"), Pieces("BTHR") };
    cout << avail[0] << endl;
}