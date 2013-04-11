#include <memory>
#include <vector>
#include <iostream>
#include <type_traits>

struct NotCopyAssignable {
private:
    int a;
    
    NotCopyAssignable ( const NotCopyAssignable& copy ) = delete;
public:
    
    NotCopyAssignable() {
     
    }
    
};

int main ( int argc, char* argv[] ) {
    
    std::cout << std::is_copy_constructible<NotCopyAssignable>::value << std::endl;
    
}