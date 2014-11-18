#include <string>

enum E {
    Thing1,
    Thing2
};

std::string toString(E e) {
    switch (e) {
        case Thing1: return "Thing1";
        case Thing2: return "Thing2";
    }
    
    throw;
}

int main() {
    E e = Thing1;
    std::string message = "I'm printing a " + e; //oops, forgot to call toString()
}