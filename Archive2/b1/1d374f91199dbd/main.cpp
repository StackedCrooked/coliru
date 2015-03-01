#include <iostream>
#include <memory>
using namespace std;

struct die;

class X
{
   unique_ptr<int, die> p;
public:
   X(int);
   ~X();
   int value() const;
};

struct die
{
   void operator()(auto *p) const { delete p; }
};

X::X(int n) : p { new int { 3 } }
   { }
X::~X() = default;
int X::value() const
   { return *p; }

int main()
{
   X x { 3 };
   cout << x.value() << endl;
}

