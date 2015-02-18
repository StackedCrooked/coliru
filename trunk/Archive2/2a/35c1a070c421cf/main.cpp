#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Base {
protected:
    string type;
    int a;
public:
    Base(const Base &) = delete;

    void operator=(Base const &) = delete;

    Base() {
        type = "Base";   
    }
    
    Base(int _a) {
        type = "Base";
        a = _a;
    }
    
    bool operator<(const Base &b) {
        return a < b.a;   
    }

    string getType() {
        lol();
        return type;   
    }
    
private:
    virtual void lol() {
              cout << "base\n";
    }
};

class Derived: public Base {
  
  private:
  virtual void lol() override {
      cout << "derv\n";
  }
};



int main()
{
    Base *d = new Derived();
    d->getType();
   return 0; 
}
