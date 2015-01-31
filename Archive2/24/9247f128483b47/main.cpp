#include <iostream>
#include <vector>

template<class T>
class MyContainer{
public:
    MyContainer(const T& val):
    value_(val){}
    
    void test(){
		std::cout << value_;
	}
private:
	T value_;
};

int main(){
	MyContainer<int> container(5);
	container.test();
}