#include <iterator>
#include <utility>

template<typename Target, typename Underlying>
struct cast_iterator_t
{
    Underlying it;

    Target operator*() const
    {
        return (Target) *it;
    }

    bool operator==(cast_iterator_t that) const
    {
        return it == that.it;
    }   

    bool operator!=(cast_iterator_t that) const
    {
        return it != that.it;
    }   

    cast_iterator_t& operator++()
    {
        ++it;
        return *this;
    }

    cast_iterator_t operator++(int)
    {
        cast_iterator_t old(*this);
        ++*this;
        return old;
    }
};

template<typename Target, typename Underlying>
cast_iterator_t<Target, Underlying> cast_iterator(Underlying it)
{
    return {it};
}

template<typename Target, typename Range>
struct cast_range_t
{
    Range range; // 1

    decltype(cast_iterator<Target>(std::begin(range))) begin()
    {
      return cast_iterator<Target>(std::begin(range));
    }

    decltype(cast_iterator<Target>(std::end(range))) end()
    {
      return cast_iterator<Target>(std::end(range));
    }
};

template<typename Target, typename Range>
cast_range_t<Target, Range> cast_range(Range&& range) // 2
{
    return {std::forward<Range>(range)}; // 3
}

#include <iostream>
#include <vector>

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
  for(auto obj : cast_range<ClassB*>(vecA)) {
    obj->DoSomething();
  }
}

int main() {
  vecA.emplace_back(new ClassB);
  vecA.emplace_back(new ClassB);
  iterate();
}
