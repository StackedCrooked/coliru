#include <algorithm>
#include <map>

#include <boost/shared_ptr.hpp>

class Base {
public:
    Base(int v) : id(v) {};
    int id; 
    
    bool operator<(const Base& b)
    {
        return true;
    };
};

class Derived : public Base {
public:
    Derived(int v) : Base(v) {};
};


struct CompareFunc {
//    template <typename T1, typename T2>
//    bool operator()(const boost::shared_ptr<T1>& me_lhs, const boost::shared_ptr<T2>& me_rhs)
//    {
//        return me_lhs->id > me_rhs->id;
//    }

//    template <typename T1, typename T2>
//    bool operator()(const T1& lhs, const T2& rhs)
//    {
//        return true;
//    }
};



int main()
{
    std::map<boost::shared_ptr<Derived>, double, std::less<boost::shared_ptr<Base>>> m;
    m.insert(std::make_pair(boost::shared_ptr<Derived>(new Derived(1)), 10));
    m.insert(std::make_pair(boost::shared_ptr<Derived>(new Derived(2)), 20));
    
    //auto d1 = boost::shared_ptr<Derived>(new Derived(1));
    //m.find(d1);
    
    auto b1 = boost::shared_ptr<dynamic_cast<Derived>(Base)>(new Base(1));
    m.find(b1);

    return 0;
}
