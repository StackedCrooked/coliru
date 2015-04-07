#include <iostream>
#include <memory>
#include <unordered_map>

struct proxy
{
    proxy(int id) : id{id} { }
    
    ~proxy() { std::cout << "Destroyed proxy with id " << id << std::endl; }
    
    int id;
};

template<typename T>
struct dual_shared_ptr
{
    dual_shared_ptr(std::weak_ptr<T> p)
        : wp{p}
    {
    }
    
    T* p = nullptr;
    
    std::weak_ptr<T> wp;
    
};

struct controller
{
    
    std::shared_ptr<proxy> get_child_object()
    {
        // Obtains the ID from the interactor...
        auto const id = 42;
        
        auto const it = registry.find(id);
        if (it == std::end(registry)) // Proxy for this ID retrieved for the first time...
        {
            return create_new_proxy(id);
        }
        
        auto& dp = registry.at(id);
        if (dp.p != nullptr)
        {
            // The controller owns the proxy...        
            release_owned_proxy(dp);
        }

        // Some other client owns the proxy...
        return dp.wp.lock();
    }
    
    void on_object_destroyed(int const id)
    {
        delete registry.at(id).p;
        registry.at(id).p = nullptr;
        registry.at(id).wp = std::weak_ptr<proxy>{};
    }
    
private:

    std::shared_ptr<proxy> create_new_proxy(int const id)
    {
        auto deleter = [this] (proxy* p) { on_proxy_unused(p); };
        auto ptr = std::shared_ptr<proxy>{new proxy{id}, deleter};
        registry.emplace(id, dual_shared_ptr<proxy>{ptr});
        return ptr;    
    }

    std::shared_ptr<proxy> release_owned_proxy(dual_shared_ptr<proxy>& dp)
    {
        // The controller owns the proxy...        
        auto deleter = [this] (proxy* p) { on_proxy_unused(p); };
        auto retp = std::shared_ptr<proxy>{dp.p, deleter};
        dp.wp = retp;
        dp.p = nullptr;
        return retp;
    }

    void on_proxy_unused(proxy* p)
    {
        registry.at(p->id).p = p;
        registry.at(p->id).wp = std::weak_ptr<proxy>{};
    }
    
private:
    
    std::unordered_map<int, dual_shared_ptr<proxy>> registry;
    
};

int main()
{   
    controller c;

    proxy* p = nullptr;
    
    auto id = 0;
    
    {
        std::cout << "Obtaining child1..." << std::endl;
        auto child1 = c.get_child_object();
        id = child1->id;

        std::cout << "ID = " << id << std::endl;
        
        {
            std::cout << "Moving to child2..." << std::endl;
            auto child2 = std::move(child1);
        
            p = child2.get();
        }
    }
    
    std::cout << "Obtaining child3..." << std::endl;
    auto child3 = c.get_child_object();
    
    std::cout << (child3.get() == p) << std::endl;
    
    std::cout << "Resetting child3..." << std::endl;
    child3.reset();
    
    c.on_object_destroyed(id);
}