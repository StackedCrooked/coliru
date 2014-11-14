#include <iostream>
#include <vector>
#include <algorithm>

class spObj {
    int r;

  public:
    spObj() : r(0)                   { std::cout << "spObj constructed\n"; }
    spObj(const spObj &_r) : r(_r.r) { std::cout << "spObj copied\n"; }
   ~spObj()                          { std::cout << "spObj destroyed\n"; }
    spObj operator=(const spObj &_r) {
        this->r = _r.r;
        std::cout << "spObj assigned\n";
        return *this;
    }
};

template <typename Obj, typename Container = std::vector<Obj> >
class TSearchModule {
  private:
    Container container;

    TSearchModule(TSearchModule const&);
    TSearchModule& operator=(TSearchModule const&);
  public:
    TSearchModule() {}

    template <typename Cond>
    void Search(Cond const& cond) {
        while (cond(const_cast<TSearchModule const&>(*this))) {
            container.insert(container.end(), spObj());
        }
    }
    typename Container::iterator begin()       { return container.begin(); }
    typename Container::iterator end()         { return container.end(); }
             size_t              size()  const { return container.size(); }
};
//---------------------------------------------------------------------------

struct sizeLessThan {
    size_t _n;
    sizeLessThan(size_t n) : _n(n) {}
    template <typename TSearchModule> bool operator()(TSearchModule const &sm) const {
        return sm.size() < _n; 
    }
};

struct doNothing {
    doNothing() : row_top(0) {};
    void operator()(const spObj&) { std::cout << __PRETTY_FUNCTION__ << " row_top: " << ++row_top << "\n"; };
    int row_top;
};

int main() {
    typedef TSearchModule<spObj> TSM;

    TSM myModule;
    myModule.Search(sizeLessThan(5));

    std::for_each(myModule.begin(), myModule.end(), doNothing());
}
