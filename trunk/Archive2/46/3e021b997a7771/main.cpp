#include <boost/ptr_container/ptr_vector.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <cxxabi.h>
                                                                                                                                                                                                                                                                std::string Demangle(char const * name) { int st; char * const p = abi::__cxa_demangle(name, 0, 0, &st); switch (st) { case 0: { return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get(); } case -1: throw std::runtime_error("A memory allocation failure occurred."); case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules."); case -3: throw std::runtime_error("One of the arguments is invalid."); default: throw std::runtime_error("unexpected demangle status"); } } template<typename T>  std::string GetTypeName() { return Demangle(typeid(T).name()); } 

struct AbstractItem
{
    AbstractItem(AbstractItem* inParent) : mParent(inParent) { }

    virtual ~AbstractItem() { }

    void destroy()
    {
        finalize();

        if (mParent) { mParent->destroyChild(this); } }

    void finalize()
    {
        for (auto& child : mChildren)
        {
            child.finalize();
        }

        do_finalize();
    }

protected:
    void addChild(AbstractItem* child) { mChildren.push_back(child); }

private:
    void destroyChild(AbstractItem* child)
    {
        mChildren.erase(std::remove_if(mChildren.begin(), mChildren.end(), [child](AbstractItem& element) { return &element == child; }), mChildren.end());
    }

    virtual void do_finalize() {}

    AbstractItem* mParent;
    boost::ptr_vector<AbstractItem> mChildren;
};


template<typename Derived>
struct Item : AbstractItem
{
    Item(AbstractItem* inParent) : AbstractItem(inParent) { std::cout << "Creating " << GetTypeName<Derived>() << std::endl; }

    template<typename T, typename ...Args>
    T& createChild(Args&& ...args)
    {
        auto& derived = dynamic_cast<Derived&>(*this);
        auto ptr = new T(derived, std::forward<Args>(args)...);
        addChild(ptr);
        return *ptr;
    }

private:
    friend struct Root;
    Item() : AbstractItem(nullptr) {}
};


// The "root" widget
struct Root : Item<Root>
{
    Root() : Item() {}

    void do_finalize() { std::cout << GetTypeName<Root>() << "::do_finalize()" << std::endl; }
};


struct Interface : Item<Interface>
{
    static Interface& Create(Root& parent) { return parent.createChild<Interface>(); }

private:
    friend class Item<Root>;

    Interface(Root& parent) : Item(&parent) { }

    void do_finalize()
    {
        std::cout << GetTypeName<Interface>() << "::do_finalize()" << std::endl;
    }
};


struct Port : Item<Port>
{
    static Port& Create(Interface& parent, const std::string& ip) {  return parent.createChild<Port>(ip); }

private:
    friend class Item<Interface>;

    Port(Interface& parent, const std::string& ip) : Item<Port>(&parent), mIP(ip) { }

    void do_finalize() { std::cout << GetTypeName<Port>() << "::do_finalize()" << std::endl; }

    std::string mIP;
};


struct Ethernet : Item<Ethernet>
{
    static Ethernet& Create(Port& parent, const std::string& mac) { return parent.createChild<Ethernet>(mac); }

private:
    friend class Item<Port>;
    
    Ethernet(Port& parent, const std::string& mac) : Item<Ethernet>(&parent), mMAC(mac) { }

    void do_finalize() { std::cout << GetTypeName<Ethernet>() << "::do_finalize()" << std::endl; }

    std::string mMAC;
};


struct IPv4 : Item<IPv4>
{
    static IPv4& Create(Port& parent, const std::string& ip) { return parent.createChild<IPv4>(ip); }

private:
    friend class Item<Port>;
    
    IPv4(Port& parent, const std::string& ip) : Item<IPv4>(&parent), mIP(ip) { }
    
    void do_finalize() { std::cout << GetTypeName<IPv4>() << "::do_finalize()" << std::endl; }
    
    std::string mIP;
};


struct HTTP : Item<HTTP>
{
    static HTTP& Create(Port& parent) { return parent.createChild<HTTP>(); }
private:
    friend class Item<Port>;
    HTTP(Port& parent) : Item<HTTP>(&parent) { }
    void do_finalize() { std::cout << GetTypeName<HTTP>() << "::do_finalize" << std::endl; }
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
