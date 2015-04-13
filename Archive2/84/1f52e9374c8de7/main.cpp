#include <iostream>
#include <vector>
#include <initializer_list>
 
template <class T>
struct S {
    std::vector<T> v;
    S(std::initializer_list<T> l) : v(l) {
         std::cout << "constructed with a " << l.size() << "-element list\n";
    }
    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }
    std::pair<const T*, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // copy-list-initialization in return statement
                                   // this is NOT a use of std::initializer_list
    }
};

template <typename T>
void templated_fn(T) {}

class Measure {
public:
    Measure (std::initializer_list<std::string> labels) : labels (labels) {

    }
    std::vector<std::string> const & getLabels () const {
        return labels;
    }
    std::vector<std::vector<double > > const& getValues () const {
        return values;
    }
    virtual void calc () = 0;
protected:
    std::vector<std::string> const labels;
    std::vector<std::vector<double> > values;
};

class ShortABMeasure final : public Measure {
public:
    ShortABMeasure () : Measure({"mlog shortA", "phase shortA", "mlog shortB", "phase shortB"}) {
    }
    void calc () override {
        std::cout << "1";
    }
};
int main()
{
    std::vector<Measure* > measure {new ShortABMeasure()};
    measure.front()->calc();
    S<int> s = {1, 2, 3, 4, 5}; // copy list-initialization
    s.append({6, 7, 8});      // list-initialization in function call
 
    std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";
 
    for (auto n : s.v) std::cout << ' ' << n;
 
    std::cout << '\n';
 
    std::cout << "range-for over brace-init-list: \n";
 
    for (int x : {-1, -2, -3}) // the rule for auto makes this ranged for work
        std::cout << x << ' ';
    std::cout << '\n';
 
    auto al = {10, 11, 12};   // special rule for auto
 
    std::cout << "The list bound to auto has size() = " << al.size() << '\n';
 
//    templated_fn({1, 2, 3}); // compiler error! "{1, 2, 3}" is not an expression,
                             // it has no type, and so T cannot be deduced
    templated_fn<std::initializer_list<int>>({1, 2, 3}); // OK
    templated_fn<std::vector<int>>({1, 2, 3});           // also OK
}

