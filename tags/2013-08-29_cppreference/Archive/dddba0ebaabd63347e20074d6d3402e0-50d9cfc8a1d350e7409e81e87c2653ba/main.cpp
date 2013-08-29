template <typename T>
struct has_typedef_handle_type {
    // Types "yes" and "no" are guaranteed to have different sizes,
    // specifically sizeof(yes) == 1 and sizeof(no) == 2.
    typedef char yes[1];
    typedef char no[2];
 
    template <typename C>
    static yes& test(typename C::handle_type*);
 
    template <typename>
    static no& test(...);
 
    // If the "sizeof" the result of calling test<T>(0) would be equal to the sizeof(yes),
    // the first overload worked and T has a nested type named foobar.
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <bool b, typename T, typename TD>
struct enable_if_handle { };

template <typename T, typename TD>
struct enable_if_handle<false, T, TD> {
    typedef T type;
};

template <typename T, typename TD>
struct enable_if_handle<true, T, TD>{
    typedef typename TD::handle_type type;
};

template <typename T>
struct default_handle_deleter {
    void operator () ( T& handle ) {
        // No-op; handle will invoke default destructor upon exist. 
        // You should override this
    }
};

template <typename T, typename TDx = default_handle_deleter<T>>
class handle {
public:
    // I'm trying to default the below to `T` in the case that there is no handle_type on the deleter
	typedef typename enable_if_handle<has_typedef_handle_type<TDx>::value, TDx, T>::type handle_type;
	typedef TDx deleter_type;

};

int main ( int argc, char* argv[] ) {
    handle<int> testing;
}