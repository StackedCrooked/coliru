#include <algorithm>
#include <array>
#include <functional>
#include <thread>
#include <vector>

template < class InputIterator, class OutputIterator >
void evaluate( InputIterator first, InputIterator last, OutputIterator outfirst ) {
    while( first != last ) {
        *outfirst++ = (*first++) / 2 ;
    }
}

template < int num_t = 4 >
struct ParallelEvaluator {

    template< typename InputContainer , typename OutputContainer >
    static void eval(InputContainer const & src, OutputContainer & dst) {
        std::array<std::thread, num_t> threads;
        auto bg = src.begin() ;
        auto bg_r = dst.begin() ;
        for ( int i = 0 ; i < num_t ; i++ ) {
            threads[i] = std::thread(evaluate<decltype(bg),decltype(bg_r)>
                                     ,bg,bg+4,bg_r);
            bg = bg+4 ;
            bg_r = bg_r + 4 ;
        }
        std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));
    }
};


int main()
{
    std::vector<int> t = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15} ;
    std::vector<int> v(16) ;

    ParallelEvaluator<4>::eval(t,v) ;
}
