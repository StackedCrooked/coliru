#include <array>
#include <iostream>
#include <string>
#include <typeindex>
#include <vector>


struct eth_t {};
struct ip4_t {}; constexpr ip4_t ip4 {};
struct tcp_t {}; constexpr tcp_t tcp {};

struct Stack
{
    std::uint16_t mIndex = 0;


    Stack();

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    template<typename T>
    void upgrade(T t)
    {
        base().upgrade(t);
    }

    void print()
    {
        base().print();
    }


    struct Base;

    const Base& base() const { return static_cast<const Base&>(static_cast<const NonPolymporphicBase&>(mStorage)); }
    Base& base() { return static_cast<Base&>(static_cast<NonPolymporphicBase&>(mStorage)); }

    bool valid() const { return mStorage.mData[0] != 0; }

    const void* data() const { return static_cast<const void*>(mStorage.data()); }
    void* data() { return static_cast<void*>(mStorage.data()); }


    // This helper base allows us to reinterpret from
    // Storage* to Base* without triggering aliasing warnings.
    struct NonPolymporphicBase {};

    struct Base : NonPolymporphicBase
    {
        virtual ~Base() {}

        template<typename T>
        void upgrade(T t)
        {
            do_upgrade(typeid(t));
        }

        void print()
        {
            do_print();
        }

        void destroy()
        {
            this->~Base();
        }

        template<typename U>
        void reconstruct(U u)
        {
            destroy();
            new (getAddress()) U(std::move(u));
        }

        void* getAddress()
        {
            NonPolymporphicBase& self = *this;
            return &self;
        }

        virtual void do_upgrade(std::type_index ti) = 0;
        virtual void do_print() = 0;
    };

    template<typename ...T>
    struct Impl;

    struct Storage : NonPolymporphicBase
    {
        const void* data() const { return mData.data(); }
        void* data() { return mData.data(); }
        void unset() { mData[0] = 0; }
        std::array<long, 40> mData;
    };

    static_assert(std::is_pod<Storage>::value, "");
    Storage mStorage;

};


template<>
struct Stack::Impl<eth_t> : Stack::Base
{
    virtual void do_upgrade(std::type_index ti) override;

    void do_print() override
    {
        std::cout << __FILE__ << ":" << __LINE__ << ": " << " MAC=" << mac << std::endl;
    }

    std::string mac = "00-ff-00-00-00-23";
};


template<>
struct Stack::Impl<ip4_t, eth_t> : Stack::Impl<eth_t>
{
    Impl(Stack::Impl<eth_t> rhs) : Stack::Impl<eth_t>(std::move(rhs))
    {
    }
    void do_upgrade(std::type_index ti) override;

    void do_print() override
    {
        std::cout << "MAC=" << mac << " IP=" << ip << std::endl;
    }

    std::string ip = "1.1.1.1";
};


template<>
struct Stack::Impl<tcp_t, ip4_t, eth_t> : Stack::Impl<ip4_t, eth_t>
{
    Impl(Stack::Impl<ip4_t, eth_t> rhs) : Stack::Impl<ip4_t, eth_t>(std::move(rhs))
    {
    }
    void do_upgrade(std::type_index )
    {
    }

    void do_print()
    {
        std::cout << "MAC=" << mac << " IP=" << ip << " local_port=" << local_port << std::endl;
    }

    std::string local_port = "234";
};



void Stack::Impl<eth_t>::do_upgrade(std::type_index ti)
{
    if (ti == typeid(ip4_t))
    {
        using new_type = Stack::Impl<ip4_t, eth_t>;
        static_assert(sizeof(new_type) <= sizeof(Storage), "");
        reconstruct(Stack::Impl<ip4_t, eth_t>(*this));
        return;
    }

}



void Stack::Impl<ip4_t, eth_t>::do_upgrade(std::type_index ti)
{
    if (ti == typeid(tcp_t))
    {
        reconstruct(Stack::Impl<tcp_t, ip4_t, eth_t>(*this));
    }
}


Stack::Stack()
{
    new (mStorage.data()) Impl<eth_t>();
}



template<typename T>
void AddProtocol(Stack& stack, T t)
{
    stack.upgrade(t);
    std::cout <<  __FILE__ << ":" << __LINE__ << ": self.new_type= " << typeid(stack.base()).name() << std::endl;
    stack.print();
}



int main()
{
    Stack client;

    AddProtocol(client, ip4);
    AddProtocol(client, tcp);
}
