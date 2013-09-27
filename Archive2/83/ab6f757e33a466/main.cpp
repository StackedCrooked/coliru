
#include <type_traits>
using namespace std;


int main() {
    
    static_assert(is_same<int[], int(&)[]>::value, "An array is not the same as a reference to an array");
    
}

