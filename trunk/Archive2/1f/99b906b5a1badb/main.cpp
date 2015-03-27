#include <boost/type.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <iostream>

struct Foo { enum { id = 879 }; };
struct Bar { enum { id = 321 }; };
struct Qux { enum { id = 555 }; };
typedef boost::mpl::vector<Foo, Bar, Qux> Types;

template <typename T>
struct Finder {
  bool operator()() const { return T::id > 500; }
};

struct Callback {
    template<typename T> void operator()() const {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
};

    template <template<typename> class Finder, typename Callback>
    struct ConditionOperation {
        ConditionOperation(Callback cb = {}) : _callback(std::move(cb)) 
        { }

        template <typename T>
        void operator()(boost::type<T>) const {
            if (Finder<T>()())
                _callback.template operator()<T>();
        }

    private:
        Callback _callback;
    };

int main() {
    using namespace boost;

    ConditionOperation<Finder, Callback> op;
    mpl::for_each<Types, boost::type<mpl::_1> >(op);
}
