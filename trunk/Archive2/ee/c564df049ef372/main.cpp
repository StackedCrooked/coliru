#include <memory>
#include <iostream>
#include <vector>

struct Ethernet
{
    friend void Pop(Ethernet& eth)
    {
        std::cout << "pop eth\n";
    }
    friend void Push(Ethernet&)
    {
        std::cout << "push eth\n";
    }
};


struct IPv4
{
    friend void Pop(IPv4& ip4)
    {
        std::cout << "pop ip4\n";
    }
    friend void Push(IPv4&)
    {
        std::cout << "push ip4 \n";
    }
};


struct TCP
{
    friend  void Pop(TCP&)
    {
        std::cout << "pop tcp\n";
    }
    friend void Push(TCP&)
    {
        std::cout << "push tcp\n";
    }
};


struct Session
{
    template<typename T>
    explicit Session(T t) : mImpl(new Impl<T>(std::move(t))) {}

    void pop() { mImpl->pop_(); }
    void push() { mImpl->push_(); }

private:
    struct Base
    {
        virtual void pop_() = 0;
        virtual void push_() = 0;
    };

    template<typename T>
    struct Impl final : Base
    {
        Impl(T t) : t(std::move(t)) {}
        void pop_() { Pop(t); }
        void push_() { Push(t); }
        T t;
    };

    std::shared_ptr<Base> mImpl;
};


int main()
{

    std::vector<Session> sessions;
    sessions.emplace_back(Ethernet{});
    sessions.emplace_back(IPv4{});
    sessions.emplace_back(TCP{});

    for (auto&& session : sessions)
    {
        session.pop();
        session.push();
    }
}
