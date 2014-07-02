#include <iostream>
using namespace std;

class base {
public:
 base(int i) {};

private:
 base(){};
};

class derivedA: virtual public base {
public:
 derivedA(int i) : base(i) {};

protected:
  derivedA() : base(0) {};
};

class derivedB: virtual public base {
public:
 derivedB(int i) : base(i) {};

protected:
  derivedB() : base(0) {};
};

class derivedAB : public derivedA, public derivedB {
public:
 derivedAB(int i) {};
 virtual ~derivedAB() = 0;
};

derivedAB::~derivedAB() {};

class lastDerived : public derivedAB {
public:
    lastDerived() : base(1), derivedAB(0) {};
};

int main(){
        lastDerived obj;
}