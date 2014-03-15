#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <assert.h>
using namespace std;
template<class Container, class Iterator> 
size_t position(Container&& c, Iterator pos){
    return size_t(distance(begin(c), pos));
}
template<class Container, class Iterator, class Iterator2> 
string sposition(Container&& c, const pair<Iterator, Iterator2>& pos){
    ostringstream r;
    r << "(" << position(c, pos.first) << ", " << position(c, pos.second) << ")";
    return r.str();
}
template<class Container, class Value> 
pair<typename remove_reference<Container>::type::iterator, typename remove_reference<Container>::type::iterator>
 binary_search(Container&& source, const Value& item){
    assert(is_sorted(begin(source), end(source)));
    const auto empty = make_pair(source.end(), source.end());
    auto l = begin(source), r=end(source), m=l;
    while(true){
        if(l==r)
            return empty;
        const auto lr = distance(l,r);
        m = next(l, lr/2);
        if(*m<item)
            l = m;
        if(*m>item)
            r = m;
        if(*m==item)
            break;
        if(l!=r && next(l)==r)
            return empty;
    }
    cout<<"part1"<<endl;
    auto l1=l, r1=m, l2=m, r2=r;
    while(true){
        const auto lr1 = distance(l1, r1);
        m = next(l1, lr1/2);
        if(*m<item)
            l1 = m;
        if(*m>=item)
            r1 = m;
        if(l1==r1 || (*l1<item && *r1>=item))
            break;
    }
    cout<<"part2"<<endl;
    while(true){
        const auto lr2 = distance(l2, r2);
        m = next(l2, lr2/2);
        if(*m<=item)
            l2 = m;
        if(*m>item)
            r2 = m;
        if(l2==r2 || (*l2>=item && (r==r2 || *r2>item)))
            break;
    }
    cout<<"part3"<<endl;
    return {r1, next(l2)};
}
int main(){
    vector<int> s{5,7,7,7,9,19,23};
    list<int> s2(s.begin()+1, s.end());
    cout<<sposition(s, binary_search(s, 7))<<endl;
    cout<<sposition(s2, binary_search(s2, 7))<<endl;
    cout<<sposition(s, binary_search(s, 9))<<endl;
    cout<<sposition(s, binary_search(s, 5))<<endl;
    cout<<sposition(s, binary_search(s, 23))<<endl;
    cout<<sposition(s, binary_search(s, 0))<<endl;
    vector<int> e;
    cout<<sposition(e, binary_search(e, 0))<<endl;
    cout<<sposition(s, binary_search(s, 25))<<endl;
    cout<<sposition(s, binary_search(s, 10))<<endl;
    return 0;
}
