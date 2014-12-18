#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>

/*boilerplate crap*/
template<class T>
bool cmp(const ::std::unique_ptr<T>& a, const ::std::unique_ptr<T>&b) {
    return (*a)<(*b);
}

template<class T>
::std::ostream& operator<<(::std::ostream& stream, const ::std::unique_ptr<T>& thing) {
    stream<<*thing;
    return stream;
}

template<class T>
::std::ostream& operator<<(::std::ostream& stream, const ::std::vector<T>& things) {
    bool first = true;
    stream<<"[";
    for(const auto& thing: things) {
        if(!first) { stream<<", "; } else { first = false; }
        stream<<thing;
    }
    stream<<"]";
    return stream;
}

/*example*/
typedef ::std::vector<::std::unique_ptr<int>> MyVec;
typedef ::std::unique_ptr<int> int_up;

MyVec GetPopulatedVec(int n=10) {
    MyVec result;
    for(int i=0;i!=n;i++) {
        result.push_back(int_up(new int(rand()%n)));
    }
    return result;
}

int main()
{
    MyVec test = GetPopulatedVec();
    
    ::std::cout<<test<<"\n";
    sort(test.begin(),test.end(),cmp<int>);
    ::std::cout<<test<<"\n";
}