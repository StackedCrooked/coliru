#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <boost/exception/exception.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/move/iterator.hpp>
#include <boost/phoenix.hpp>
#include <boost/thread.hpp>
#include <boost/config.hpp>

#include <unordered_set>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <ostream>
#include <cstddef>
#include <string>
#include <vector>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>

// _____________________[CONFIGURATION]________________________ //
namespace async_lib = std;
const bool work_is_sleep = false;
// ____________________________________________________________ //

using namespace std;
using boost::phoenix::arg_names::arg1;
using boost::thread_specific_ptr;
using boost::back_move_inserter;
using boost::type_name;
using boost::count_if;
using boost::copy;

template<typename Mutex>
unique_lock<Mutex> locker(Mutex &m)
{
    return unique_lock<Mutex>(m);
}

void do_work()
{
    if(work_is_sleep)
    {
        this_thread::sleep_for( chrono::milliseconds(20) );
    }
    else
    {
        volatile double result=0.0;
        for(size_t i=0; i!=1<<22; ++i)
            result+=0.1;
    }
}

int main()
{
    typedef thread::id TID;
    typedef async_lib::future<TID> FTID;

    unordered_set<TID> tids, live_tids;
    vector<FTID> ftids;
    vector<int> live_tids_count;
    async_lib::mutex m;
    generate_n
    (
        back_move_inserter(ftids), 64*thread::hardware_concurrency(),
        [&]()
        {
            return async_lib::async([&]() -> TID
            {
                static thread_specific_ptr<bool> fresh;
                if(fresh.get() == nullptr)
                    fresh.reset(new bool(true));
                TID tid = this_thread::get_id();
                locker(m),
                    live_tids.insert(tid),
                    live_tids_count.push_back(int(live_tids.size()) * (*fresh ? -1 : 1));
                do_work();
                locker(m),
                    live_tids.erase(tid);
                *fresh = false;
                return tid;
            });
        }
    );
    transform
    (
        begin(ftids), end(ftids),
        inserter(tids, tids.end()),
        [](FTID &x){return x.get();}
    );

    cout << "Compiler = " << BOOST_COMPILER                             << endl;
    cout << "Standard library = " << BOOST_STDLIB                       << endl;
    cout << "Boost = " << BOOST_LIB_VERSION                             << endl;
    cout << "future type = " << type_name<FTID>()                       << endl;
    cout << "Only sleep in do_work = " << boolalpha << work_is_sleep    << endl;
    cout << string(32,'_')                                              << endl;
    cout << "hardware_concurrency = " << thread::hardware_concurrency() << endl;
    cout << "async count = " << ftids.size()                            << endl;
    cout << "unique thread id's = " << tids.size()                      << endl;
    cout << "live threads count (negative means fresh thread):"                ;
    copy(live_tids_count, ostream_iterator<int>(cout," "));        cout << endl;
    cout << "fresh count = " << count_if(live_tids_count, arg1 < 0)     << endl;
}
