#include <cassert>
#include <iostream>
#include <string>
#include <memory>
#include <set>


template<typename T>
struct Proxy;


std::string shorten(void* ptr)
{
    return "0x" + std::to_string(reinterpret_cast<long>(ptr) % 0x100);
}


template<typename T>
struct Proxiable
{
    void register_ref(Proxy<T>* ref)
    {
        std::cout << "register_ref: this=" << shorten(this) << ", ref=" << shorten(ref) << std::endl;
        assert(proxies.count(ref) == 0);
        proxies.insert(ref);
    }

    void unregister_ref(Proxy<T>* ref)
    {
        std::cout << "unregister_ref this=" << shorten(this) << ", ref=" << shorten(ref) << std::endl;
        assert(proxies.count(ref) == 1);
        std::cout << std::endl;
        proxies.erase(ref);
    }

    std::set<Proxy<T>*> proxies;
};


template<typename T>
struct Proxy
{
    Proxy() : target(NULL)
    {
    }

    Proxy(T& p) :
        target(&p)
    {
        if (target)
        {
            target->register_ref(this);
        }
    }

    ~Proxy()
    {
        if (target)
        {
            target->unregister_ref(this);
        }
    }

    Proxy(const Proxy& rhs) :
        target(rhs.target)
    {
        if (target)
        {
            target->register_ref(this);
        }
    }

    Proxy& operator=(Proxy rhs) // copy swap
    {
        this->swap(rhs);
        return *this;
    }

    void reset(T& t)
    {
        Proxy<T>(t).swap(*this);
    }

    void swap(Proxy& rhs)
    {
        using std::swap;
        swap(target, rhs.target);
    }

    T* target;
};


struct Resource : Proxiable<Resource>
{
};


struct ResourceUser
{
    ResourceUser(Resource& resource) : proxy(resource) {}

    Proxy<Resource> proxy;
};


void run()
{
    Resource a, b;

    ResourceUser user_a(a);
    ResourceUser user_b(b);
    user_b = user_a;

    std::cout << "End of scope" << std::endl;
}


int main()
{
    run();
}
