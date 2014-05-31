#include <vector>
 
namespace vec {
 
    template< typename T >
    class vector {
        // ...
    };
 
} // of vec
 
int main()
{
    std::vector<int> v1; // Standard vector.
    vec::vector<int> v2; // User defined vector.
 
    v1 = v2; // Error: v1 and v2 are different object's type.
 
    {
        using namespace std;
        vector<int> v3; // Same as std::vector
        v1 = v3; // OK
    }
 
    {
        using vec::vector;
        vector<int> v4; // Same as vec::vector
        v2 = v4; // OK
    }
 
    return 0;
}