#include <iostream>
using namespace std;

template<class T>
class iter: public std::iterator<std::random_access_iterator_tag, T>{
private:
    T* m_pter;

public:

    iter(T* value):  m_pter(value){}
    iter(const iter& other_it): m_pter(other_it.m_pter){}
    iter& operator++() { ++m_pter; return *this; }
    bool operator!=(const iter& rhs) {return m_pter!=rhs.m_pter;}
    T& operator*() { return *m_pter; }

};


int main(){

    int a[]  = {1,2,3,4,5,6};
    iter<int> from(a);
    iter<int> to(a+5);
    for (iter<int> iter = from; iter != to; ++iter) {
        std::cout << *iter << std::endl;
    }

    // std::vector<int> a  = {1,2,3,4,5,6};
    // iter<std::vector<int> > from(a);
    // iter<std::vector<int> > to(a+5);
    // for (iter<std::vectorVECTOR<int> > iter=from; iter!=to; ++iter) {
    //     std::cout << *iter << std::endl;
    // }

}
