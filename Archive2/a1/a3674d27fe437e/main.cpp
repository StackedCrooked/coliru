#include <iostream>
#include <vector>

class A{
public:
    A(int){
        std::cout<<"Constructor\n";   
    }
    A(const A&){
        std::cout<<"Copy Constructor\n";   
    }
    A(A&&){
        std::cout<<"Move Constructor\n";   
    }
    void operator=(const A&){
        std::cout<<"operator= \n";   
    }
    void operator=(A&&){
        std::cout<<"operator= (rvalue) \n";   
    }

};

int main(){
	std::vector<A> vec;
    vec.push_back(A(5));
    vec.push_back(A(5));
    std::cout<<"____\n";
    std::vector<A> vec2;
    vec2.push_back(A(5));
    vec2.emplace_back(5);

}