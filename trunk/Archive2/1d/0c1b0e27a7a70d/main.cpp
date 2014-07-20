#include <set>
#include <iostream>
#include <iterator>
#include <utility>
#include <type_traits>
using namespace std;

namespace My{
    template <typename T>
    struct sfinae_true : std::true_type {};
    
    struct is_iterator_tester {
        template <typename T>
        static sfinae_true<typename std::iterator_traits<T>::iterator_category> test(int);
    
        template <typename>
        static std::false_type test(...);
    };
    
    template <typename T>
    struct is_iterator : decltype(is_iterator_tester::test<T>(0)) {};
    
    //base case
    template<typename T>
    static std::enable_if_t<!is_iterator<T>::value, string> to_string(const T& t) {
        return "basic ";
    }
    
    //specialization for string
    template <typename Char, typename Traits, typename Alloc>
    static string to_string(const std::basic_string<Char, Traits, Alloc>& s) {
        return (string)s;
    }
    
    //Problem line: how to write specialization for iterators of standard containers?
    template<typename T>
    static std::enable_if_t<is_iterator<T>::value, string> to_string(const T& s) {
        return "itor ";
    }
}

int main() {
  int i =  2;
  string str = "Hello";
  set<int> s;
  s.insert(i);
  cout << My::to_string(i) << ", " << str << ", "
       << My::to_string(s.begin()) << endl;   //no matching function for call to 'to_string(std::set<int>::iterator)'
}