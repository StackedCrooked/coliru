#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

class A {
public:
    void doSomething() {}
     A(A const&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
     A()         { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    ~A()         { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

int main()
{
    boost::ptr_unordered_map<int, A> m;
    m.insert(0, std::auto_ptr<A>(new A()));
    m.insert(1, std::auto_ptr<A>(new A()));
    m.insert(2, std::auto_ptr<A>(new A()));

    // later...
    {
        boost::ptr_vector<A> f;
        boost::ptr_unordered_map<int, A>::iterator i;

        i = m.find(0);
        f.push_back(std::auto_ptr<A>(new A(*i->second)));
        i = m.find(1);
        f.push_back(std::auto_ptr<A>(new A(*i->second)));
        i = m.find(2);
        f.push_back(std::auto_ptr<A>(new A(*i->second)));

        // and then do operations on f:
        for(size_t i = 0; i < f.size(); ++i) {
            f[i].doSomething();
        }
    }

    std::cout << "Done\n";

}
