#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

#include <boost/variant.hpp>

#include <cxxabi.h>

auto reduceToObjectArg = [](auto f, auto&&... args) {
    return [&](auto &&object) {
        return f(std::forward<decltype(object)>(object), std::forward<decltype(args)>(args)...);
    };
};

template<typename F, typename... Args>
struct ApplicatorFunc {};

template<typename Func>
struct ReduceToObjectArgImpl;

template<typename F, typename... Args>
struct ReduceToObjectArgImpl<ApplicatorFunc<F, Args...>> {
    using type = decltype(reduceToObjectArg(std::declval<F>(), std::declval<Args>()...));
};

template<typename Func>
using ReduceToObjectArg = typename ReduceToObjectArgImpl<Func>::type;

//Holds any object t for which f(t) works, where f is an instance of one of Funcs.
//Which action to take is determined when apply() is called.
//The class design is based on Sean Parent's Concept-Based Polymorphism.
template<typename... Funcs>
struct Applicator {
    //Create a new Applicator and store the given object in the right type of model for later use.
    template<typename T>
    Applicator(T t) : self_{new Model<T>(std::move(t))} {}

    //Copy an Applicator by copying the contents of the unique pointer and move it as normal.
    Applicator(const Applicator &other) : self_{other.self_->copy()} {}
    Applicator(Applicator &&other) = default;

    //Assign to an Applicator using copy-swap.
    Applicator &operator=(Applicator other) {
        swap(other);
        return *this;
    }

    //Swap an Applicator by swapping the unique pointers.
    void swap(Applicator &other) noexcept {
        using std::swap;
        swap(self_, other.self_);
    }

    //Call an instance of one of Funcs... on the given object.
    template<typename F, typename... Args>
    void apply(F f, Args&&... args) {
        self_->apply(reduceToObjectArg(f, std::forward<Args>(args)...));
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
        virtual Concept *copy() const = 0;

        virtual void apply(const boost::variant<ReduceToObjectArg<Funcs>...> &func) = 0;
    };

    //Defines the model for this contained object.
    template<typename T>
    struct Model : Concept {
        Model(T t) : object_(std::move(t)) {}

        //Creates a new model from the existing one.
        Concept *copy() const override {
            return new Model(object_);
        }

        //Applies the function contained in the given variant to the stored object.
        void apply(const boost::variant<ReduceToObjectArg<Funcs>...> &func) {
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

using IntFoo = Foo<int>;
using DoubleFoo = Foo<double>;
using CharFooFoo = Foo<Foo<char>>;

struct PrintFoo {
    template<typename T>
    void operator()(Foo<T> t, int i) {
        auto name = typeid(t).name();

        auto status = int{};
        auto ptr = std::unique_ptr<char, void(*)(void *)>(abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free);

        if (status == 0) {
            std::cout << "Got " << ptr.get() << " and " << i << '\n';
        } else {
            std::cout << name << '\n';
        }
    }
};

struct PrintFoo2 {
    template<typename T>
    void operator()(Foo<T> t) {
        auto name = typeid(t).name();
        std::cout << name << '\n';
    }
};

int main() {
    std::vector<Applicator<ApplicatorFunc<PrintFoo, int>, ApplicatorFunc<PrintFoo2>>> foos{
        IntFoo{}, DoubleFoo{}, IntFoo{}, IntFoo{}, CharFooFoo{}
    };

    for (auto &&foo : foos) {
        foo.apply(PrintFoo{}, 5);
        foo.apply(PrintFoo2{});
    }
}
