#include <thread>
#include <vector>

struct parallell_for{
    parallell_for(int thread_count=std::thread::hardware_concurrency()) :threads(thread_count-1) {}
    template<class function_type>
    void operator()(int minindex, int maxindex, function_type&& func) {
        int index=minindex;
        operator()(index, [=](int index){return index<maxindex;}, [](int& index){++index;}, std::forward<function_type>(func));
    }
    template<class index_type, class stop_type, class next_type, class function_type>
    void operator()(index_type& index, stop_type&& continue_func, next_type&& inc_func, function_type&& do_func) {
        bool do_continue = continue_func(index);
        if (do_continue==false)
            return;            
        for(int i=0; i<threads.size() && do_continue; i++) {
            threads[i] = std::thread(do_func, index);
            inc_func(index);
            do_continue = continue_func(index);
        }
        if (do_continue) {
            do_func(index);
            inc_func(index);
            do_continue = continue_func(index);            
        }
        while(do_continue) {
            for(int i=0; i<threads.size() && do_continue; i++) {
                if (threads[i].joinable())
                    threads[i].join();
                threads[i] = std::thread(do_func, index);
                inc_func(index);
                do_continue = continue_func(index);
            }
            if (do_continue) {
                do_func(index);
                inc_func(index);
                do_continue = continue_func(index);            
            }
        }
        for(int i=0; i<threads.size(); i++) {
            if (threads[i].joinable())
                threads[i].join();  
        }
    }
private:
    std::vector<std::thread> threads;
};

#include <iostream>
void do_stuff(int index) {std::cout << index << '\n';}

int main() {
    parallell_for{8}(0, 200, do_stuff); //note do_stuff takes the index as a param
}