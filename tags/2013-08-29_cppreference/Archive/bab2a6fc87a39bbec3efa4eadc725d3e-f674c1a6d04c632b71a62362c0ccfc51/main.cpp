#include <iostream>

using namespace std;

class FeatureA;
class FeatureB;

class Computer{
    public:
    int visitA(FeatureA& f);
    
    int visitB(FeatureB& f);
};

class Feature {
public:
  virtual ~Feature() {}
  virtual int accept(Computer&) = 0;
};

class FeatureA{
    public:
    int accept(Computer& c){
        return c.visitA(*this);
    }
    int compute(int a){
        return a+1;
    }
};

class FeatureB{
    public:
    int accept(Computer& c){
        return c.visitB(*this);
    }
    int compute(int a, int b){
        return a+b;
    }
};

int Computer::visitA(FeatureA& f){
        return f.compute(1);
}

int Computer::visitB(FeatureB& f){
        return f.compute(1, 2);
}

int main()
{
    FeatureA a;
    FeatureB b;
    Computer c;
    cout << a.accept(c) << '\t' << b.accept(c) << endl;
}