#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
 
class Alpha {
public:
    std::string s;
    // Default constructor
    Alpha() : s("test") {
        std::cout << "Default ctr.\n";
    }

    
    // Copy constructors
    Alpha( Alpha& o) : s(o.s) { 
        std::cout << "Copy ctr!\n";
    }
        
    Alpha(const Alpha& o) : s(o.s) { 
        std::cout << "Const Copy ctr!\n";
    }
        
    // Move constructors
    Alpha(Alpha&& o) : s(std::move(o.s)) {
        std::cout << "Move ctr.\n";
        this->a = std::move(o.a);
        this->b = std::move(o.b);
    }
    
    Alpha(const Alpha&& o) : s(std::move(o.s)) {
        std::cout << "Const Move ctr.\n";
    }
        
    // Assignment operators    
    Alpha& operator = ( Alpha &rhs) {
        std::cout << "non-const Assignment operator.\n";
        return *this;
    }
    
    Alpha& operator = (const Alpha &rhs) {
        std::cout << "Assignment operator.\n";
        return *this;
    }
    
    // Move operators
    Alpha& operator = ( Alpha &&rhs) {
        std::cout << "Move assignment operator.\n";
        return *this;
    }    
           
    Alpha& operator = (const Alpha &&rhs) {
        std::cout << "Const Move assignment operator.\n";
        this->a = std::move(rhs.a);
        this->b = std::move(rhs.b);   

        return *this;
    }    
    
    int a = 5;
    int b = 6;
    
    void print_me() {
        std::cout << a << ", " << b << std::endl;
    }
};
 
Alpha f(Alpha a) {
    return a;
}
 
Alpha operator + (const Alpha &lhs, const Alpha &rhs) {
    std::cout << "Addition operator.\n";
    Alpha tmp;
    tmp.a = lhs.a + rhs.a;
    tmp.b = lhs.b + rhs.b;  
    return tmp;
}

Alpha adder(const Alpha &lhs, const Alpha &rhs) {
    std::cout << "Adder.\n";
    Alpha tmp;
    return tmp;
}


int main()
{
    Alpha a1 = f(Alpha()); // move-construct from rvalue temporary
    Alpha a2 = std::move(a1); // move-construct from xvalue
    Alpha a3 = std::move(a1 + a2);
    std::cout << "-----Hello--------\n";
 //   Alpha a4 = std::move(adder(a1,a2));
 //   std::cout << "-------------\n";
 
    Alpha a5 = a1 + a2; // Inline move constructor ? 
    std::cout << "----World------\n";    
    a5.print_me();
}