#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class ThingNoMove
{
    public:
    ThingNoMove(const std::string& name): mName(name){cout << "ctor  - " << mName << endl; }
    ThingNoMove(const ThingNoMove& other)      {cout << "copy ctor  - " << other.mName << endl; }
    ThingNoMove& operator=(const ThingNoMove& other) {cout << "copy assign - " << other.mName << endl; return *this;}
    
    std::string mName;
};

class Thing
{
    public:
    Thing(const std::string& name): mName(name){cout << "ctor  - " << mName << endl; }
    Thing(const Thing& other)       {cout << "copy ctor  - " << other.mName << endl; }
    Thing& operator=(const Thing& other)  {cout << "copy assign - " << other.mName << endl; return *this;}
    Thing(Thing&& other) noexcept   {cout << "move ctor  - " << other.mName << endl; mName = other.mName; other.mName = ""; }    //parameter can not be const, noexpect needed
    Thing& operator=(Thing&& other) {cout << "move assign - " << other.mName << endl; mName = other.mName; other.mName = ""; return *this;}
    
    std::string mName;
};

ThingNoMove returnObject1()
{
    ThingNoMove a("return object1");
    return a;
}

Thing returnObject2()
{
    Thing a("return object2");
    return std::move(a);
}

Thing returnObject3()
{
    Thing a("return object3");
    return a;
}

int main()
{
    cout << ">>>only copy ctor & assign<<<" <<endl;
    ThingNoMove a("ThingNoMove1");
    ThingNoMove b = a;
    b = a;
   // ThingNoMove c = move(a);    //ERROR: move const is deleted
   // b = move(a);                //ERROR: move assignment is deleted
    cout << "---------------------------------------" <<endl;
    cout << ">>>copy&move ctor & assign<<<" <<endl;
    Thing c("Thing1");
    Thing d = c;
    d = c;
    cout << ">>>using std::move<<<" <<endl;
    Thing e = move(c);
    cout << "c is moved and lost its identity: " << c.mName << endl;
    Thing f("f");
    f = move(e); // e contains all the data from c.
    cout << "---------------------------------------" <<endl;
    cout << ">>>return object from function<<<" << endl;
    b = returnObject1();
    f = returnObject2();
    f = returnObject3();
}
