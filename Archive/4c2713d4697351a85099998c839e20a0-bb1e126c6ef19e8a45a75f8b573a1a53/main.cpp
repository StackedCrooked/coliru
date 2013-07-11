#include <cassert>
#include <iostream>
#include <memory>
#include <set>


template<typename T>
struct Proxy;


template<typename T>
struct Proxiable
{
    void add_proxy(Proxy<T>* proxy)
    {
        std::cout << "add_proxy " << proxy << " (this=" << this << ")" << std::endl;
        assert(proxies.count(proxy) == 0);
        proxies.insert(proxy);
    }

    void remove_proxy(Proxy<T>* proxy)
    {
        std::cout << "remove_proxy " << proxy << " (this=" << this << ")" << std::endl;
        assert(proxies.count(proxy) == 1);
        proxies.erase(proxy);
    }

    std::set<Proxy<T>*> proxies;
};


template<typename T>
struct Proxy
{
    Proxy() : proxiable(NULL)
    {
    }
    
    Proxy(Proxiable<T>& p) :
        proxiable(&p)
    {
        if (proxiable)
        {
            proxiable->add_proxy(this);
        }
    }

    ~Proxy()
    {
        if (proxiable)
        {
            proxiable->remove_proxy(this);
        }
    }

    Proxy(const Proxy& rhs) :
        proxiable(rhs.proxiable)
    {
        if (proxiable)
        {
            proxiable->add_proxy(this);
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
        swap(proxiable, rhs.proxiable);
    }

    Proxiable<T>* proxiable;
};


struct Item : Proxiable<Item>
{
    Item()
    {
        std::cout << "create " << this << std::endl;
    }
    
    ~Item()
    {
        std::cout << "destroy " << this << std::endl;
    }
};


void run()
{
    Item a, b;
    
    Proxy<Item> proxy;
    proxy.reset(a);
    proxy.reset(b);
    
    std::cout << "End of scope" << std::endl;
}


int main()
{
    run();
}
