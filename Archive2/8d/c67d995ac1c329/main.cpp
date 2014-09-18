#include "tbb/task.h"
#include <iostream>
#include <future>



template< class F, class... Args>
auto Async(F&& f) -> std::future<decltype(f())>
{
    typedef decltype(f()) result_type;

    struct Task : tbb::task
    {
        Task(F&& f) : f_(std::forward<F>(f)) {} // is forward correct here?

        virtual tbb::task* execute()
        {
            f_();
            return nullptr;
        }

        std::packaged_task<result_type()> f_;
    };

    auto task = new (tbb::task::allocate_root()) Task(std::forward<F>(f));
    tbb::task::enqueue(*task);
    return task->f_.get_future();
}

struct MoveOnly {
    MoveOnly() {}
    void operator()() {}
    
    MoveOnly(MoveOnly&&) = default;
    MoveOnly& operator=(MoveOnly&&) = default; 
    
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete; 
};

struct CopyOnly {
    CopyOnly() {}
    void operator()() {}
    
    CopyOnly(CopyOnly&&) = delete;
    CopyOnly& operator=(CopyOnly&&) = delete; 
    
    CopyOnly(const CopyOnly&) = default;
    CopyOnly& operator=(const CopyOnly&) = default; 
};

int main()
{
    CopyOnly co;
    MoveOnly mo;

    Async(co).get();
    Async(mo).get();
    
    Async(CopyOnly{}).get();
    Async(MoveOnly{}).get();
}
