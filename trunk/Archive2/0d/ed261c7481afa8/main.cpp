#include <memory>
#include <type_traits>
 
namespace MyStd {
    template <class ...T> struct common_type;
 
    template <class T>
    struct common_type<T> {
        typedef std::decay_t<T> type;
    };
 
    template <class T, class U>
    struct common_type<T, U> {
        typedef std::decay_t<decltype(true ? std::declval<std::decay_t<T>>() : std::declval<std::decay_t<U>>() )> type;
    };
}
 
int main() {
 
    MyStd::common_type<std::unique_ptr<int> & , std::unique_ptr<int> >::type tt = std::make_unique<int>(33);
 
    static_assert(std::is_same<MyStd::common_type<int, double>::type, double>(), "pass");
    static_assert(std::is_same<MyStd::common_type<int, double&>::type, double>(), "pass");
    static_assert(std::is_same<MyStd::common_type<int, double&&>::type, double>(), "pass");
    static_assert(std::is_same<MyStd::common_type<int&, int>::type, int>(), "pass");
 
    static_assert(std::is_same<MyStd::common_type<std::unique_ptr<int> & , std::unique_ptr<int> >::type,
                  std::unique_ptr<int>>(), "pass");
 
 
    static_assert(std::is_same<MyStd::common_type<int, int&>::type,
                                 std::common_type<int&, int&>::type>(), "pass");
 
}