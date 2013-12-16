#include <functional>
#include <iostream>
#include <boost/container/stable_vector.hpp>

template <typename... Params>
class Delegate {
private:
    typedef std::function<void(Params...)> Handler;
    typedef boost::container::stable_vector<Handler> Vector;
    Vector m_functions;
public:
    typedef typename Vector::const_iterator cookie;

    cookie connect(Handler&& func) {
        m_functions.push_back(std::move(func));
        return m_functions.begin() + m_functions.size() - 1;
    }

    template <typename... BindArgs, typename Sfinae = typename std::enable_if<(sizeof...(BindArgs)>1), void>::type>
    cookie connect(BindArgs&&... args) {
        return connect(Handler(std::bind(std::forward<BindArgs>(args)...)));
    }

    void disconnect(cookie which) {
        m_functions.erase(which);
    }

    template <typename ... Args> void operator()(Args...args) {
        for(auto const& handler : m_functions) 
            handler(args...);
    }
};

//////////////////////////////////
// demonstration
#define CV volatile const
struct BaseClass {
    virtual void print(const std::string& str) CV = 0;
};

struct A : BaseClass {
    void print(const std::string& str) CV { std::cout << " Class A : Print [" << str << "]\n"; }
};

struct B : BaseClass {
    void print(const std::string& str) CV { std::cout << " Class B : Print [" << str << "]\n"; }
};

using namespace std::placeholders;

int main() {
    Delegate <const std::string&> delegate;
    A CV a;
    B CV b;
    auto acookie = delegate.connect(&A::print, std::ref(a), _1);
    auto bcookie = delegate.connect(&B::print, std::ref(b), _1);

    delegate("hello");
    delegate("world");

    delegate.disconnect(acookie);
    delegate("bye world");

    delegate.disconnect(bcookie);
    delegate("nobody there.");  // should not print anything
}
