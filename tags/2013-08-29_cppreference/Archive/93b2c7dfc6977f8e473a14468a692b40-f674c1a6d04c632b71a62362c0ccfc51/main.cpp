#include <iostream>
#include <memory>
#include <set>


struct Test
{
    struct Proxy;

    struct Proxiable
    {
        void add_proxy(Proxy* proxy)
        {
            std::cout << "add_proxy: " << proxy << std::endl;
            proxys.insert(proxy);
        }

        void remove_proxy(Proxy* proxy)
        {
            std::cout << "remove_proxy: " << proxy << std::endl;
            proxys.erase(proxy);
        }

        std::set<Proxy*> proxys;
    };

    struct Proxy
    {
        Proxy(Proxiable& p) :
            proxiable(&p)
        {
            proxiable->add_proxy(this);
        }

        ~Proxy()
        {
            proxiable->remove_proxy(this);
        }

        Proxy(const Proxy& rhs) :
            proxiable(rhs.proxiable)
        {
            proxiable->add_proxy(this);
        }

        Proxy& operator=(Proxy rhs) // copy swap
        {
            this->swap(rhs);
            return *this;
        }

        void swap(Proxy& rhs)
        {
            using std::swap;
            swap(proxiable, rhs.proxiable);
        }

        Proxiable* proxiable;
    };

    void run()
    {
        Proxiable obj;
        Proxy a(obj);
        Proxy b(obj);

        std::cout << "1" << std::endl;
        a = b;
        std::cout << "2" << std::endl;
    }
};


int main()
{
    Test().run();
}
