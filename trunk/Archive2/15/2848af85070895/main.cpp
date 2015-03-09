#include <iostream>
#include <utility>

template<class T>
struct proxy_arg {
    void* ptr;
    T (*ctor)(proxy_arg&&);
    void (*assign)(proxy_arg&&, T&);
    
    template<class O>
    O&& as()&& {
        return std::forward<O>(*static_cast<std::remove_const_t<std::remove_reference_t<O>>*>(ptr));
    }
    template<class O>
    proxy_arg(O&&o):
        ptr(const_cast<std::remove_const_t<std::remove_reference_t<O>>*>(&o)),
        ctor([](proxy_arg&& self)->T{
            return std::move(self).template as<O>();
        }),
        assign([](proxy_arg&& self, T& target){
            target = std::move(self).template as<O>();
        })
    {}
    proxy_arg(proxy_arg const&)=delete;
    operator T()&& {
        return ctor(std::move(*this));
    }
    void assign_to(T& t)&& {
        assign( std::move(*this), t );
    }
};

static size_t created = 0;
static size_t moved = 0;
static size_t copied = 0;
static size_t destroyed = 0;

void reset() {
    created = moved = copied = destroyed = 0;
}
void print() {
    std::cout << "Created:   " << created << '\n';
    std::cout << "Moved:     " << moved << '\n';
    std::cout << "Copied:    " << copied << '\n';
    std::cout << "Destroyed: " << destroyed << '\n';
}
struct counter {
    counter() {++created;}
    counter(counter const&) {++created;++copied;}
    counter(counter&&) {++created;++moved;}
    void operator=(counter const&) {++copied;}
    void operator=(counter &&) {++moved;}
    ~counter() {++destroyed;}
    void operator=(proxy_arg<counter>&& p) {
        std::move(p).assign_to(*this);
    }
};

void func1( counter const& x ) {
    auto local = x;
    (void)local;
}
void func1( counter& local, counter const& x ) {
    local = std::move(x);
}
void func1( counter && x) {
    auto local = std::move(x);
    (void)local;
}
void func1( counter& local, counter && x) {
    local = std::move(x);
}
void func2( counter x ) {
    auto local = std::move(x);
    (void)local;
}
void func2( counter& local, counter x ) {
    local = std::move(x);
}
void func3( proxy_arg<counter> x ) {
    counter local = std::move(x);
    (void)local;
}
void func3( counter&local, proxy_arg<counter> x ) {
    local = std::move(x);
}
int main() {
    counter a, b;
    reset();
    std::cout << "func1\n";
    func1(a);
    func1(std::move(a));
    func1(b, a);
    func1(b, std::move(a));
    print(); reset();
    std::cout << "func2\n";
    func2(a);
    func2(std::move(a));
    func2(b, a);
    func2(b, std::move(a));
    print(); reset();
    std::cout << "func3\n";
    func3(a);
    func3(std::move(a));
    func3(b, a);
    func3(b, std::move(a));
    print(); reset();
}