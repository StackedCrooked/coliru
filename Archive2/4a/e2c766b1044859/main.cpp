#include <cstddef>
#include <utility>
#include <type_traits>

template <size_t Size>
class Field {
public:    
    Field(const char* c) {}
    template <size_t Offset, size_t Count>
    Field<Count> SubString(typename std::enable_if<(Size >= Offset + Count)>::type* = 0) const {
        return {};
    }
};

template <size_t Offset, size_t Count, typename T>
auto test_substring(T t, int) -> decltype(t.template SubString<Offset, Count>(), void(), std::true_type{});

template <size_t Offset, size_t Count, typename T>
auto test_substring(T t, ...) -> std::false_type;

int main()
{
    static_assert(std::is_same<decltype(test_substring<3, 4>(Field<5>("abcde"), 0)), std::false_type>::value, "This should not compile");
    static_assert(std::is_same<decltype(test_substring<3, 4>(Field<10>("abcde"), 0)), std::true_type>::value, "This should compile");
}
