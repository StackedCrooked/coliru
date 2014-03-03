#include <utility>


struct AbstractPair
{
};


template<typename Head, typename Tail>
struct Pair : AbstractPair
{
    Pair(Head h, Tail t) : head(h), tail(t) {}
    
    Head head;
    Tail tail;
};


template<typename Head, typename Tail>
auto make_pair(Head h, Tail t)
{
    return Pair<Head, Tail>(h, t);
}

template<typename Head, typename ...Tail>
auto make_pair(Head head, Tail ...tail)
{
    return Pair<Head, decltype(make_pair(std::declval<Tail>()...))>(head, make_pair(tail...));
}


struct L { L(int l) : l(l) {} int l; };


struct L2 : L { enum { ETH      }; L2(int n) : L(2), n(n) {} int n; };
struct L3 : L { enum { IP4, IP6 }; L3(int n) : L(3), n(n) {} int n; };
struct L4 : L { enum { TCP, UDP }; L4(int n) : L(4), n(n) {} int n; };




template<int> struct Id;


struct ETH  : L2
{
    ETH() : L2(L2::ETH) {}
    
    struct P
    {
        enum { VLAN, PPP };
        
        P(int p) : p(p) {}
        
        int p;
    };
};


struct VLAN : ETH::P { VLAN() : ETH::P(ETH::P::VLAN) {} };
struct PPP  : ETH::P { PPP() : ETH::P(ETH::P::PPP) {} };

struct IP4  : L3 { IP4() : L3(L3::IP4) {} };
struct IP6  : L3 { IP6() : L3(L3::IP6) {} };
struct TCP  : L4 { TCP() : L4(L4::TCP) {} };
struct UDP  : L4 { UDP() : L4(L4::UDP) {} };
    
    
auto create(L2 l2, L3 l3, L4 l4, const char*)
{
    return make_pair(l2, l3, l4);
}

auto create(L2 l2, L3 l3, const char* str)
{
    switch (str[0])
    {
        case 't': return create(l2, l3, UDP(), str + 1);
        case 'u': return create(l2, l3, TCP(), str + 1);
        default: throw "bad l4";
    }
}
    
auto create(L2 l2, const char* str)
{
    switch (str[0])
    {
        case '4': return create(l2, IP4(), str + 1);
        case '6': return create(l2, IP6(), str + 1);
        default: throw "bad l3";
    }
}

auto create(const char* str)
{
    switch (str[0])
    {
        case 'e':
        {
            return create(ETH(), str + 1);
        }
        default: throw "bad l2";
    }
}


int main()
{
    create("e4t");
    create("e6t");
    create("e4u");
    create("e6u");
}