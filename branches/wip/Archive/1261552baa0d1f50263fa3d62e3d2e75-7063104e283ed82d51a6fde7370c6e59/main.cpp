#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

inline const string& shorterString(const string &s1, const string &s2) {
    return s1.size() <= s2.size() ? s1 : s2;
}

bool lengthCompare(const string& s1, const string& s2) {
    return s1.size() <= s2.size();
}

constexpr int new_sz() {
    return 2;
}

constexpr size_t scale(size_t cnt) {   // This is a constexpr function if the argument is a constexpr
    return new_sz() * cnt;
}

// Function taking function pointer as parameter
void useBigger(const string& s1, const string& s2, bool pf(const string&, const string&));   // Function name implicitly treated as pointer to function
void useBigger(const string& s1, const string& s2, bool (*pf)(const string&, const string&));   // Explicitly define parameter as pointer to function


int main() {
    
    //====================================== constexpr Function ==========================================//
    
    constexpr int foo_size = new_sz();
    cout << new_sz() << endl;
    cout << foo_size << endl;
    
    int arr[scale(2)];
    int i = 2;
    int a[scale(i)];
    
    arr[0] = 3; arr[1] = 4;
    a[0] = 2; a[1] = 5;
    
    for (int val: arr) {
        cout << val;
    }
    
    cout << endl;
    
    for (int val: a) {
        cout << val;
    }
    cout << endl;
    
    
    //=================================== Pointer To Function ================================//
    
    bool (*pf)(const string&, const string&);  // Pointer to function of given type
    
    pf = lengthCompare; // We can assign the name of the function, in which case it will store the pointer in pf
    pf = &lengthCompare; // equivalent. & is optional
    
    bool b1 = pf("hello", "goodbye");   // We don't need to dereference pf to make a call to function
    bool b2 = (*pf)("hello", "goodbye");            // Equivalent call
    bool b3 = lengthCompare("hello", "goodbye");    // Equivalent call
    
    
}