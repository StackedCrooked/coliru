#include <iostream>

class A{
 public:
    A(int a):a_(a){};
 private:
    int a_;
    friend std::ostream& operator<<(std::ostream& os,const A&);
};

std::ostream& operator<<(std::ostream& os,const A& a_instance){
    os<<  a_instance.a_;
    return os;
}
int main(int argc, char** argv) {
    A test(10);
    std::cout<<test;
}
