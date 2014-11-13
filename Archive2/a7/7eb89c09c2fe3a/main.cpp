#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <cxxabi.h>


std::string Demangle(char const * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0: { return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get(); }
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("unexpected demangle status");
    }
}

template<typename T>
const std::string& GetTypeName()
{
    static const std::string fCached = Demangle(typeid(T).name());
    return fCached;
}


struct AbstractWidget : std::enable_shared_from_this<AbstractWidget>
{
    AbstractWidget(AbstractWidget* inParent) :
        mParent(inParent)
    {
    }
    
    virtual ~AbstractWidget()
    {
    }
    
    void destroy()
    {
        finalize();
        
        if (mParent)
        {
            mParent->destroyChild(shared_from_this());
        }
    }
    
    void finalize()
    {
        auto children = std::move(mChildren);
        std::reverse(children.begin(), children.end());
        for (auto& child_ptr : children)
        {
            child_ptr->finalize();
        }
        
        do_finalize();
    }
    
protected:
    void addChild(std::shared_ptr<AbstractWidget> child)
    {
        mChildren.push_back(child);
    }
    
private:
    void destroyChild(std::shared_ptr<AbstractWidget> child)
    {
        mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), child), mChildren.end());
    }
    
    virtual void do_finalize() = 0;
    AbstractWidget* mParent;
    std::vector<std::shared_ptr<AbstractWidget>> mChildren;
};


template<typename Derived> 
struct Widget : AbstractWidget
{
    Widget(AbstractWidget* inParent) : AbstractWidget(inParent) { std::cout << "Creating " << GetTypeName<Derived>() << std::endl; }
    ~Widget() { /*std::cout << "~" << GetTypeName<Derived>() << std::endl;*/ }
    
    template<typename T, typename ...Args>
    T& createChild(Args&& ...args)
    {
        auto& derived = dynamic_cast<Derived&>(*this);
        std::shared_ptr<T> ptr(new T(derived, std::forward<Args>(args)...));
        T& result = *ptr;
        addChild(ptr);
        return result;
    }
    
private:
    friend struct Root;
    
    Widget() : AbstractWidget(nullptr) {}
};


// The "root" widget
struct Root : Widget<Root>
{
    Root() : Widget() {}
    
    AbstractWidget& getParent() { return *this; }
    
    void do_finalize()
    {
        std::cout << GetTypeName<Root>() << "::do_finalize()" << std::endl;
    }
};


struct Interface : Widget<Interface>
{       
    static Interface& Create(Root& parent)
    {
        return parent.createChild<Interface>();
    }
    
    
private:
    friend class Widget<Root>;
    
    Interface(Root& parent) : 
        Widget(&parent)
    {
    }

    void do_finalize()
    {
        std::cout << GetTypeName<Interface>() << "::do_finalize()" << std::endl;
    }
};


struct Port : Widget<Port>
{       
    static Port& Create(Interface& parent, const std::string& ip)
    {
        return parent.createChild<Port>(ip);
    }
    
    
private:
    friend class Widget<Interface>;
    
    Port(Interface& parent, const std::string& ip) : 
        Widget<Port>(&parent),
        mIP(ip)
    {
    }

    void do_finalize()
    {
        std::cout << GetTypeName<Port>() << "::do_finalize()" << std::endl;
    }
    
    std::string mIP;
};


struct Ethernet : Widget<Ethernet>
{       
    static Ethernet& Create(Port& parent, const std::string& mac)
    {
        return parent.createChild<Ethernet>(mac);
    }
    
    
private:
    friend class Widget<Port>;
    
    Ethernet(Port& parent, const std::string& mac) : 
        Widget<Ethernet>(&parent),
        mMAC(mac)
    {
    }

    void do_finalize()
    {
        std::cout << GetTypeName<Ethernet>() << "::do_finalize()" << std::endl;
    }
    
    std::string mMAC;
};


struct IPv4 : Widget<IPv4>
{       
    static IPv4& Create(Port& parent, const std::string& ip)
    {
        return parent.createChild<IPv4>(ip);
    }
    
    
private:
    friend class Widget<Port>;
    
    IPv4(Port& parent, const std::string& ip) : 
        Widget<IPv4>(&parent),
        mIP(ip)
    {
    }

    void do_finalize()
    {
        std::cout << GetTypeName<IPv4>() << "::do_finalize()" << std::endl;
    }
    
    std::string mIP;
};


struct HTTP : Widget<HTTP>
{       
    static HTTP& Create(Port& parent)
    {
        return parent.createChild<HTTP>();
    }
    
private:
    friend class Widget<Port>;
    
    HTTP(Port& parent) : 
        Widget<HTTP>(&parent)
    {
    }

    void do_finalize()
    {
        std::cout << GetTypeName<HTTP>() << "::do_finalize" << std::endl;
    }
};


int main()
{
    Root root;
    auto& interface = root.createChild<Interface>();
    auto& port1 = interface.createChild<Port>("trunk-1-1");
    port1.createChild<Ethernet>("00-ff-23-00-00-01");
    port1.createChild<IPv4>("1.1.1.1");
    port1.createChild<HTTP>();
    port1.createChild<HTTP>();

    root.destroy();
}
