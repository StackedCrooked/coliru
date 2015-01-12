
template<class T>
struct my_type_implementation
{
    // impl
};


template<class T>
using my_type = my_type_implementation<T>;


int main() {
    
    my_type<int> a;
    
    (void)a;
    
    return 0;
}