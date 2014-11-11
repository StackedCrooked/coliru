#include <iostream>
#include <string>

template<class Tag>
struct Ref {
    private:
        void* something;
        void* another_thing;
        
    public:
        template<class T>
        Ref<T> operator[](std::string name) {
           //magic->getMember(something, name.c_str); 
           return Ref<T>();
        }
};

struct java {
    struct BeanProxyFactory {};
    struct lang {
        struct String {};
    };
};

template<class T>
class RefExtend {};

template <>
class RefExtend<java::lang::String> {
    public:
        operator std::string() const {
            return "Testing everyone";
        }
};

class StringRef : public Ref<java::lang::String> {
    public:
        StringRef(Ref<java::lang::String> other) {
        }
        operator std::string() const {
            return "not good enough!";
        }
};


int main() {
    auto some_instance = Ref<java::BeanProxyFactory>();
    
    //std::string bean_string = some_instance.operator[]<java::lang::String>("createMagicBeanString"); // doesn't work, Ref<T> doesn't have string operator
    std::string bean_string = StringRef(some_instance.operator[]<java::lang::String>("CreatemagicBeanString")); // Not good enough, I don't want to have to explicitly initialize the extended version!
    
    std::cout << bean_string << "\n";
}