#include <boost/intrusive/splay_set.hpp>
#include <boost/lexical_cast.hpp>

#include <vector>
#include <algorithm>

using namespace boost::intrusive;

class MyType : public splay_set_base_hook<>
{
    int int_;

  public:
    MyType(int i) :  int_(i)
    {}

    // default ordering
    friend bool operator<  (const MyType &a, const MyType &b) {  return a.int_ <  b.int_;  }
    friend bool operator>  (const MyType &a, const MyType &b) {  return a.int_ >  b.int_;  }
    friend bool operator== (const MyType &a, const MyType &b) {  return a.int_ == b.int_;  }

    int getValue() const { return int_; }
};

struct CompareReversed {

    bool operator()(MyType const& a, MyType const& b) const {
        return reversed(a.getValue()) < reversed(b.getValue());
    }

  private:

    static int reversed(int i)
    {
        auto s = std::to_string(i);
        std::reverse(s.begin(), s.end());
        return boost::lexical_cast<int>(s);
    }
};

#include <iostream>

int main()
{
    //typedef splay_set<MyType, compare<std::less<MyType> > > Set;
    typedef splay_set<MyType, compare<CompareReversed> > Set;

    std::vector<MyType> v { 24, 42, 123, 321 };

    Set set;
    set.insert(v[0]);
    set.insert(v[1]);
    set.insert(v[2]);
    set.insert(v[3]);

    for (auto& el : set)
    {
        std::cout << el.getValue() << "\n";
    }

    std::cout << set.count(24) << "\n"; // 1
    std::cout << set.count(25) << "\n"; // 0
    std::cout << set.count(42) << "\n"; // 1
}
