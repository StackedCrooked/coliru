#include <iostream>

template <typename TypesPolicy>
struct Bitset {
    inline Bitset() {
        for (unsigned char& c : arr)
            c = 0;
    }
    
    union {
        TypesPolicy types;
        unsigned char arr[sizeof(TypesPolicy)];
    };
};

//http://msdn.microsoft.com/en-us/library/ewwyfdbe%28v=vs.120%29.aspx
struct Types {
    unsigned char opacity : 1;
    unsigned char margin : 4;
    unsigned char padding : 4;
    unsigned char zIndex : 1;
    unsigned char borderWidth : 4;
};


struct FooEnd {};

template <typename T, std::size_t Size, typename P = FooEnd>
struct Foo : public P {
    inline Foo() : var(0) {}
    
    T var : Size;
};

template <typename T, std::size_t Size>
struct Foo<T, Size, FooEnd> {
    inline Foo() : var(0) {}
    
    T var : Size;
};


class A {
  public:
    template<class T> T function_m() { return T(); }
};

template<class U> void function_n(U argument) {
  char object_x = argument.template function_m<char>();
}


int main() {
    function_n(A());
    
    
    std::cout << sizeof(Types) << std::endl;
    
    
    Bitset<Types> b;
    b.types.opacity = 1;

    
    b.types.margin = 1 + 2 + 4 + 8;

    
    b.types.opacity = 0;
    
    unsigned int arr[3]{1};
    
    std::cout << "arr: " << arr[0] << " " << arr[1] << " " << arr[2] << std::endl;
    
    
    Foo<unsigned char, 2, Foo<unsigned char, 1, Foo<unsigned char, 4>>> foo;
    
}