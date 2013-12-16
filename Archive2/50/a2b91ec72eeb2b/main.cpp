#include <functional>
#include <iostream>
#include <map>

template <typename... Params>
class Delegate {
private:
    typedef std::function<void(Params...)> Handler;
    typedef std::map<size_t, Handler> FunctionMap;
    FunctionMap m_functions;
    size_t id_gen;
public:
    Delegate() : id_gen(0) {}

    typedef typename FunctionMap::key_type cookie;

    cookie connect(Handler&& func) {
        m_functions[id_gen] = std::move(func);
        return id_gen++;
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
            handler.second(args...);
    }
};

//////////////////////////////////
// demonstration
#define CV volatile const
struct BaseClass {
    virtual void print(const std::string& str) CV = 0;
};

struct A : BaseClass {
    A() {}
    void print(const std::string& str) CV { std::cout << " Class A : Print [" << str << "]\n"; }
};

struct B : BaseClass {
    B() {}
    void print(const std::string& str) CV { std::cout << " Class B : Print [" << str << "]\n"; }
};

using namespace std::placeholders;

int main() {
    Delegate <const std::string&> delegate;
    A CV a;
    B CV b;
    auto acookie1 = delegate.connect(&A::print, std::ref(a), _1);
    auto acookie2 = delegate.connect(&A::print, std::ref(a), _1);
    auto bcookie  = delegate.connect(&B::print, std::ref(b), _1);

    delegate("hello");
    delegate("world");

    delegate.disconnect(acookie1);
    delegate("bye world1");

    delegate.disconnect(acookie2);
    delegate("bye world2");

    delegate.disconnect(bcookie);
    delegate("nobody there.");  // should not print anything
}
