#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
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


struct AbstractController
{
    std::string getTypeName() const
    {
        return Demangle(typeid(*this).name());
    }
    
    template<typename T>
    T& createChild()
    {
        // parent is passed to the constructor of the child
        auto ptr = std::make_shared<T>(*this);
        mChildren.push_back(ptr);
        return *ptr;
    }

    void destroy()
    {
        std::cout << getTypeName() << "::destroy " << std::endl;

        // perform cleanups first
        _finalize();

        _clearChildren();        
        
        _destroy();
    }

protected:
    AbstractController(AbstractController& inParent) :
        mParent(inParent)
    {
    }

    AbstractController& getParent()
    {
        return mParent;
    }

    void _clearChildren()
    {
        while (!mChildren.empty())
        {
            mChildren.pop_back();
        }
    }
    
    void _removeSelf()
    {
        getParent()._removeChild(*this);
    }

    void _removeChild(AbstractController& child)
    {
        std::cout << getTypeName() << "::_removeChild of type " << child.getTypeName() << std::endl;

        auto pred = [&](const std::shared_ptr<AbstractController>& rhs) {
            return &child == &*rhs;
        };
        mChildren.erase(std::remove_if(mChildren.begin(), mChildren.end(), pred), mChildren.end());
    }

    void _finalize()
    {
        std::cout << getTypeName() << "::finalize " << std::endl;

        // finalize children in reverse order of creation
        for (auto i = mChildren.rbegin(), e = mChildren.rend(); i != e ; ++i)
        {
            (*i)->_finalize();
        }

        do_finalize();
    }

private:
    virtual void do_finalize() = 0;
    virtual void _destroy() = 0;

    AbstractController& mParent;
    std::vector<std::shared_ptr<AbstractController>> mChildren;
};


struct RootController : AbstractController
{
    RootController() : AbstractController(*this)
    {
        std::cout << getTypeName() << "::RootController " << std::endl;
    }

    ~RootController()
    {
        std::cout << getTypeName() << "::~RootController " << std::endl;
    }

    void _destroy() override final
    {
        // root stays alive
    }

    void do_finalize() override final
    {
        std::cout << getTypeName() << "::do_finalize " << std::endl;
        // no special cleanup required

    }
};


struct Controller : AbstractController
{
    Controller(AbstractController& inParent) :
        AbstractController(inParent)
    {
    }


private:
    void _destroy() override final
    {
        _removeSelf();
    }

    void do_finalize() override /*nonfinal*/
    {
        //std::cout << getTypeName() << "::do_finalize is not implemented. Are you sure it does not require any cleanup?" << std::endl;
    }
};


struct IPv4Controller : Controller
{
    IPv4Controller(AbstractController& inParent) :
        Controller(inParent)
    {
        std::cout << getTypeName() << "::IPv4Controller " << std::endl;
    }

    ~IPv4Controller()
    {
        std::cout << getTypeName() << "::~IPv4Controller " << std::endl;
    }

    void setIP(const char*) {}
};


struct ICMPController : Controller
{
    ICMPController(AbstractController& inParent) :
        Controller(inParent)
    {
        std::cout << getTypeName() << "::ICMPController " << std::endl;
    }

    ~ICMPController()
    {
        std::cout << getTypeName() << "::~ICMPController " << std::endl;
    }

    void setDataSize(int) {}
};


struct HTTPController : Controller
{
    HTTPController(AbstractController& inParent) :
        Controller(inParent)
    {
        std::cout << getTypeName() << "::HTTPController " << std::endl;
    }

    ~HTTPController()
    {
        std::cout << getTypeName() << "::~HTTPController " << std::endl;
    }

    void do_finalize()
    {
        std::cout << "HTTPController::do_finalize: sending FIN" << std::endl;
    }

    void setLocalPort(int) {}
};


int main()
{
    RootController root;

    auto& ip = root.createChild<IPv4Controller>();
    ip.setIP("1.2.3.4");

    auto& icmp = ip.createChild<ICMPController>();
    icmp.setDataSize(123);

    auto& http = root.createChild<HTTPController>();
    http.setLocalPort(1234);

    std::cout << "<destroy_icmp>" << std::endl;
    icmp.destroy();
    std::cout << "</destroy_icmp>" << std::endl;

    root.destroy();
}
