#include <type_traits>

template<typename enable>
struct CopyAssignmentEnabler {};

template<>
struct CopyAssignmentEnabler<std::false_type>
{
    CopyAssignmentEnabler(const CopyAssignmentEnabler&) = default;
    CopyAssignmentEnabler(CopyAssignmentEnabler&&) = default;
    CopyAssignmentEnabler& operator=(const CopyAssignmentEnabler&) = delete;
    CopyAssignmentEnabler& operator=(CopyAssignmentEnabler&&) = default;
};

template<typename enable>
struct MoveAssignmentEnabler {};

template<>
struct MoveAssignmentEnabler<std::false_type>
{
    MoveAssignmentEnabler(const MoveAssignmentEnabler&) = default;
    MoveAssignmentEnabler(MoveAssignmentEnabler&&) = default;
    MoveAssignmentEnabler& operator=(const MoveAssignmentEnabler&) = default;
    MoveAssignmentEnabler& operator=(MoveAssignmentEnabler&&) = delete;
};

template<typename T>
struct Foobar : CopyAssignmentEnabler<typename std::is_nothrow_copy_constructible<T>::type>,
                MoveAssignmentEnabler<typename std::is_nothrow_move_constructible<T>::type>
{
    Foobar(T value) : x(value) {}

    T x;
};

struct value_type
{
    value_type() = default;
    value_type(int) {}
    value_type(value_type const&) noexcept(false) {}
    value_type& operator=(value_type const&) = default;
};

int main() {
    Foobar<value_type> foo(10);
    Foobar<value_type> bar(20);
    
    auto x = foo;

    foo = bar;
    foo.operator=(bar);

    return 0;
}