#include <vector>
#include <functional>
#include <deque>
#include <utility>
#include <type_traits>

typedef std::vector<int> state_type;

template <typename ...Arguments>
struct CSignal
{
    template <typename ...ActualArguments>
    void invoke(ActualArguments&&... args) const {}
};

struct SomeClass
{
    template <typename... Arguments, typename... Args>
    void invokeQueued(CSignal<Arguments...>& signal, Args&&... args)
    {
        invokeQueued(signal, std::index_sequence_for<Args...>{}, std::forward<Args>(args)...);
    }
    
    template <typename... Arguments, typename... Args, std::size_t... Is>
    void invokeQueued(CSignal<Arguments...>& signal, std::index_sequence<Is...>, Args&&... args)
    {
        m_queue.emplace_back(
          [signal, t = std::tuple<std::decay_t<Arguments>...>(std::forward<Args>(args)...)]
          (){signal.invoke(std::get<Is>(t)...);});
    }

    std::deque<std::function<void (void)>> m_queue;
};

int main()
{
    CSignal<float> signal;
    int i = 0;
    SomeClass().invokeQueued(signal, i);
}
