#include <iostream>
#include <vector>

class A{
public:
    A(int val):a(val){
        std::cout<<"Constructor "<<a<<"\n";   
    }
    A(const A& other){
        std::cout<<"Copy Constructor "<<other.a<<"\n";   
    }
    A(A&&other){
        std::cout<<"Move Constructor "<<other.a<<"\n";   
    }
    void operator=(const A& other){
        std::cout<<"operator= "<<a<<"\n";    
    }
    void operator=(A&& other){
        std::cout<<"operator= (rvalue) "<<other.a<<"\n";    
    }

int a;
};

int main(){
	std::vector<A> vec;
    vec.push_back(A(5));
    std::cout<<"____\n";
    vec.push_back(A(1));

}