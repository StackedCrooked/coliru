#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <boost/signals2/signal.hpp>

struct object
{
    object(std::string name) : name(std::move(name)) { }
    
    ~object() 
    {
        std::cout << "Destroying object " << name << "..." << std::endl;
        
        on_destruction(); 

        std::cout << name << " says bye!" << std::endl;
    }
    
    std::string name;

    std::vector<std::shared_ptr<object>> children;
        
    boost::signals2::signal<void()> on_destruction;
};

template<typename T>
struct exported_shared_ptr
{
    
    exported_shared_ptr(std::shared_ptr<T> sp)
        : sp{std::move(sp)}
        , wp{this->sp}
        , p{this->sp.get()}
    {
    }
    
    int add_owner()
    {
        if (sp == nullptr)
        {
            sp = wp.lock();
        }
        
        ++count;
        
        return count;
    }
    
    int remove_owner()
    {
        auto new_count = --count;

        if (new_count == 0)
        {
            sp.reset();
        }
        
        return new_count;
    }
    
    std::shared_ptr<T> sp;
    
    std::weak_ptr<T> wp;
    
    T* p = nullptr;

    int count = 0;

};

struct interactor
{
    
    int create_object(std::string name)
    {
        auto o = std::make_shared<object>(std::move(name));
                
        return share_object(o);
    }
    
    void add_object_child(int const parent_id, int const child_id)
    {
        auto& parent = objects.at(parent_id);
        auto& child = objects.at(child_id);
        
        parent.p->children.push_back(child.sp);
    }
  
    int get_object_child(int const object_id, int const index)
    {
        auto obj = objects.at(object_id).sp->children[index];

        return share_object(obj);
    }
  
    void release_ownership(int const id)
    {
        std::cout << "Interactor decreasing count for ID = " << id << "...\n";
        auto const new_count = objects.at(id).remove_owner();
        std::cout << "Ownership count is now " << new_count << "\n";
    }
    
    boost::signals2::signal<void(int)> on_object_destroyed;
    
private:

    int share_object(std::shared_ptr<object> obj)
    {
        auto it = std::find_if(std::begin(objects), 
                               std::end(objects), 
                               [&obj] (decltype(objects)::value_type const& entry)
        {
            return entry.second.p == obj.get();
        });
        
        if (it == std::end(objects))
        {
            auto const id = objects.size() + 1;
            std::cout << "Interactor registering object with ID = " << id << "...\n";
            auto raw_obj = obj.get();
            obj->on_destruction.connect([this, raw_obj] { on_destruction(*raw_obj); });
            it = objects.emplace(id, exported_shared_ptr<object>{obj}).first;
        }
    
        std::cout << "Interactor increasing count for ID = " << it->first << "...\n";
        auto new_count = it->second.add_owner();
        std::cout << "Ownership count for ID = " << it->first << " is now " << new_count << "\n";  
                        
        return it->first;        
    }

    void on_destruction(object& o)
    {
        std::cout << "Interactor becoming aware of " << o.name << "'s death...\n";
    
        auto it = std::find_if(std::begin(objects), 
                               std::end(objects), 
                               [&o] (decltype(objects)::value_type const& entry)
        {
            return entry.second.p == &o;
        });
        
        std::cout << "Interactor firing event for object " << it->first << " death...\n";
        on_object_destroyed(it->first);
        
        std::cout << "Interactor unregistering object " << it->first << "...\n";
        objects.erase(it);
    }

private:
    
    std::unordered_map<int, exported_shared_ptr<object>> objects;
    
};

struct proxy
{
    proxy(int id) : id{id} 
    { 
        std::cout << "Constructing proxy with id " << id << std::endl;    
    }
    
    ~proxy() 
    { 
        std::cout << "Destroying proxy with id " << id << std::endl; 
    }
    
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
    
    controller(interactor& i) : the_interactor{i} 
    {
        the_interactor.on_object_destroyed.connect([this] (int const id)
        {
            on_object_destroyed(id);
        });
    }
    
    std::shared_ptr<proxy> create_object(std::string name)
    {
        auto const id = the_interactor.create_object(std::move(name));
        
        return get_or_create_proxy(id);
    }
    
    void add_object_child(proxy& p, std::shared_ptr<proxy> child)
    {
        the_interactor.add_object_child(p.id, child->id);
    }
    
    std::shared_ptr<proxy> get_object_child(proxy& p, int const index)
    {
        // Obtains the ID from the interactor...
        auto const id = the_interactor.get_object_child(p.id, index);
        
        return get_or_create_proxy(id);
    }
    
private:

    std::shared_ptr<proxy> get_or_create_proxy(int const id)
    {
        auto const it = registry.find(id);
        if (it == std::end(registry))
        {
            std::cout << "Proxy for ID " << id << " asked first time...\n";
            return create_new_proxy(id);
        }
        
        auto& dp = registry.at(id);
        if (dp.p != nullptr)
        {
            std::cout << "Controller owns proxy for ID " << id << "...\n";
            return release_owned_proxy(dp);
        }
        
        auto ptr = dp.wp.lock();
        
        std::cout << "Telling the interactor we already have an owning pointer...\n";
        the_interactor.release_ownership(id);

        // Some other client owns the proxy...
        return ptr;        
    }

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
        std::cout << "Client-side, no one owns object " << p->id << "...\n";
        
        registry.at(p->id).p = p;
        registry.at(p->id).wp = std::weak_ptr<proxy>{};
        the_interactor.release_ownership(p->id);
    }
    
    void on_object_destroyed(int const id)
    {
        std::cout << "Object " << id << " destroyed, controller unregistering...\n";
        
        try
        {
            delete registry.at(id).p;
            registry.at(id).p = nullptr;
            registry.at(id).wp = std::weak_ptr<proxy>{};
        }
        catch (std::exception const&)
        {
        }
    }    
    
private:
    
    std::unordered_map<int, dual_shared_ptr<proxy>> registry;
  
    interactor& the_interactor;
  
};

int main()
{   
    interactor i;
    
    controller c{i};

    {
        std::cout << "Creating obj1..." << std::endl;
        auto obj1 = c.create_object("COOL OBJ1");
    
        std::cout << "Creating obj2..." << std::endl;
        auto obj2 = c.create_object("COOL OBJ2");
    
        std::cout << "Adding obj1 as child of obj2..." << std::endl;
        c.add_object_child(*obj1, obj2);
        
        proxy* p = obj2.get();
        
        {    
            auto obj2_last_pointer = std::move(obj2);
            
            std::cout << "Retrieving first child of obj1..." << std::endl;        
            auto child = c.get_object_child(*obj1, 0);
            
            std::cout << "Releasing last obj2 proxy pointer..." << std::endl;                
        }
        
        std::cout << "Retrieving first child of obj1 again..." << std::endl;        
        auto child = c.get_object_child(*obj1, 0);
    
        std::cout << "Old == New: " << (child.get() == p) << std::endl; 
    
        std::cout << "Resetting obj1..." << std::endl;
        obj1.reset();
      
        std::cout << "All right, we're done here!" << std::endl;
    }
    
    std::cout << "Destroying interactor and controller..." << std::endl;    
}