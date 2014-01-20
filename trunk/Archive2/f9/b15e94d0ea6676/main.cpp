
#include <iostream>

using namespace std;


class MainStruct {
protected:
  class Proto {
    template<typename T>
    struct Internal {
      struct InternalInternal {
          const char* get() const;
      };
    };

    class Tada {
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
};

template<>
struct MainStruct::Proto::Internal<MainStruct::Proto::Tada>::InternalInternal {
    //const char* get() const {
    //    return "HELLO";
    //}
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
    
    cout << "2345" << endl;
    
    //MainStruct::Internal<int>::InternalInternal aa;
    //cout << aa.get() << endl;
    //
    //Namespace::Internal<int>::InternalInternal bb;
    //cout << bb.get() << endl;
    
    return 1;
}