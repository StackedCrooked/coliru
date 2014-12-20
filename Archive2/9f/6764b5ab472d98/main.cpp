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
    template <typename... FormalArguments, typename... ActualArguments>
    void invokeQueued(CSignal<FormalArguments...>& signal, ActualArguments&&... args)
    {
        invokeQueued(signal, std::index_sequence_for<ActualArguments...>{}, std::forward<ActualArguments>(args)...);
    }
    
    template <typename... FormalArguments, typename... ActualArguments, std::size_t... Is>
    void invokeQueued(CSignal<FormalArguments...>& signal, std::index_sequence<Is...>, ActualArguments&&... args)
    {
        m_queue.emplace_back(
          [signal, t = std::tuple<std::decay_t<FormalArguments>...>(std::forward<ActualArguments>(args)...)]
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
