
#include <iostream>

using namespace std;


class MainStruct {
    template<typename T>
    struct Internal {
        struct InternalInternal {
            const char* get() const;
        };
    };
    
    // error: explicit specialization in non-namespace scope 'struct MainStruct'
    /*
    template<>
    struct Internal<int>::InternalInternal {
        const char* get() const {
            return "HELLO";
        }
    };
    */
};

template<>
struct MainStruct::Internal<int>::InternalInternal {
    const char* get() const {
        return "HELLO";
    }
};

// BUT

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
    
    MainStruct::Internal<int>::InternalInternal aa;
    cout << aa.get() << endl;
    
    Namespace::Internal<int>::InternalInternal bb;
    cout << bb.get() << endl;
    
    return 1;
}