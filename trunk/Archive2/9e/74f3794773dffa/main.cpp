#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <functional> // for error callback

using namespace std;
namespace {
    void Hello(string str) {
        cout << "Hello " << str << endl;
    }
    
    void Goodbye(string str) {
        cout << "Goodbye " << str << endl;
    }
    
    
    // Function signature for returning void and taking string as argument
    // Instead of writing: 
    // typedef void (*FunctionPtr)(string);
    
    using CallbackPtrA = void (*)(string);
    unordered_map<size_t, CallbackPtrA> aCallbacks {
      {0, Hello}, 
      {1, Goodbye }
    };

    // Function to return from the mapA
    CallbackPtrA  LookupA(size_t key) {
        try {
            return aCallbacks.at(key);
        } catch(...) {
            // return error lambda instead
        }
        return [](string str){ cout << "FATAL LOOKUP: No function to use with 'str': " << str << endl; };
    }
    
    
    // But that's kind of weird. Let's use type_traits. Type traits are mystical but 
    // quite readable, at least in this context
    using CallbackPtrB = std::add_pointer<void(string)>::type;
    unordered_map<size_t, CallbackPtrB> bCallbacks {
      {0, Hello}, 
      {1, Goodbye }
    };

    

    CallbackPtrB  LookupB(size_t key) {
        try {
            return bCallbacks.at(key);
        } catch(...) {
            // return error lambda instead
        }
        
        return [](string str){ cout << "FATAL LOOKUP: No function to use with 'str': " << str << endl; };
    }
    
} // namespace




int main()
{
    cout << "Trying Lookup A" << endl;
    auto funcA1 = LookupA(0);
    auto funcA2 = LookupA(1);
    auto funcA3 = LookupA(2); // this will trigger the error function
    funcA1(" Rafael ");
    funcA2(" Michaelangelo");
    funcA3(" Donatello");    // here the error function is triggered
    
    
    cout << "\n\n\n Now Trying LookupB" << endl;
    auto funcB1 = LookupB(0);
    auto funcB2 = LookupB(1);
    auto funcB3 = LookupB(2); // this will trigger the error function

    funcB1(" Naruto ");
    funcB2(" Shipuuden");
    funcB3(" Konichiwa");   
}