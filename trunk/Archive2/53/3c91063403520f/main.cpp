#include <iostream>
#include <string>
#include <vector>

class Alpha
{
    public:
    
    Alpha() {
    }
    
    Alpha(const Alpha &other) {
        std::cout << "Copy ctr.\n";
        this->a = other.a;
        this->b = other.b;
    }
    
    Alpha operator + (const Alpha &rhs) {
        std::cout << "Addition operator.\n";
        this->a += rhs.a;
        this->b += rhs.b;
        return *this;
    }
    
    void print_me() {
        std::cout << this->a << ", " << this->b << std::endl;
    }
    
    private:
    int a = 4;
    int b = 5;
};


int main()
{
    Alpha a,b;
    
    Alpha c;
    
    c = a+b;

    c.print_me();
    
    
    return 0;
}
