#include <iostream>
#include <iterator>
#include <algorithm>

#include <string>
#include <vector>
#include <set>

#include <functional>

#include <memory>

using namespace std;

#define PRINT_CONTAINER(x) \
    copy(begin(x), end(x), ostream_iterator<decltype(*begin(x))>(cout, " ")); \
    cout << endl
    
#define PRINT(x) cout << x << endl

int globalVariable;

void print(int lhs, int rhs)
{
    cout << "lhs " << lhs << " rhs " << rhs << endl;
}

class Duck
{
    template<typename T> using smart_ptr = shared_ptr<T>;

    string name;
    int age;
    smart_ptr<Duck> partner;
public:
    Duck(string const& name, int const age)
      : name{name}, age{age} 
        { PRINT("Constructor 1 {" << name << ", " << age << "}"); }
        
    Duck(string const& name) 
      : Duck{name, 0} 
        { PRINT("Constructor 2 {" << name << ", " << age << "}"); }
    
    ~Duck()
        { PRINT("Destructor {" << name << ", " << age << "}"); }
        
    void assignPartner(std::shared_ptr<Duck> const& anotherDuck)
    {
        partner = anotherDuck;
    }
};

int main()
{
    std::function<void(int,int)> switchedParamsUsingPlaceHolders = std::bind(&print, placeholders::_2, placeholders::_1);
    std::function<void(int,int)> sameAsPrint = std::bind(&print, placeholders::_1, placeholders::_2);
    std::function<void(int)> printWithDefaultValue = std::bind(&print, 100, placeholders::_1);
    
    print(1,2);
    switchedParamsUsingPlaceHolders(1,2);
    sameAsPrint(1,2);
    printWithDefaultValue(5);
}
