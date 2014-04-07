#include <type_traits>
#include <iterator>

template<typename T>
class Slice {
    T* backing_array;
    std::size_t slice_length;
    std::size_t slice_capacity;
    static constexpr bool is_const = std::is_const<T>::value;
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = typename std::add_const<T>::type*;
    using reference = T&;
    using const_reference = typename std::add_const<T>::type&;
    using rvalue_reference = typename std::conditional<is_const, const_reference, T&&>::type;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using move_iterator = typename std::conditional<is_const, iterator, std::move_iterator<iterator>>::type;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_move_iterator = typename std::conditional<is_const, reverse_iterator, std::reverse_iterator<move_iterator>>::type;

public:
    constexpr Slice() noexcept : backing_array(nullptr), slice_length(0), slice_capacity(0) {}
    constexpr Slice(std::nullptr_t) noexcept : Slice() {}
    constexpr Slice(pointer array, size_type length, size_type capacity) noexcept : backing_array(array), slice_length(length), slice_capacity(length) {}
    constexpr Slice(pointer array, size_type length) noexcept : Slice(array, length, length) {}
    template<size_type Capacity>
    constexpr Slice(T(&array)[Capacity], size_type length) noexcept : Slice(array, length, Capacity) {}
    template<size_type Capacity>
    constexpr Slice(T(&array)[Capacity]) noexcept : Slice(array, Capacity, Capacity) {}
    constexpr Slice(const Slice&) noexcept = default;
    Slice(Slice&& other) noexcept : backing_array(other.backing_array), slice_length(other.slice_length), slice_capacity(other.slice_capacity) {
        other.backing_array = nullptr;
        other.slice_length = other.slice_capacity = 0;
    }

#if __cplusplus > 201103L
    constexpr pointer data() noexcept { return backing_array; }

    constexpr iterator begin() noexcept { return iterator(backing_array); }

    constexpr iterator end() noexcept { return iterator(backing_array + size()); }
#else
    pointer data() noexcept { return backing_array; }

    iterator begin() noexcept { return iterator(backing_array); }

    iterator end() noexcept { return iterator(backing_array + size()); }
#endif

    constexpr const_iterator begin() const noexcept { return const_iterator(backing_array); }
    constexpr const_iterator cbegin() const noexcept { return const_iterator(backing_array); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    move_iterator mbegin() { return move_iterator(begin()); }
    reverse_move_iterator rmbegin() { return reverse_move_iterator(mend()); }

    constexpr const_iterator end() const noexcept { return const_iterator(backing_array + size()); }
    constexpr const_iterator cend() const noexcept { return const_iterator(backing_array + size()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }
    move_iterator mend() { return move_iterator(end()); }
    reverse_move_iterator rmend() { return reverse_move_iterator(mbegin()); }

    constexpr size_type size() const noexcept { return slice_length; }

#if __cplusplus > 201103L
    constexpr reference operator[](size_type index) & noexcept {
        return data()[index];
    }

    constexpr rvalue_reference operator[](size_type index) && noexcept {
        return std::move(data()[index]);
    }
#else
    reference operator[](size_type index) & noexcept {
        return data()[index];
    }

    rvalue_reference operator[](size_type index) && noexcept {
        return std::move(data()[index]);
    }
#endif

    constexpr const_reference operator[](size_type index) const & noexcept {
        return data()[index];
    }
};

#include <iostream>

template<typename T>
void identify() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
template<typename T>
void identify(T&&) { identify<T>(); }

int main() {
    char data[] = "Hello";
    Slice<const char> s(data);
    std::cout << __cplusplus << '\n';
    identify<decltype(*s.begin())>();
    identify<decltype(*s.cbegin())>();
    identify<decltype(*s.rbegin())>();
    identify<decltype(*s.crbegin())>();
    identify<decltype(*s.mbegin())>();
    identify<decltype(*s.end())>();
    identify<decltype(*s.cend())>();
    identify<decltype(*s.rend())>();
    identify<decltype(*s.crend())>();
    identify<decltype(*s.mend())>();
    identify<decltype(s.size())>();
}