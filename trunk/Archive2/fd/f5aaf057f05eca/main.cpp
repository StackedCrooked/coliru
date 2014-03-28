#include <cassert>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>
#include <boost/iterator/iterator_facade.hpp>

template <typename T, typename Range>
struct casted_range {
  Range range_;

  class iterator : public boost::iterator_facade<iterator,T,std::input_iterator_tag,T> {
    friend boost::iterator_core_access;

    using base_iterator = decltype(std::begin(range_));
    base_iterator base_;

    using source_type = typename std::decay<decltype(*base_)>::type;
    using can_dynamic_cast = 
      std::integral_constant<bool,
        std::is_pointer<T>::value &&
        std::is_pointer<source_type>::value &&
        std::is_polymorphic<typename std::remove_pointer<source_type>::type>::value
      >;
      
    T dereference(std::false_type) const {
      return static_cast<T>(*base_);
    }

    T dereference(std::true_type) const {
      assert(dynamic_cast<T>(*base_));
      return static_cast<T>(*base_);
    }

    T dereference() const {
      return dereference(can_dynamic_cast{});
    }
    
    void increment() { ++base_; }
    
    bool equal(const iterator& other) const {
      return base_ == other.base_;
    }
    
  public:
    iterator(base_iterator base) : base_{base} {}
  };

  iterator begin() { return {std::begin(range_)}; }
  iterator end()   { return {std::end(range_)}; }
};

template <typename T, typename Range>
casted_range<T, Range> range_of(Range&& range) {
  return {std::forward<Range>(range)};
}

class ClassA {
public:
  virtual ~ClassA() = default;
};

class ClassB : public ClassA {
public:
  void DoSomething() const { std::cout << "something: " << this << '\n'; }
};

std::vector<ClassA*> vecA;

void iterate()
{
  for(auto obj : range_of<ClassB*>(vecA)) {
    obj->DoSomething();
  }
}

int main() {
  vecA.emplace_back(new ClassB);
  vecA.emplace_back(new ClassB);
  iterate();
}
