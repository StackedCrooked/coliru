#include <memory>


    class Parent {
    public:
        static const std::shared_ptr<Parent>& get_singleton();
    };

    class Child: public Parent {
    public:
        Child(){}
        static const std::shared_ptr<Child>& singleton;
    };

    const std::shared_ptr<Child>& Child::singleton = std::make_shared<Child>();

    const std::shared_ptr<Parent>& Parent::get_singleton() {
        return  Child::singleton;
    }


int main() {
}