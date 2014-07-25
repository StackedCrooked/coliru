#include <boost/unordered_map.hpp>
#include <boost/intrusive_ptr.hpp>

struct A
{
    void doSomething() {}

  private:
    int refcount = 0;
    friend void intrusive_ptr_add_ref(A* px) { ++px->refcount; }
    friend void intrusive_ptr_release(A* px) { --px->refcount; if (!px->refcount) delete px; }
};

int main()
{
    boost::unordered_map<int, boost::intrusive_ptr<A>> m;
    m.emplace(0, new A());
    m.emplace(1, new A());
    m.emplace(2, new A());

    // later...
    std::vector<boost::intrusive_ptr<A>> f;
    boost::unordered_map<int, boost::intrusive_ptr<A>>::iterator i;

    i = m.find(0);
    f.push_back(i->second);
    i = m.find(1);
    f.push_back(i->second);
    i = m.find(2);
    f.push_back(i->second);

    // and then do operations on f:
    for(size_t i = 0; i < f.size(); ++i) {
        f[i]->doSomething();
    }
}
