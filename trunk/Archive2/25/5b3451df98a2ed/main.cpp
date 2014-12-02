#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <cstdint>

class IoC
{
private:
    struct IRegistredBase {
        virtual void Construct(char*) = 0;
        virtual bool GetIsSingleton() const = 0;
        virtual ~IRegistredBase(){};
    };

public:
    template <class ImplType>
    class Registred : public IRegistredBase
    {
        friend class IoC;

    private:
        IoC& m_ioc;
        bool m_singleton = false;
        std::function<ImplType*(char*)> m_constructor;

        ImplType Construct()
        {
            ImplType obj;
            return *m_constructor(&obj);
        }

    public:
        void Construct(char* ptr) override
        {
            auto obj = m_constructor(ptr);
            (void)obj;
        }

        bool GetIsSingleton() const override
        {
            return m_singleton;
        }

        Registred(IoC& ioc)
            : m_ioc(ioc)
            , m_constructor([](char* ptr) { return new (ptr) ImplType{}; })
        {
        }

        template <class... Args>
        Registred& Constructor(Args&&... args)
        {
            m_constructor = [&](char* ptr) { return new (ptr) ImplType{std::forward<Args>(args)...}; };
            return *this;
        }

        Registred& Singleton()
        {
            m_singleton = true;
            return *this;
        }
    };

    template <class InterfaceType>
    struct deleter {
        bool m_singleton;
        explicit deleter(bool singleton)
            : m_singleton(singleton){};
        void operator()(InterfaceType* ptr) const
        {
            if (!m_singleton) {
                ptr->~InterfaceType();
                delete[](char*)(ptr);
            }
        }
        template <class U>
        void operator()(U*) const = delete;
    };

    template <class InterfaceType>
    std::unique_ptr<InterfaceType, deleter<InterfaceType>> Get()
    {
        auto result = m_classMap.find(typeid(InterfaceType).name());
        if (result != m_classMap.end()) {
            auto buffer = new char[result->second.TypeSize];
            result->second.HandlerInstance->Construct(buffer);
            auto singleton = result->second.HandlerInstance->GetIsSingleton();
            InterfaceType* obj = reinterpret_cast<InterfaceType*>(buffer);
            return std::unique_ptr<InterfaceType, deleter<InterfaceType>>(obj, deleter<InterfaceType>(singleton));
        }
        throw std::exception();
    }

    struct HandlerInfo {
        size_t TypeSize;
        std::unique_ptr<IRegistredBase> HandlerInstance;
        std::string ImplTypeName;
        HandlerInfo(size_t size, std::unique_ptr<IRegistredBase> instance, std::string name)
            : TypeSize(size)
            , HandlerInstance(std::move(instance))
            , ImplTypeName(std::move(name))
        {
        }
        template <class ImplType>
        static HandlerInfo MakeHandlerInfo(IoC& ioc)
        {
            return HandlerInfo{sizeof(ImplType), std::make_unique<Registred<ImplType>>(ioc), typeid(ImplType).name()};
        }
    };

    std::map<std::string, HandlerInfo> m_classMap;
    std::map<uintptr_t, size_t> m_refCounters;

    template <class InterfaceType, class ImplType>
    Registred<ImplType>& Register()
    {
        auto result = m_classMap.emplace(
            std::make_pair(typeid(InterfaceType).name(), HandlerInfo::MakeHandlerInfo<ImplType>(*this)));

        return *static_cast<Registred<ImplType>*>(result.first->second.HandlerInstance.get());
    }
};

struct IFace {
    virtual void SomeMethod() = 0;
    virtual ~IFace(){};
};

class Face : public IFace
{
public:
    void SomeMethod() override
    {
        std::cout << "SomeMethod" << std::endl;
    }
};

class Muzzle : public IFace
{
public:
    Muzzle()
    {
        throw std::runtime_error("NotImplemented");
    }
    explicit Muzzle(std::string name)
        : m_name(std::move(name))
    {
    }
    void SomeMethod() override
    {
        std::cout << "Muzzle name: " << m_name << std::endl;
    }

private:
    std::string m_name;
};

void f1(IoC& ioc)
{
    ioc.Get<IFace>()->SomeMethod();
}

void f2(IoC& ioc)
{
    ioc.Get<IFace>()->SomeMethod();
}

int main(int argc, const char* argv[])
{

    IoC ioc1;
    IoC ioc2;

    ioc1.Register<IFace, Face>();
    ioc2.Register<IFace, Muzzle>().Constructor("The Dog");

    f1(ioc1);
    f2(ioc2);


    return 0;
}
