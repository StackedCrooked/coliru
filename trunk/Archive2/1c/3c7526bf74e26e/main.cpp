#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <numeric>
#include <ratio>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <typename T, typename U = T>
inline T exchange(T& obj, U&& value)
  noexcept(std::is_nothrow_move_constructible<T>() &&
           std::is_nothrow_assignable<T&,U&&>()) {
  auto tmp = std::move(obj);
  obj = std::forward<U>(value);
  return tmp;
}

namespace iterator_detail {
template <typename T>
auto is_iterator_test(int) -> decltype((void)(typename std::iterator_traits<T>::iterator_category()), std::true_type());
template <typename>
auto is_iterator_test(...) -> std::false_type;

template <typename Iterator>
using IteratorValueType = typename std::iterator_traits<Iterator>::value_type;

template <typename Iterator>
using CanMoveElements =
std::integral_constant<bool,
  (std::is_nothrow_move_constructible<IteratorValueType<Iterator> >::value &&
   std::is_nothrow_move_assignable<IteratorValueType<Iterator> >::value) ||
  !(std::is_copy_constructible<IteratorValueType<Iterator> >::value &&
    std::is_copy_assignable<IteratorValueType<Iterator> >::value)>;
} // namespace iterator_detail
using iterator_detail::IteratorValueType;

template <typename T>
using IsIterator = decltype(iterator_detail::is_iterator_test<T>(0));

template <typename Iterator>
auto maybe_move_iterator(Iterator i) ->
  typename std::enable_if<
    IsIterator<Iterator>::value &&
      iterator_detail::CanMoveElements<Iterator>::value,
    decltype(std::make_move_iterator(i))
  >::type {
  return std::make_move_iterator(i);
}

template <typename Iterator>
auto maybe_move_iterator(Iterator i) ->
  typename std::enable_if<
    IsIterator<Iterator>::value &&
      !iterator_detail::CanMoveElements<Iterator>::value,
    Iterator
  >::type {
  return i;
}

template <typename T>
struct is_relocatable {
  using type = typename std::is_trivially_move_constructible<T>::type;
};
template <typename T>
using is_relocatable_t = typename is_relocatable<T>::type;

template <typename T, bool override_relocatable_check = false>
class reallocator {
  static constexpr bool DEBUG = true;
public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = T const*;
  using reference = typename std::add_lvalue_reference<T>::type;
  using const_reference = typename std::add_lvalue_reference<T const>::type;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using propagate_on_container_move_assignment = std::true_type;

  template <typename U>
  struct rebind {
    using other = reallocator<U, override_relocatable_check>;
  };

  constexpr reallocator() noexcept = default;
  template <typename U, bool B>
  constexpr reallocator(const reallocator<U, B>&) noexcept {}

  pointer address(reference r) const noexcept {
    return std::addressof(r);
  }
  const_pointer address(const_reference r) const noexcept {
    return std::addressof(r);
  }

  size_type max() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  pointer allocate(size_type n, const void* = nullptr) {
    if (DEBUG) {
      std::cout << "reallocator::allocate(" << n << "): ";
    }
    if (auto ptr = std::malloc(n * sizeof(T))) {
      if (DEBUG) {
        std::cout << ptr << '\n';
      }
      return static_cast<pointer>(ptr);
    }
    if (DEBUG) {
      std::cout << "(failed)" << std::endl;
    }
    throw std::bad_alloc();
  }

  void deallocate(pointer ptr, size_type n) noexcept {
    if (DEBUG) {
      std::cout << "reallocator::deallocate(" << ptr << ", " << n << ")\n";
    }
    std::free(ptr);
  }

  pointer relocate(pointer ptr, size_type old_capacity, size_type new_capacity, size_type /* size */) {
    static_assert(override_relocatable_check || is_relocatable_t<value_type>(),
                  "reallocator requires a relocatable value_type");

    if (DEBUG) {
      std::cout << "reallocator::relocate(" << ptr << ", " << old_capacity << ", " << new_capacity << "): ";
    }
    if (auto new_ptr = std::realloc(ptr, new_capacity * sizeof(T))) {
      if (DEBUG) {
        std::cout << new_ptr;
        if (new_ptr == ptr) {
          std::cout << " (inplace)\n";
        } else {
          std::cout << " (relocated)\n";
        }
      }
      return static_cast<pointer>(new_ptr);
    }
    if (DEBUG) {
      std::cout << "(failed)" << std::endl;
    }
    throw std::bad_alloc();
  }

  template <typename U, typename... Args >
  void construct(U* p, Args&&... args) {
    ::new(static_cast<void*>(p)) U(std::forward<Args>(args)...);
  }

  template <typename U>
  void destroy(U* p) {
    p->~U();
  }
};

template <typename T, bool TB, typename U, bool UB>
inline bool operator == (const reallocator<T, TB>&, const reallocator<U, UB>&) noexcept {
  return true;
}
template <typename T, bool TB, typename U, bool UB>
inline bool operator != (const reallocator<T, TB>&, const reallocator<U, UB>&) noexcept {
  return false;
}

template <typename T>
struct reallocator_traits : public std::allocator_traits<T> {
  using typename std::allocator_traits<T>::allocator_type;
  using typename std::allocator_traits<T>::value_type;
  using typename std::allocator_traits<T>::pointer;
  using typename std::allocator_traits<T>::size_type;

private:
  template <typename U = allocator_type>
  static auto has_resize_test(int) ->
    decltype((void)(std::declval<bool&>() =
               std::declval<U&>().resize(
                 std::declval<pointer>(),
                 std::declval<size_type>(),
                 std::declval<size_type>())),
             std::true_type());
  static auto has_resize_test(...) -> std::false_type;

  template <typename U = allocator_type>
  static auto has_relocate_test(int) ->
    decltype((void)(std::declval<pointer&>() =
               std::declval<U&>().relocate(
                 std::declval<pointer>(),
                 std::declval<size_type>(),
                 std::declval<size_type>(),
                 std::declval<size_type>())),
             std::true_type());
  static auto has_relocate_test(...) -> std::false_type;

  template <typename U = allocator_type>
  static auto has_block_align_test(int) ->
    decltype((void)(std::declval<size_type&>() =
               std::declval<U&>().block_align(
                 std::declval<size_type>())),
             std::true_type());
  static auto has_block_align_test(...) -> std::false_type;

public:
  using has_resize = decltype(has_resize_test(0));
  using has_relocate = decltype(has_relocate_test(0));
  using has_block_align = decltype(has_block_align_test(0));

  static size_type block_align(allocator_type& a, size_type n) {
    return block_align_(has_block_align(), a, n);
  }

  static pointer relocate(allocator_type& a, pointer ptr, size_type from, size_type to, size_type size) {
    assert(from >= size);
    assert((from > 0) == (ptr != nullptr));
    return relocate_(has_relocate(), a, ptr, from, to, size);
  }
  static pointer relocate(allocator_type& a, pointer ptr, size_type from, size_type to) {
    return relocate(a, ptr, from, to, std::min(from, to));
  }

  static bool resize(allocator_type& a, pointer ptr, size_type from, size_type to) {
    assert((from > 0) == (ptr != nullptr));
    return resize_(has_resize(), a, ptr, from, to);
  }

private:
  static size_type block_align_(std::false_type, allocator_type&, size_type n) {
    static constexpr size_type blocksize = 16;
    auto in_blocks = (n * sizeof(value_type) + blocksize - 1) / blocksize;
    return in_blocks * blocksize / sizeof(value_type);
  }

  static size_type block_align_(std::true_type, allocator_type& a, size_type n) {
    return a.block_align(n);
  }

  static bool resize_(std::false_type, allocator_type&, pointer, size_type /* from */, size_type /* to */) {
    return false;
  }
  static bool resize_(std::true_type, allocator_type& a, pointer ptr, size_type from, size_type to) {
    return a.resize(ptr, from, to);
  }
  static pointer relocate_(std::true_type, allocator_type& a, pointer ptr, size_type from, size_type to, size_type size) {
    return a.relocate(ptr, from, to, size);
  }
  static pointer relocate_(std::false_type, allocator_type& a, pointer ptr, size_type from, size_type to, size_type size) {
    pointer new_space = nullptr;
    if (to > 0) {
      new_space = std::allocator_traits<T>::allocate(a, to);
      if (ptr) {
        std::copy_n(reinterpret_cast<unsigned char*>(std::addressof(*ptr)),
                    std::min(to, size) * sizeof(*ptr),
                    reinterpret_cast<unsigned char*>(std::addressof(*new_space)));
      }
    }
    if (ptr) {
      std::allocator_traits<T>::deallocate(a, ptr, from);
    }
    return new_space;
  }
};

struct reserve_t {};
struct default_init_t {};

template <typename T, typename Allocator =
          typename std::conditional<
            is_relocatable_t<T>::value,
            reallocator<T>,
            std::allocator<T>>::type>
class vector : private Allocator {
  using ATraits = reallocator_traits<Allocator>;

  static constexpr bool DEBUG = true;
  static constexpr bool trivial_destruction =
    std::is_trivially_destructible<T>::value;
  static constexpr bool trivial_default_construction =
    std::is_trivially_default_constructible<T>::value;

  struct unchecked_insert_iterator : std::iterator<std::output_iterator_tag, T> {
    vector* v_;

    unchecked_insert_iterator() noexcept : v_(nullptr) {}
    explicit unchecked_insert_iterator(vector& v) noexcept : v_(&v) {}

    unchecked_insert_iterator& operator* () {
      return *this;
    }
    unchecked_insert_iterator& operator ++ () {
      return *this;
    }
    unchecked_insert_iterator& operator ++ (int) {
      return *this;
    }

    template <typename U, typename=typename std::enable_if<std::is_convertible<U&&, T>::value>::type>
    unchecked_insert_iterator& operator = (U&& u) {
      v_->unchecked_emplace_back(std::forward<U>(u));
      return *this;
    }

    unchecked_insert_iterator& operator = (default_init_t) {
      v_->unchecked_emplace_back(default_init_t());
      return *this;
    }

    friend bool operator == (unchecked_insert_iterator const& a, unchecked_insert_iterator const& b) noexcept {
      return a.v_ == b.v_;
    }
    friend bool operator != (unchecked_insert_iterator const& a, unchecked_insert_iterator const& b) noexcept {
      return a.v_ != b.v_;
    }
  };

public:
  using value_type = T;
  using allocator_type = Allocator;
  static_assert(std::is_same<value_type, typename allocator_type::value_type>::value,
                "value_type and allocator_type::value_type must be the same.");
  using size_type = typename ATraits::size_type;
  using difference_type = typename ATraits::difference_type;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = typename ATraits::pointer;
  using const_pointer = typename ATraits::const_pointer;
  using scaling_factor = std::ratio<2,1>;
  static_assert(scaling_factor::num > scaling_factor::den,
                "scaling_factor must be greater than 1.");

  vector() noexcept = default;
  explicit vector(const Allocator& a) noexcept :
    Allocator(a) {}

  vector(const vector& other) :
    vector(other, ATraits::select_on_container_copy_construction(other.alloc())) {}
  vector(const vector& other, const Allocator& a) :
    vector(other.begin(), other.end(), a) {}

  vector(vector&& other) noexcept :
    Allocator(std::move(other.alloc())),
    first_(exchange(other.first_, nullptr)),
    last_(exchange(other.last_, nullptr)),
    end_(exchange(other.end_, nullptr)) {}
  vector(vector&& other, const Allocator& a) :
    vector(a) {
    if (alloc() == other.alloc()) {
      first_ = exchange(other.first_, nullptr);
      last_ = exchange(other.last_, nullptr);
      end_ = exchange(other.end_, nullptr);
    } else {
      assign(std::make_move_iterator(other.begin()),
             std::make_move_iterator(other.end()));
    }
  }

  vector(size_type n, reserve_t, const Allocator& a = Allocator()) :
    Allocator(a),
    first_(n ? ATraits::allocate(alloc(), n) : pointer{nullptr}),
    last_(first_), end_(first_ + n) {}

  explicit vector(size_type n, const Allocator& a = Allocator()) :
    vector(n, reserve_t(), a) {
    while (n-- > 0) {
      unchecked_emplace_back();
    }
  }

  vector(size_type n, default_init_t d, const Allocator& a = Allocator()) :
    vector(n, reserve_t(), a) {
    if (trivial_default_construction) {
      last_ = first_ + n;
    } else {
      while (n-- > 0) {
        unchecked_emplace_back(d);
      }
    }
  }

  vector(size_type n, const T& value, const Allocator& a = Allocator()) :
    vector(n, reserve_t(), a) {
    while (n-- > 0) {
      unchecked_emplace_back(value);
    }
  }

  template <typename InputIterator>
  vector(InputIterator first, InputIterator last, const Allocator& a = Allocator()) :
    vector(a) {
    assign(first, last);
  }

  vector(std::initializer_list<T> il, const Allocator& a = Allocator()) :
    vector(il.begin(), il.end(), a) {}

  ~vector() noexcept {
    clear();
    ATraits::deallocate(alloc(), first_, capacity());
  }

  vector& operator = (const vector& other) & {
    clear();
    if (typename ATraits::propagate_on_container_copy_assignment() && alloc() != other.alloc()) {
      ATraits::deallocate(alloc(), first_, capacity());
      first_ = last_ = end_ = nullptr;
      alloc() = other.alloc();
    }
    assign(other.begin(), other.end());
    return *this;
  }

  vector& operator = (vector&& other) &
    noexcept(ATraits::propagate_on_container_move_assignment::value) {
    clear();
    if (typename ATraits::propagate_on_container_move_assignment() || alloc() == other.alloc()) {
      ATraits::deallocate(alloc(), first_, capacity());
      if (typename ATraits::propagate_on_container_move_assignment()) {
        alloc() = std::move(other.alloc());
      }
      first_ = exchange(other.first_, nullptr);
      last_ = exchange(other.last_, nullptr);
      end_ = exchange(other.end_, nullptr);
    } else {
      assign(std::make_move_iterator(other.begin()),
             std::make_move_iterator(other.end()));
    }
    return *this;
  }

  vector& operator = (std::initializer_list<T> il) & {
    assign(il);
    return *this;
  }

  void swap(vector& other)
    noexcept(ATraits::propagate_on_container_swap::value) {
    using std::swap;
    if (typename ATraits::propagate_on_container_swap()) {
      swap(alloc(), other.alloc());
    } else {
      assert(alloc() == other.alloc());
    }
    swap(first_, other.first_);
    swap(last_, other.last_);
    swap(end_, other.end_);
  }
  friend void swap(vector& a, vector& b) noexcept(noexcept(a.swap(b))) {
    a.swap(b);
  }

  allocator_type get_allocator() const { return alloc(); }

  reference at(size_type i) {
    if (i < size()) {
      return first_[i];
    }
    throw std::out_of_range("index out of range in vector::at");
  }
  const_reference at(size_type i) const {
    if (i < size()) {
      return first_[i];
    }
    throw std::out_of_range("index out of range in vector::at");
  }

  reference operator [] (size_type i) {
    assert(i < size());
    return first_[i];
  }
  const_reference operator [] (size_type i) const {
    assert(i < size());
    return first_[i];
  }

  reference front() { assert(!empty()); return *first_; }
  const_reference front() const { assert(!empty()); return *first_; }
  reference back() { assert(!empty()); return *(last_ - 1); }
  const_reference back() const { assert(!empty()); return *(last_ - 1); }

  pointer data() { return first_; }
  const_pointer data() const { return first_; }

  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  iterator begin() { return first_; }
  iterator end() { return last_; }
  const_iterator begin() const { return first_; }
  const_iterator end() const { return last_; }
  const_iterator cbegin() const { return begin(); }
  const_iterator cend() const { return end(); }
  reverse_iterator rbegin() { return {end()}; }
  reverse_iterator rend() { return {begin()}; }
  const_reverse_iterator rbegin() const { return {end()}; }
  const_reverse_iterator rend() const { return {begin()}; }
  const_reverse_iterator crbegin() const { return rbegin(); }
  const_reverse_iterator crend() const { return rend(); }

  bool empty() const noexcept { return first_ == last_; }
  size_type size() const noexcept { return last_ - first_; }
  size_type max_size() const noexcept { return ATraits::max_size(alloc()); }

  void reserve(size_type new_capacity) {
    if (new_capacity > capacity()) {
      adjust_capacity(new_capacity);
    }
  }

  size_type capacity() const noexcept { return end_ - first_; }

  void shrink_to_fit() {
    auto const min_capacity = ATraits::block_align(alloc(), size());
    if (min_capacity < capacity()) {
      adjust_capacity(min_capacity);
    }
  }

  void clear() noexcept {
    if (trivial_destruction) {
      last_ = first_;
    } else {
      while (last_ != first_) {
        ATraits::destroy(alloc(), --last_);
      }
    }
  }

  iterator insert(const_iterator pos, const T& value) {
    return emplace(pos, value);
  }
  iterator insert(const_iterator pos, T&& value) {
    return emplace(pos, std::move(value));
  }
  iterator insert(const_iterator pos, size_type n, const T &value);
  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
  }
  template <typename InputIterator>
  auto insert(const_iterator pos, InputIterator first, InputIterator last) ->
    decltype((void)(typename std::iterator_traits<InputIterator>::iterator_category()), iterator()) {
    return insert_(typename std::iterator_traits<InputIterator>::iterator_category(),
                   pos, first, last);
  }

  template <typename... Args>
  iterator emplace(const_iterator cpos, Args&&... args);

  void resize(size_type new_size) {
    resize_common(new_size);
  }
  void resize(size_type new_size, const T& value) {
    resize_common(new_size, value);
  }
  void resize(size_type new_size, default_init_t d) {
    resize_common(new_size, d);
  }

  void assign(size_type n, const T& value) {
    if (capacity() < n) {
      vector{n, value, alloc()}.swap(*this);
    } else {
      if (n < size()) {
        resize(n);
      }
      std::fill(begin(), end(), value);
      auto const s = size();
      if (n > s) {
        std::uninitialized_fill_n(last_, n - s, value);
        last_ += n - s;
      }
    }
  }

  template <typename InputIterator>
  auto assign(InputIterator first, InputIterator last) ->
    decltype(std::iterator_traits<InputIterator>::iterator_category, void()) {
    assign_(typename std::iterator_traits<InputIterator>::iterator_category(), first, last);
  }

  void assign(std::initializer_list<T> il) {
    assign(il.begin(), il.end());
  }

  unchecked_insert_iterator unchecked_inserter() {
    return unchecked_insert_iterator{*this};
  }

  template <typename... Args>
  void unchecked_emplace_back(Args&&... args) {
    assert(last_ != end_);
    ATraits::construct(alloc(), last_, std::forward<Args>(args)...);
    ++last_;
  }
  void unchecked_emplace_back(default_init_t) {
    assert(last_ != end_);
    if (!trivial_default_construction) {
      ::new(static_cast<void*>(last_)) T;
    }
    ++last_;
  }
  template <typename... Args>
  void emplace_back(Args&&... args) {
    if (last_ == end_) {
      auto tmp = T(std::forward<Args>(args)...);
      grow();
      unchecked_emplace_back(std::move_if_noexcept(tmp));
    } else {
      unchecked_emplace_back(std::forward<Args>(args)...);
    }
  }
  void emplace_back(default_init_t d) {
    if (last_ == end_) {
      grow();
    }
    unchecked_emplace_back(d);
  }

  void push_back(const T& t) {
    emplace_back(t);
  }
  void push_back(T&& t) {
    emplace_back(std::move(t));
  }
  void push_back(default_init_t d) {
    emplace_back(d);
  }

  void pop_back() {
    assert(!empty());
    if (!trivial_destruction) {
      ATraits::destroy(alloc(), last_ - 1);
    }
    --last_;
  }

private:
  Allocator& alloc() { return *this; }
  Allocator const& alloc() const { return *this; }

  template <typename InputIterator>
  void assign_(std::input_iterator_tag, InputIterator first, InputIterator last) {
    clear();
    std::copy(first, last, std::back_inserter(*this));
  }

  template <typename ForwardIterator>
  void assign_(std::forward_iterator_tag, ForwardIterator first, ForwardIterator last) {
    auto n = std::distance(first, last);
    if (capacity() < n) {
      vector{first, last, alloc()}.swap(*this);
    } else {
      if (n < size()) {
        resize(n);
      }
      for (auto& i : *this) {
        assert(first != last);
        i = *first;
        ++first;
      }
      last_ = std::uninitialized_copy(first, last, last_);
    }
  }

  void grow_to(size_type min_capacity) {
    auto new_capacity = capacity();
    if (!new_capacity) {
      new_capacity = 1;
    }
    while (new_capacity < min_capacity) {
      new_capacity = (scaling_factor::num * new_capacity + scaling_factor::den - 1) / scaling_factor::den;
    }
    adjust_capacity(new_capacity);
  }

  void grow() {
    grow_to(capacity() + 1);
  }

  void resize_capacity(const size_type new_size);
  template <typename... Args>
  void resize_common(const size_type new_size, Args&&... args) {
    resize_capacity(new_size);
    while (size() < new_size) {
      unchecked_emplace_back(std::forward<Args>(args)...);
    }
  }

  void adjust_capacity(size_type new_capacity);
  template <typename InputIterator>
  iterator insert_(std::input_iterator_tag, const_iterator pos, InputIterator first, InputIterator last);
  template <typename ForwardIterator>
  iterator insert_(std::forward_iterator_tag, const_iterator pos, ForwardIterator first, ForwardIterator last);

  pointer first_ = nullptr, last_ = nullptr, end_ = nullptr;
};

template <typename T, typename A>
void vector<T, A>::resize_capacity(const size_type new_size) {
  if (new_size <= size()) {
    if (trivial_destruction) {
      last_ = first_ + new_size;
    } else {
      do {
        pop_back();
      } while (new_size < size());
    }
  } else if (new_size > size()) {
    reserve(new_size);
  }
  assert(capacity() >= new_size);
}

template <typename T, typename A>
void vector<T, A>::adjust_capacity(size_type new_capacity) {
  new_capacity = ATraits::block_align(alloc(), new_capacity);
  assert(new_capacity >= size());

  if (is_relocatable_t<T>::value) {
    auto ptr = ATraits::relocate(alloc(), first_, capacity(), new_capacity, size());
    if (DEBUG) {
      std::cout << "relocate from " << first_ << '[' << capacity() << "] to "
                << ptr << '[' << new_capacity << "]\n";
    }
    end_ = ptr + new_capacity;
    last_ = ptr + size();
    first_ = ptr;
  } else if (ATraits::resize(alloc(), first_, capacity(), new_capacity)) {
    if (DEBUG) {
      std::cout << "resize " << first_ << " from "
                << capacity() << " to "
                << new_capacity << '\n';
    }
    end_ = first_ + new_capacity;
  } else {
    auto tmp = vector{new_capacity, reserve_t(), alloc()};
    tmp.last_ = std::uninitialized_copy(maybe_move_iterator(begin()),
                                        maybe_move_iterator(end()), tmp.first_);
    if (DEBUG) {
      std::cout << "fresh allocation from " << first_ << '[' << capacity() << "] to "
                << tmp.first_ << '[' << new_capacity << "]\n";
    }
    swap(tmp);
  }
}

template <typename T, typename A>
template <typename... Args>
auto vector<T, A>::emplace(const_iterator cpos, Args&&... args) -> iterator {
  assert(first_ <= cpos && cpos <= last_);
  auto const index = cpos - first_;
  T tmp(std::forward<Args>(args)...);
  if (last_ == end_) {
    grow();
  }

  auto const pos = first_ + index;
  if (pos == last_) {
    unchecked_emplace_back(std::move_if_noexcept(tmp));
  } else {
    unchecked_emplace_back(std::move_if_noexcept(*(last_ - 1)));
    std::copy_backward(maybe_move_iterator(pos),
                       maybe_move_iterator(last_ - 2),
                       last_ - 1);
    *pos = std::move_if_noexcept(tmp);
  }

  return pos;
}

template <typename T, typename A>
auto vector<T, A>::insert(const_iterator cpos, size_type n, const T &value) -> iterator {
  assert(first_ <= cpos && cpos <= last_);
  auto const index = cpos - begin();
  if (!n) {
    return first_ + index;
  }
  T tmp(value);

  if (n > size_type(end_ - last_)) {
    grow_to(size() + n);
  }

  auto const pos = first_ + index;
  auto delta = size_type(0);
  if (size_type(last_ - pos) < n) {
    delta = n - (last_ - pos);
  }
  std::uninitialized_fill_n(last_, delta, tmp);
  last_ += delta;
  last_ = std::uninitialized_copy_n(maybe_move_iterator(last_ - n),
                                    n - delta, last_);
  if (!delta) {
    std::copy_backward(maybe_move_iterator(pos),
                       maybe_move_iterator(last_ - 2 * n), last_ - n);
  }
  std::fill_n(pos, n - delta, tmp);
  return pos;
}

template <typename T, typename A>
template <typename ForwardIterator>
auto vector<T, A>::insert_(std::forward_iterator_tag,
                           const_iterator cpos,
                           ForwardIterator first,
                           ForwardIterator last) -> iterator {
  assert(first_ <= cpos && cpos <= last_);
  auto const index = cpos - begin();

  auto const n = size_type(std::distance(first, last));
  if (!n) {
    return first_ + index;
  }
  if (n > size_type(end_ - last_)) {
    grow_to(size() + n);
  }

  last_ = std::uninitialized_copy(first, last, last_);
  auto const pos = first_ + index;
  std::rotate(pos, last_ - n, last_);
  return pos;
}

template <typename T, typename A>
template <typename InputIterator>
auto vector<T, A>::insert_(std::input_iterator_tag,
                           const_iterator cpos,
                           InputIterator first,
                           InputIterator last) -> iterator {
  assert(first_ <= cpos && cpos <= last_);
  auto const index = cpos - begin();
  auto const original_size = size();

  try {
    std::copy(first, last, std::back_inserter(*this));
  } catch(...) {
    resize(original_size);
    throw;
  }

  auto const pos = first_ + index;
  std::rotate(pos, first_ + original_size, last_);
  return pos;
}


template <typename T>
class Wrapper {
  static constexpr bool DEBUG = true;
  T value;
public:
  Wrapper() noexcept {
    if (DEBUG) {
      std::cout << "Wrapper()\n";
    }
  }
  Wrapper(T i) noexcept : value(std::move(i)) {
    if (DEBUG) {
      std::cout << "Wrapper(" << value << ")\n";
    }
  }
  Wrapper(Wrapper const& other) noexcept : value(other.value) {
    if (DEBUG) {
      std::cout << "Wrapper(Wrapper const&" << value << ")\n";
    }
  }
  Wrapper& operator = (Wrapper const& other) & noexcept {
    value = other.value;
    if (DEBUG) {
      std::cout << "operator=(Wrapper const&" << value << ")\n";
    }
    return *this;
  }
  Wrapper(Wrapper&& other) noexcept : value(std::move(other.value)) {
    if (DEBUG) {
      std::cout << "Wrapper(Wrapper&&" << value << ")\n";
    }
  }
  Wrapper& operator = (Wrapper&& other) & noexcept {
    value = std::move(other.value);
    if (DEBUG) { std::cout << "operator=(Wrapper&&" << value << ")\n"; }
    return *this;
  }
  ~Wrapper() noexcept {
    if (DEBUG) {
      std::cout << "~Wrapper(" << value << ")\n";
    }
  }
  // operator T () const noexcept { return value; }
  friend void swap(Wrapper& a, Wrapper& b) noexcept {
    using std::swap;
    if (DEBUG) {
      std::cout << "swap(Wrapper(" << a.value << "), Wrapper(" << b.value << "))\n";
    }
    swap(a.value, b.value);
  }
  friend std::ostream& operator << (std::ostream& os, const Wrapper& w) {
    os << w.value;
    return os;
  }
};

template <typename T>
struct is_relocatable<Wrapper<T>> {
  using type = is_relocatable_t<T>;
};

template <typename T>
void dump(const T& t) {
  std::cout << '{';
  auto first = true;
  for (auto&& i : t) {
    if (first) {
      first = false;
    } else {
      std::cout << ", ";
    }
    std::cout << i;
  }
  std::cout << '}';
}

template <typename Iterator, typename Tag = std::input_iterator_tag>
class iterator_hack : public std::iterator<
    Tag,
    typename std::iterator_traits<Iterator>::value_type,
    typename std::iterator_traits<Iterator>::difference_type,
    typename std::iterator_traits<Iterator>::pointer,
    typename std::iterator_traits<Iterator>::reference> {
  Iterator iter_;
public:
  iterator_hack() = default;
  iterator_hack(Iterator iter) : iter_(std::move(iter)) {}

  friend bool operator == (const iterator_hack& a, const iterator_hack& b) {
    return a.iter_ == b.iter_;
  }
  friend bool operator != (const iterator_hack& a, const iterator_hack& b) {
    return a.iter_ != b.iter_;
  }

  auto operator * () const -> decltype(*iter_) { return *iter_; }
  auto operator -> () const -> const Iterator& { return iter_; }

  iterator_hack& operator ++ () {
    ++iter_;
    return *this;
  }
  iterator_hack operator ++ (int) {
    auto tmp = *this;
    ++iter_;
    return tmp;
  }
};

template <typename Tag = std::input_iterator_tag, typename Iterator>
auto hack_iterator(Iterator iter) ->
  decltype(iterator_hack<Iterator, Tag>(iter)) {
    return iterator_hack<Iterator, Tag>(iter);
}

int main() {
  std::cout << std::boolalpha;
  {
    vector<Wrapper<int>> vec;
    for (auto i = 0, e = 19; i < e; ++i) {
      vec.emplace_back(i);
    }
    dump(vec);
    std::cout << '\n';
    vec.shrink_to_fit();
  }
  std::cout << '\n';
  {
    vector<Wrapper<int>> vec;
    int some_ints[7];
    std::iota(std::begin(some_ints), std::end(some_ints), 0);
    vec.insert(vec.end(),
               std::begin(some_ints), std::end(some_ints));
    std::transform(std::begin(some_ints), std::end(some_ints), std::begin(some_ints), [](int i){ return -i; });
    vec.insert(vec.end() - 2,
               hack_iterator(std::begin(some_ints)), hack_iterator(std::end(some_ints)));
    dump(vec);
    std::cout << '\n';
  }
}
