#include <array>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>

struct KnuthSeq {
    int operator()(int i) {
        static int seqElems_[] = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841,
                295214, 88573, 265720, 797161, 2391484, 7174453, 21523360, 64570081,
                193710244, 581130733, 1743392200};
        return seqElems_[i];
    }
};

template<typename Iterator, typename Sequence, typename Predicate>
void shellSort(Iterator begin, Iterator end, Sequence strideSeq, Predicate pred)
{
        int numElems = std::distance(begin, end);
        int startIndex = 0;
        while(strideSeq(startIndex + 1) < numElems)
        {
                startIndex++;
        }

        recursiveShellSort(begin, end, strideSeq, pred, numElems, startIndex);
}
template<typename Iterator, typename Predicate>
void hSort(Iterator begin, Iterator end, int stride, Predicate pred)
{
        for(Iterator it = begin + stride; it != end; ++it)
        {
                for(Iterator lhs = it; lhs - begin >= stride;)
                {
                        Iterator rhs = lhs;
                        lhs -= stride;
                        if(!pred(*lhs, *rhs))
                        {
                                std::iter_swap(lhs, rhs);
                        }
                }
        }
}

template<typename Iterator, typename Sequence, typename Predicate>
void recursiveShellSort(Iterator begin, Iterator end, Sequence strideSeq, Predicate pred, int numElems, int index)
{
        hSort(begin, end, strideSeq(index), pred);

        if(index > 0)
                recursiveShellSort(begin, end, strideSeq, pred, numElems, index - 1);
}

void do_test(std::vector<int> a)
{
    for(unsigned i=0; i<a.size(); ++i)
        std::cout << a[i] << " ";
    std::cout << "-> ";
    shellSort(a.begin(), a.end(), KnuthSeq(), std::less<int>());
    if (std::is_sorted(a.begin(), a.end()))
        std::cout << "pass\n";
    else {
        for(unsigned i=0; i<a.size(); ++i)
            std::cout << a[i] << " ";
        std::cout << "fail\n";
    }
}

int main() {
    //do_test({}); //segfault
    do_test({0});
    do_test({0, 0});
    do_test({0, 1});
    do_test({1, 0});
    do_test({0, 0, 0});
    do_test({0, 0, 1});
    do_test({0, 1, 0});
    do_test({1, 0, 0});
    do_test({0, 1, 1});
    do_test({1, 0, 1});
    do_test({1, 1, 0});
    do_test({0, 1, 2});
    do_test({0, 2, 1});
    do_test({1, 0, 2});
    do_test({1, 2, 0});
    do_test({2, 0, 1});
    do_test({2, 1, 0});
}
