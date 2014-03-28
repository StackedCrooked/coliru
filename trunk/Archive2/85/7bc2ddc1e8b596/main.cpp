#include <boost/test/unit_test.hpp>

template<typename T,typename Cmp>
class queue{
public:
    queue(Cmp c):cmp(c){};
    void push(T a){
        cmp(a,a);
    }
    Cmp cmp;

};

template<typename T>
void fun(T a){
    class decreasing_order
    {
    public:
        decreasing_order(std::vector<T>  BBB):AAA(BBB) {}
        std::vector<T>  AAA;
        bool operator() (const T & lhs, const T & rhs) const
        {
            return AAA[lhs]<AAA[rhs];
        }
    };
    std::vector<T> tab;
    // queue<T,  decreasing_order >uncoveredSetQueue((decreasing_order(tab)));/*1*/
    queue<T,  decreasing_order >uncoveredSetQueue( decreasing_order(tab) );/*2*/
    uncoveredSetQueue.push(a);

}

BOOST_AUTO_TEST_CASE(TestX) {
    fun(1);
}
