#include <memory>


    class Parent {
    public:
        static const std::shared_ptr<Parent>& get_singleton();
    };

    class Child: public Parent {
    public:
        Child(){}
        static const std::shared_ptr<Parent>& singleton;
    };

    const std::shared_ptr<Parent>& singleton = std::make_shared<Child>();

    const std::shared_ptr<Parent>& Parent::get_singleton() {
        return singleton;
    }


int main() {
}