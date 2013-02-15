#include <algorithm>    // for std::copy
#include <iterator>     // for std::begin, std::end, std::distance
#include <iostream>     // for std::cout
#include <list>         // for std::list
#include <sstream>      // for std::ostringstream
#include <string>       // for std::string

using namespace std;

// Test class
class X 
{
public:    
    explicit X(int n) 
        : m_n(n) 
    {
        cout << Name() << " created.\n";
    }
    
    ~X()
    {
        cout << Name() << " destroyed.\n";
    }

    string Name() const
    {
        ostringstream os;
        os << "X(" << m_n << ")";
        return os.str();
    }
    
private:
    int m_n;   
};


// Test
int main()
{
    // Array of raw pointers
    typedef X * XPtr;
    
    // Dynamically allocate some objects
    XPtr v[3];
    v[0] = new X(10);
    v[1] = new X(20);
    v[2] = new X(30);
    
    // Build a list of observing pointers from raw array of pointers
    auto count = std::distance(std::begin(v), std::end(v));
    list<X*> l(count);
    std::copy(std::begin(v), std::end(v), std::begin(l));

    // Print list content
    cout << "\nList contains:\n";
    for (auto && e : l)
        cout << e->Name() << endl;       
    cout << '\n';
           
    // Release the allocated objects
    for (auto && e : v)
    {
        delete e;
    }        
}
