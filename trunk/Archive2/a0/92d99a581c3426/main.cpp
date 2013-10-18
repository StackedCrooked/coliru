#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>


namespace Detail {

// Overload resolution:
// (1) decltype removes invalid candidates (SFINAE)
// (2) int/long parameter resolves remaining ambiguity

template<typename Container, typename T>
auto find(Container&& container, T&& val, int) -> decltype(container.find(val))
{
    return container.find(val);
}

using std::begin;
using std::end;
using std::find;

template<typename Container, typename T>
auto find(Container&& container, T&& val, long) -> decltype(find(begin(container), end(container), val))
{
    return find(begin(container), end(container), val);
}

} // namespace Detail


// Finds an item in a container.
// Uses `container.find(...)` if available, otherwise `std::find(...)` is used.
template<typename Container, typename T>
auto find(Container&& container, T&& val)
{
    std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
    return Detail::find(container, val, int{}); // prefer int overload in case of ambiguity
}



namespace user
{
    struct item
    {
        int i;
        item(int i) : i(i) {}
        
        friend bool operator<(const item& lhs, const item& rhs)
        {
            return lhs.i < rhs.i;
        }   
        
        friend bool operator==(const item& lhs, const item& rhs)
        {
            return lhs.i == rhs.i;
        }   
        
        friend std::ostream& operator<<(std::ostream& os, const item& i)
        {
            return os << "item(" << i.i << ')';
        }
    };
    
    template<int N>
    const item* find(item(&items)[N], const item& item)
    {
        std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
        using std::find;
        using std::begin;
        using std::end;
        return find(begin(items), end(items), item);
    }
}


int main()
{    
    std::set<std::string> wordSet = { "abc", "test", "123" };
    std::cout << *find(wordSet, "test") << std::endl;
        
    std::vector<std::string> wordVector = { "abc", "test", "123" };
    std::cout << *find(wordVector, "test") << std::endl;
    
    std::string wordArray[] = { "abc", "test", "123" };
    std::cout << *find(wordArray, "test") << std::endl;
    
    int intArray[] = { 1, 2, 3 };
    std::cout << *find(intArray, 2) << std::endl;
    
    auto wordInitializerList = { "abc", "test", "123" };
    std::cout << *find(wordInitializerList, "test") << std::endl;
    
    user::item userItemArray[] = { user::item{1}, user::item{2}, user::item{3} };
    std::cout << *user::find(userItemArray, userItemArray[1]) << std::endl;
}
