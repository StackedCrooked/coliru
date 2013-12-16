
template<typename T> struct return_type {
    typedef int type;
};

template<typename T> struct function_contents {
    typename return_type<T>::type func() {
    }
};

int main () {
    
    function_contents<void> arf;
    int a = arf.func();
    
}