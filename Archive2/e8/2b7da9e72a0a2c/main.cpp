
#include <iostream>

using namespace std;


class MainStruct {
    private:
    
    template<typename T>
    struct Internal {
        struct InternalInternal {
            void print();
        };
    };

    template<typename T>
    void foo();
    
    public:
    
    // function for call private template function
    
    template<typename T>
    void callFoo() {
        foo<T>();
    }
    
    // error: explicit specialization of 'InternalInternal' after instantiation
    // solution: (1)
    /*
    template<typename T>
    void callInternal() {
        Internal<int>::InternalInternal().get();
    }
    */
    
    // (1)
    template<typename T>
    void callInternal(); // look (2) and (3)
    
    
    // error: explicit specialization in non-namespace scope 'struct MainStruct'
    /*
    template<>
    struct Internal<int>::InternalInternal {
        const char* get() const {
            return "HELLO";
        }
    };
    */
    
    // error: explicit specialization in non-namespace scope 'class MainStruct'
    /*
    template<>
    void foo<int>() {
        cout << "foo<int>" << endl;
    }
    */
};

// (2)
// error: explicit specialization of 'InternalInternal' after instantiation
/*
template<typename T>
void MainStruct::callInternal() {
    Internal<int>::InternalInternal().get();
}
*/

// OK
// вызывающий этот код вещи должны быть после этой специализации
template<>
struct MainStruct::Internal<int>::InternalInternal {
    void print() {
        cout << "HELLO" << endl;
    }
};

// (3)
// OK
template<typename T>
void MainStruct::callInternal() {
    Internal<int>::InternalInternal().print();
}


//OK
template<typename T>
void MainStruct::foo() {
    cout << "foo<T>" << endl;
}

// OK
template<>
void MainStruct::foo<int>() {
    cout << "foo<int>" << endl;
}

// BUT
// инстанцировать внутри namespace можно спокойно
namespace Namespace {
    template<typename T>
    struct Internal {
        struct InternalInternal {
            const char* get() const;
        };
    };
    
    // NO_ERROR    
    template<>
    struct Internal<int>::InternalInternal {
        const char* get() const {
            return "HELLO2";
        }
    };
    
}

int main() {
    
    // error: 'Internal' is a private member of 'MainStruct'
    // MainStruct::Internal<int>::InternalInternal().print();
    
    // OK
    MainStruct().callInternal<int>();
    
    MainStruct().callFoo<float>();
    MainStruct().callFoo<int>();
    
    Namespace::Internal<int>::InternalInternal bb;
    cout << bb.get() << endl;
    
    return 1;
}