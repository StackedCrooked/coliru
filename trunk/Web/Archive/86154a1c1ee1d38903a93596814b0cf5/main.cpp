#include <iostream>

template <typename T>
struct default_get {
    T operator () ( T& current ) {
        return current;
    }
};

template <typename T>
struct default_set {
    
    void operator () ( T& current, const T& val ) {
        current = val;
    }
    
    void operator () ( T& current, T&& val ) {
        current = val;
    }
    
};


template <typename T, typename TGet = default_get<T>, typename TSet = default_set<T>>
struct Property {
public:
     T val;
     
     Property () {
         
     }
     
     Property ( const T& value ) {
         operator=( value );
     }
     
     Property ( T&& value ) {
         operator=( value );
     }
     
     Property& operator= ( const T& right ) {
         TSet set;
         set( val, right );
         return *this;
     }
     
     Property& operator= ( T&& right ) {
         TSet set;
         set( val, right );
         return *this;
     }
     
     operator T () {
         TGet get;
         return get( val );
     }
};

struct myget {
    int operator () ( int& current ) {
        return current;
    }
};

struct myset {
    void operator () ( int& current, const int& val ) {
        current = val - 101;
    }
    
    void operator () ( int& current, int&& val ) {
        current = val;
    }  
};

int main ( int argc, char* argv[] ) {
     
     Property<int> Tango = 245;
     Property<int, myget, myset> Foxtrot = 245;
     std::cout << "Tango = 245: " << Tango << std::endl;
     std::cout << "Foxtrot = 245: " << Foxtrot << std::endl;
     Tango = 101;
     Foxtrot = 101;
     std::cout << std::endl;
     std::cout << "Tango = 101: " << Tango << std::endl;
     std::cout << "Foxtrot = 101: " << Foxtrot << std::endl;
     
     return 0;
}