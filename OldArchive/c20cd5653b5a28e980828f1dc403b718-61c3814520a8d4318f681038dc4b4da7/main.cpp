#include <utility>

template <typename T, typename tag_type>
struct TaggedValue {
    
    template<typename ...Args>
    TaggedValue(Args && ...args) : val(std::forward<Args>(args)...) { }
    
    operator const T& () const { return val; }
    
    T val;
};

struct radian_tag {};
struct degrees_tag {};

int main ( int argc, char* argv[] ) {
 
     TaggedValue<double, radian_tag> radians = 3.14159;
     TaggedValue<double, degrees_tag> degrees = 180.0;
     
}