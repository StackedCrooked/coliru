#include <iostream>
#include <cassert>
using namespace std;

class S {
    int v1[20];
    int v2[20];
    int N;
public:
    S(){
        N = 10;   
    }
    
    class iterator;
    class const_iterator;

    class P {
        friend class const_iterator;
        S *s;
        int i;

        P &operator ++() { ++i; return *this; }
        P &operator ++(int) { ++i; return *this; }
    public:
        P() : s(nullptr), i(0) {}
        P(const P &p) : s(p.s), i(p.i) {}
        P(P &&p) : s(p.s), i(p.i) {}
        P & operator = (const P &p) { s = p.s; i = p.i; }
        P & operator = (P &&p) { s = p.s; i = p.i; }
        
        explicit P(S &_s, int _i) : s(&_s), i(_i) {}
        int &V1() { return s->v1[i]; }
        int V1() const { return s->v1[i]; }
        int &V2() { return s->v2[i]; }
        int V2() const { return s->v2[i]; }
    };
    
    class const_iterator {
        friend class S;
        friend class iterator;
        P p;

        const_iterator(S &_s, int _i) : p(_s, _i) {}
    public:
        const_iterator() {}
        const_iterator(const const_iterator &i) : p(i.p) {}
        const_iterator(const_iterator &&i) : p(i.p) {}
        const_iterator & operator = (const const_iterator &i) { p = i.p; }
        const_iterator & operator = (const_iterator &&i) { p = i.p; }

        const_iterator &operator ++() { ++p; return *this; }
        const_iterator &operator ++(int) { ++p; return *this; }
        const P &operator *() const { return p; }
        const P *operator -> () const { return &p; }

        bool operator == (const const_iterator &other) const { 
            assert(&p.s == &other.p.s);
            return p.i == other.p.i;
        }
    
        bool operator != (const const_iterator &other) const { 
            return !(*this == other);
        }
    };

    class iterator : public const_iterator {
        friend class S;
        iterator(S &_s, int _i) : const_iterator(_s, _i) {}
    public:
        P &operator *() { return p; }
        P *operator -> () { return &p; }
    };
    
    iterator begin() { return iterator(*this, 0); }
    const_iterator begin() const { return const_iterator(const_cast<S&>(*this), 0); }
    const_iterator cbegin() const { return begin(); }

    iterator end() { return iterator(*this, N); }
    const_iterator end() const { return const_iterator(const_cast<S&>(*this), N); }
    const_iterator cend() const { return end(); }
};

S::iterator begin(S &s) { return s.begin(); }


int main() {
    S s;
    int i = 0;
    cout << "1" << endl;
    //for(auto x = s.begin(); x != s.end(); x++) {
      //  x->V1() = 5 + i;
    //    x->V2() = 5 - i;
  //      ++i;
//    }
    cout << "2" << endl;
    S::const_iterator tmp;
    cout << "5" << endl;
    for(auto x = s.cbegin(); x != s.cend(); x++) {
        cout << x->V1() << " " << x->V2() << endl;
    }
}
