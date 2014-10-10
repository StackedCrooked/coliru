#include <iostream>
#include <memory>
#include <typeinfo>
#include <utility>

#include <boost/variant.hpp>

//Holds any object t for which f(t) works, where f is an instance of one of Funcs.
//Which action to take is determined when apply() is called.
//The class design is based on Sean Parent's Concept-Based Polymorphism.
template<typename... Funcs>
struct Applicator {
    //Create a new Applicator and store the given object in the right type of model for later use.
    template<typename T>
    Applicator(T t) : self_{new Model<T>(std::move(t))} {}

    //Call an instance of one of Funcs... on the given object.
    template<typename F>
    void apply(F f) {
        self_->apply(f);
    }

private:
    //Visits the function variant to call the contained function on a given object.
    template<typename T>
    struct FuncVisitor : boost::static_visitor<> {
        //Creates a new visitor with an object to use as an argument.
        FuncVisitor(T &t) : object_{t} {}

        //Calls the contained function on the object.
        template<typename F>
        void operator()(F f) const {
            f(object_);
        }

    private:
        T &object_;
    };

    //Defines the concept of this contained object.
    //This includes applying a given function.
    struct Concept {
        virtual ~Concept() = default;
        virtual void apply(const boost::variant<Funcs...> &func) = 0;
    };

    //Defines the model for this contained object.
    template<typename T>
    struct Model : Concept {
        Model(T t) : object_(std::move(t)) {}

        //Applies the function contained in the given variant to the stored object.
        void apply(const boost::variant<Funcs...> &func) {
            boost::apply_visitor(FuncVisitor<T>(object_), func);
        }

    private:
        //Holds the object initially given to Applicator.
        T object_;
    };

    //Holds the concept for the contained object (actually a model).
    std::unique_ptr<Concept> self_;
};

template<typename T>
struct Foo {};

struct PrintFoo {
    template<typename T>
    void operator()(T t) {
        auto name = typeid(t).name();
        std::cout << "PrintFoo got " << name << '\n';
    }
};

struct PrintFoo2 {
    template<typename T>
    void operator()(T t) {
        auto name = typeid(t).name();
        std::cout << "PrintFoo2 got " << name << '\n';
    }
};

int main() {
    Applicator<PrintFoo, PrintFoo2> foo{Foo<int>{}};

    foo.apply(PrintFoo{});
    foo.apply(PrintFoo2{});
}
