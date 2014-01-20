
#include <iostream>

using namespace std;

struct Outer {
    const char* getTypeName() const {
        return "Outer";
    };
};

template<typename T>
struct Stru {
    template<typename U>
    struct Internal {
        const char* getTypeName() const;
    };
    
    struct Internal2 {
        const char* getTypeName() const;
    };
    
    void foo(const Internal<T>& value) {
        cout << "foo " << value.getTypeName() << endl;
    }
    
    void foo2(const Internal2& value) {
        cout << "foo " << value.getTypeName() << endl;
    }
    
    void boo(const Outer& value) const {
        cout << "foo " << value.getTypeName() << endl;
    }
};

template<>
struct Stru<int>::Internal2 {
    const char* getTypeName() const {
        return "Internal2 int";
    };
};

//template<>
//struct Stru<int> {
//    void foo() {
//        cout << "foo - int " << endl;
//    }
//};

template<>
template<>
struct Stru<int>::Internal<int> {
    const char* getTypeName() const {
        static const char* name = "int";
        return name;
    }
};

//template<>
//struct Stru<float> {
//    void foo() {
//        cout << "foo - float " << endl;
//    }
//};

template<>
template<>
struct Stru<float>::Internal<float> {
    const char* getTypeName()const {
        static const char* name = "float";
        return name;
    }
};

int main() {
    
    const Stru<int>::Internal<int> param;    
    Stru<int>().foo(param);
    
    //Stru<int>().foo(Stru<int>::Internal<int>());
    
    Outer outer;
    Stru<int>().boo(outer);
    
    Stru<int>().boo(Outer());
//    Stru<float>().foo(Stru<float>::Internal<float>());

Stru<int>::Internal2 param2;
Stru<int>().foo2(param2);

const int& a = 10;
// int& a = 10; // error: non const
cout << a << endl;

const Stru<int>::Internal<int>& value = Stru<int>::Internal<int>();
// Stru<int>::Internal<int>& value = Stru<int>::Internal<int>(); // error: non-const
cout << value.getTypeName() << endl;
    
    return 1;
}