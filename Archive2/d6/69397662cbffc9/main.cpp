#include <map>
#include <vector>
#include <iostream>
#include <functional>
#include <type_traits>

struct identity_t {
    template<typename T>
    constexpr inline T &&operator ()(T &&p_arg) const noexcept {
        return std::forward<T>(p_arg);
    }
};

struct one_t {
    template<typename T>
    constexpr inline int operator ()(T &&) const noexcept {
        return 1;
    }
};

template<template <typename Key, typename Value, typename Comp, typename...> class Map,
         typename Output,
         typename Updater,
         typename KeyComp,
         typename KeyProj,
         typename ValueProj>
struct histogram_t {
    Output    m_initial;
    Updater   m_update;
    KeyComp   m_kcomp;
    KeyProj   m_kproj;
    ValueProj m_vproj;
    
    histogram_t(Output p_initial, Updater p_update, KeyComp p_kcomp, KeyProj p_kproj, ValueProj p_vproj)
        : m_initial(std::move(p_initial))
        , m_update (std::move(p_update ))
        , m_kcomp  (std::move(p_kcomp  ))
        , m_kproj  (std::move(p_kproj  ))
        , m_vproj  (std::move(p_vproj  ))
    { }
};

template<template <typename Key, typename Value, typename Comp, typename...> class Map = std::map,
         typename Output    = int,
         typename Updater   = std::plus<>,
         typename KeyComp   = std::less<>,
         typename KeyProj   = identity_t,
         typename ValueProj = one_t>
histogram_t<Map, Output, Updater, KeyComp, KeyProj, ValueProj>
histogramed(Output p_initial = Output {}, Updater p_update = Updater {}, KeyComp p_kcomp = KeyComp {}, KeyProj p_kproj = KeyProj {}, ValueProj p_vproj = ValueProj {}) {
    return histogram_t<Map, Output, Updater, KeyComp, KeyProj, ValueProj>
        { std::move(p_initial), std::move(p_update), std::move(p_kcomp), std::move(p_kproj), std::move(p_vproj) };
}

template<typename Range,
         template <typename Key, typename Value, typename Comp, typename...> class Map,
         typename Output,
         typename Updater,
         typename KeyComp,
         typename KeyProj,
         typename ValueProj>
inline auto operator | (Range &&p_range, histogram_t<Map, Output, Updater, KeyComp, KeyProj, ValueProj> &&p_histogram) ->
    Map<std::decay_t<decltype(p_histogram.m_kproj(*std::begin(p_range)))>, std::decay_t<decltype(p_histogram.m_update(p_histogram.m_initial, p_histogram.m_vproj(*std::begin(p_range))))>, KeyComp>
{
    using key_t   = std::decay_t<decltype(p_histogram.m_kproj(*std::begin(p_range)))>;
    using value_t = std::decay_t<decltype(p_histogram.m_update(p_histogram.m_initial, p_histogram.m_vproj(*std::begin(p_range))))>;
    
    auto result = Map<key_t, value_t, KeyComp>(std::move(p_histogram.m_kcomp));
    
    for(auto &&element : p_range) {
        auto &&kv_pair = *result.emplace(p_histogram.m_kproj(element), p_histogram.m_initial).first;
        kv_pair.second = p_histogram.m_update(std::move(kv_pair.second), p_histogram.m_vproj(element));
    }
    
    return result;
}

int main() {
    auto foo = std::vector<int> { 1, 2, 3, 1, 1, 1, 1 };    
    auto histogram = foo | histogramed(1, std::plus<>(), std::less<>(), [](auto i) { return i + 1; }, [](auto i) { return i + 1; });
    
    for(auto &&pair : histogram) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}