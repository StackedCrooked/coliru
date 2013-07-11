#include <cassert>
#include <iostream>
#include <string>
#include <memory>
#include <set>


template<typename T>
struct Proxy;


//std::string shorten(void* ptr)
//{
//    return "0x" + std::to_string(reinterpret_cast<long>(ptr) % 0x1000);
//}


template<typename T>
struct Proxiable
{
    void register_ref(Proxy<T>* ref)
    {
        //std::cout << "register: this=" << shorten(this) << ", ref=" << shorten(ref) << std::endl;
        assert(proxies.count(ref) == 0);
        proxies.insert(ref);
    }

    void unregister_ref(Proxy<T>* ref)
    {
        //std::cout << "unregister: this=" << shorten(this) << ", ref=" << shorten(ref) << std::endl;
        assert(proxies.count(ref) == 1);
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

    Proxy(T& p) : target(&p)
    {
        register_self();
    }

    ~Proxy()
    {
        unregister_self();
    }

    Proxy(const Proxy& rhs) : target(rhs.target)
    {
        register_self();
    }


#ifdef USE_COPY_SWAP

    Proxy& operator=(Proxy rhs)
    {
        this->swap(rhs);
        return *this;
    }

    void swap(Proxy<T>& rhs)
    {
        using std::swap;
        swap(target, rhs.target);
    }
    
    void reset(T& t)
    {
        Proxy<T>(t).swap(*this);
    }

#else

    Proxy& operator=(const Proxy& rhs)
    {
        if (this != &rhs)
        {
            unregister_self();
            this->target = rhs.target;
            register_self();
        }
        return *this;
    }
    
    void reset(T& t)
    {
        *this = Proxy<T>(t);
    }
    
#endif


private:
    void register_self()
    {
        if (target)
        {
            target->register_ref(this);
        }
    }
    void unregister_self()
    {
        if (target)
        {
            target->unregister_ref(this);
        }
    }

    T* target;
};


struct Resource : Proxiable<Resource>
{
};


int main()
{
    {
        Resource a, b;    
        Proxy<Resource> proxy;
        proxy.reset(a);
        proxy.reset(b);
    }
    std::cout << "Ok" << std::endl;
}
