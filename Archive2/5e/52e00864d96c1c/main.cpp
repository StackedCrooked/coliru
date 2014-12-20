#include <vector>
#include <functional>
#include <deque>

typedef std::vector<int> state_type;

template <typename ...Arguments>
struct CSignal
{
    template <typename ...ActualArguments>
    void invoke(ActualArguments&&... args) const {}
};

template <typename T> struct identity_t { using type = T; };
template <typename T> using identity = typename identity_t<T>::type;

struct SomeClass
{
    template<typename ...Arguments>
    void invokeQueued(CSignal<Arguments...>& signal, const identity<Arguments>&... args)
    {
        m_queue.emplace_back([=](){signal.invoke(args...);});
    }

    std::deque<std::function<void (void)>> m_queue;
};

int main()
{
    CSignal<float> signal;
    int i = 0;
    SomeClass().invokeQueued(signal, i);
}
