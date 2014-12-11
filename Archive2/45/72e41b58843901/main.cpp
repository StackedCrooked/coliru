#include <iostream>
using namespace std;

using PyObject = void;

    template< typename Derived >
    class Object
    {
    private:
        PyObject* p{nullptr};

    public:
        #define DECAY(T)     			typename std::decay<T>::type
        #define IS_INTEGRAL(T) 			std::is_integral< DECAY(T) >::value
        #define IS_FLOATING(T) 			std::is_floating_point< DECAY(T) >::value
        #define SUBFAIL_UNLESS(PRED)  	typename X = typename std::enable_if<PRED>::type

        // long, float
        template<typename T, SUBFAIL_UNLESS(IS_INTEGRAL(T)) > explicit Object( T&& t      ) : Object{ pyob_from_integral(t) }  { }
        template<typename T, SUBFAIL_UNLESS(IS_FLOATING(T)) > explicit Object( T&& t, ... ) : Object{ pyob_from_floating(t) }  { }

    private:
        // constructor helpers return charged pointer
        PyObject* pyob_from(bool    b) { cout << "int"; return nullptr; }

        template<typename T> PyObject* pyob_from_integral( T t ) { cout << "int"; return nullptr; }
        template<typename T> PyObject* pyob_from_floating(T t)   { cout << "int"; return nullptr; }
    };

    class Generic : Object<Generic>
    {
        using Object<Generic>::Object;
        using Object<Generic>::operator=;

    public:
        static PyObject* from_generic_pyob( PyObject* pyob_charged ) { return pyob_charged; }
    };

int main() {
	// your code goes here
	return 0;
}