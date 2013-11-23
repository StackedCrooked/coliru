#include <iostream>
#include <stdlib.h>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

typedef void (*func)();

typedef struct alpha {      // alpha stands for alphabet, really it's a char
    func fptr;
    struct alpha * alphas;
} keychar;


// Really no need for the template here, I could make it
// an optional constructor argument...
// But templates look cool!
template<bool logfail = false>
class ssearch {
private:
    alpha chars[256];
    func keyfail;
public:

    ssearch() {
        for(int i = 0; i < 256; i++) chars[i] = {  };
        if (logfail) keyfail = []() { printf("Error: Could not find key. "); };
        else keyfail = [](){};
    }

    void addkey(string s, func f) { // Adds a key
        alpha* ptr = chars;

        for(int i = 0; i < s.length(); i++) {
            if (!ptr->alphas) { // Check if the alpha array isn't initialized
                 ptr->alphas = (alpha*) malloc(sizeof(alpha) << 8); // Allocates room for 256 alpha structs
                 for(int j = 0; j < 256; j++) ptr->alphas[j] = { }; // Initialize for all 256 characters
            }
            // Casting unsigned int isn't necessary, but it gets rid of silly compiler warnings for uses chars to index
            ptr = &(ptr->alphas[(unsigned int)s[i]]); // Sets the pointer to the next character key

            if(i == s.length() - 1)  ptr->fptr = f; // Assign
        }
    }

    func gettoken(string s) {
        alpha* ptr = chars;

        int n = s.length() - 1; // Try not to do the subtraction every loop

        for(int i = 0; i < s.length(); i++) {
            ptr = &(ptr->alphas[(unsigned int)s[i]]);        // Sets the pointer to the next character key
            if ((uintptr_t)ptr < 0x800) break; // Search failed, just checks the address. Because usually when the search fails the pointer goes down there...
            if (i == n) return ptr->fptr;
        }
        return keyfail; // Returns the function depending on the 'logfail' bool
    }
};


int main()
{
    ssearch<true> s;
    // Assign a lambda to "test"
    s.addkey("test", [](){ cout << "Works!" << endl; });

    s.gettoken("test")();       // Should execute ^
    s.gettoken("not a key")();  // Doesn't find the key

    return 0;
}
