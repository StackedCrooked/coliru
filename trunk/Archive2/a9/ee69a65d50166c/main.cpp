#include <boost/variant.hpp>
#include <iostream>

class ZIndexLess
    : public boost::static_visitor<bool>
{
public:
    template <typename T, typename U>
    bool operator()( const T &lhs, const U &rhs) const
    {
        if (lhs.zindex != rhs.zindex) {
            return lhs.zindex < rhs.zindex;
        }
        
        return typeid(lhs).before(typeid(rhs));
    }

    template <typename T>
    bool operator()( const T & lhs, const T & rhs ) const
    {
        return lhs.zindex < rhs.zindex;
    }
};

template<typename... T>
struct ZIndexComparator {
    bool operator()(const boost::variant<T...>& l, const boost::variant<T...>& r) 
    { 
        return boost::apply_visitor(ZIndexLess(), l, r);
    }
};

template<typename... T>
class MultiCollection {
public:
    void add(const boost::variant<T...>& item) { collection_.push_back(item); }

    //преполагаю, что sort будет зваться для RS, но не будет зваться для RO
    template <typename ComparatorType>
    void sort(const ComparatorType& cmp) {
        std::sort(collection_.begin(), collection_.end(), cmp); //сортируем используя boost::variant operator <
    }

    template <typename Visitor>
    void traverse(Visitor& visitor) {
        for (auto& item : collection_) {
            boost::apply_visitor(visitor, item);
        }
    }

private:
    std::vector<boost::variant<T...>> collection_;    
};


struct A {
    A(int zindex) : zindex(zindex) {}
    int zindex;         
};

struct B {
    B(int zindex) : zindex(zindex) {}
    int zindex;         
};

//Comparator<A, B> cmp;

struct VisitorImpl : public boost::static_visitor<> {
    void operator()(A& v) { std::cout << "A" << v.zindex << "\n"; }
    void operator()(B& v) { std::cout << "B" << v.zindex << "\n"; }
};

int main() {
    VisitorImpl visitor; 
    MultiCollection<A, B> collection;
    collection.add(A(2));
    collection.add(B(1));
    collection.add(B(2));
    collection.sort(ZIndexComparator<A, B>());

    collection.traverse(visitor);
    //boost::apply_visitor(visitor, v);
    return 0;
}

