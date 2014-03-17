#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/function.hpp>
#include <boost/phoenix.hpp>

#include <iostream>

struct X
{
    int foo() const { return 42; }

    // non-const and taking parameters
    int bar(std::string number) { return std::stoi(number); }

    virtual ~X() {
        std::cout << "I'm stepping out here\n";
    }
};

template <typename Ptmf/* = R(T::*)(Args...) const*/, typename R, typename T, typename... Args>
struct weak_member_invoke
{
    template <typename...> struct result { typedef R type; };

    weak_member_invoke(Ptmf ptmf) : _ptmf(ptmf) {}

    template <typename T1, typename... TOther>
        R operator()(boost::weak_ptr<T1> const& wp, TOther&&... other) const {
            auto locked = wp.lock();
            if (!locked)
                throw boost::bad_weak_ptr();

            return ((*locked).*_ptmf)(std::forward<TOther>(other)...);
        }

  private:
    Ptmf _ptmf;
};

template <typename R, typename T, typename... Args>
   weak_member_invoke<R(T::*)(Args...) const, R, T, Args...> weak_member(R(T::*f)(Args...) const) { return { f }; }
template <typename R, typename T, typename... Args>
   weak_member_invoke<R(T::*)(Args...), R, T, Args...> weak_member(R(T::*f)(Args...)) { return { f }; }

using namespace boost;
using phoenix::bind;

int main()
{
    function<int()> bound_foo;

    {
        auto x = make_shared<X>(); 

        bound_foo = bind(weak_member(&X::bar), weak_ptr<X>(x), "17");

        std::cout << "Bound foo returns: " << bound_foo() << "\n";
    }

    // the bind expression keeps the shared pointer alive
    std::cout << "Bound foo returns: " << bound_foo() << "\n";
}
