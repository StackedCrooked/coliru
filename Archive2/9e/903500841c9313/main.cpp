#include <memory>
#include <iostream>

template<class T>
struct Weak : public std::weak_ptr<T> {
    
    Weak(const std::shared_ptr<T>& shared) : std::weak_ptr<T>(shared) { }
    
    std::shared_ptr<T> operator->() {
        auto shared = std::weak_ptr<T>::lock();
        if(shared == nullptr) {
            throw std::bad_weak_ptr(); // or some other exception
        }
        return shared;
    }
    
};

struct Test {
 
    void TestFunction() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    
};

int main()
{
    auto shared = std::make_shared<Test>();
    
    Weak<Test> weak = shared;
    
    weak->TestFunction();
}