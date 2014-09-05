#include <iostream>
#include <iterator>
#include <algorithm>

#include <string>
#include <vector>
#include <set>

#include <memory>

using namespace std;

#define PRINT_CONTAINER(x) \
    copy(begin(x), end(x), ostream_iterator<decltype(*begin(x))>(cout, " ")); \
    cout << endl
    
#define PRINT(x) cout << x << endl

int globalVariable;

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
    shared_ptr<Duck> donald(new Duck{"Donald", 18});
    shared_ptr<Duck> daisy(new Duck{"Daisy", 18});
    
    donald->assignPartner(daisy);
    daisy->assignPartner(donald);
}
