#include <type_traits>

template<typename T, typename A, template<typename, typename> class Container, typename F>
auto Map (const Container<T, A>&c, F f) -> typename std::enable_if<!std::is_same<void, typename std::result_of<F (T)>::type>::value,
        Container<typename std::decay<typename std::result_of<F (T)>::type>::type, A>>::type
{
    Container<typename std::decay<typename std::result_of<F (T)>::type>::type, A> result;
    for (const auto& t : c)
        result.push_back(f(t));
    return result;
}

template<typename T, typename A, template<typename, typename> class Container, typename F>
auto Map (const Container<T, A>& c, F f) -> typename std::enable_if<std::is_same<void, typename std::result_of<F(T)>::type>::value>::type
{
    for (const auto& t : c)
        f(t);
}

#include <string>
#include <vector>
#include <list>
#include <deque>

struct StringVector : std::vector<std::string> {
    using std::vector<std::string>::vector;
};

struct StringList : std::list<std::string> {
    using std::list<std::string>::list;
};

struct StringDeque : std::deque<std::string> {
    using std::deque<std::string>::deque;
};

std::size_t GetId(const std::string& str) {
    using Hasher = std::hash<std::string>;
    Hasher hasher;
    return hasher(str);
}


#include <iostream>
#include <iterator>
#include <algorithm>

template<typename T>
void idof() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

template<typename T>
void idof(T&&) { idof<T>(); }

int main() {
    StringVector someVector{"Hello", "World"};
    StringList someList{"Goodbye", "Word"};
    StringDeque someDeque{"Array", "World"};

    const auto& vectorResult = Map(someVector, [] (const std::string& str) { return GetId(str); });
    const auto& listResult = Map(someList, [] (const std::string& str) { return GetId(str); });
    const auto& dequeResult = Map(someDeque, [] (const std::string& str) { return GetId(str); });

    idof<decltype(vectorResult)>();
    idof<decltype(listResult)>();
    idof<decltype(dequeResult)>();

    std::copy(begin(vectorResult), end(vectorResult), std::ostream_iterator<std::size_t>{std::cout, ", "});
    std::cout << '\n';
    std::copy(begin(listResult), end(listResult), std::ostream_iterator<std::size_t>{std::cout, ", "});
    std::cout << '\n';
    std::copy(begin(dequeResult), end(dequeResult), std::ostream_iterator<std::size_t>{std::cout, ", "});
    std::cout << '\n';
    
}
