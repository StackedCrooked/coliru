#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

struct noisy 
{
    noisy() = default;
    noisy(const noisy&) { cout << "copy" << endl; }
    noisy(noisy&&) { cout << "move" << endl; }
    
};

ostream& operator<<(ostream& os, const noisy&)
{
    return os << "N";
}

template<typename Fun, typename... Args>
auto profile_in_ms(Fun&& fun, Args&& ... args)
{
    auto tic = chrono::high_resolution_clock::now();
    auto&& res = forward<Fun>(fun)(forward<Args>(args)...);
    cout << "qui" << endl;
    auto toc = chrono::high_resolution_clock::now();
    return make_pair(chrono::duration_cast<chrono::milliseconds>(toc-tic).count(), move(res));
}

template<typename Fun>
struct profile_wrapper
{
    struct time_guard
    {
        ~time_guard()
        {
            _w->elapsed = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - _w->tic).count();
        }
        
        profile_wrapper* _w;
    };
    
    profile_wrapper(Fun&& f)
        :   _f{forward<Fun>(f)}, tic{}
    {
                
    }
    
    template<typename... Args>
    decltype(auto) operator()(Args&&... args)
    {
        tic = chrono::high_resolution_clock::now();
        time_guard guard {this};
        return _f(forward<Args>(args)...);
    }
    
    chrono::high_resolution_clock::time_point tic;
    size_t elapsed;
    Fun _f;
};

template<typename Fun>
profile_wrapper<Fun> make_profiler(Fun&& fun)
{
    return {forward<Fun>(fun)};
}

template<typename Log, typename Fun, typename... Args>
decltype(auto) prof(Log&& log, Fun&& fun, Args&&... args)
{
    struct on_exit
    {
        on_exit(Log logFn)
            : tic(high_resolution_clock::now()), _log(logFn)
        {
            
        }
        
        ~on_exit()
        {
            auto elapsed = high_resolution_clock::now() - tic;
            _log(duration_cast<milliseconds>(elapsed).count());
        }
        
        high_resolution_clock::time_point tic;
        Log _log;
    };
    
    on_exit _guard{forward<Log>(log)};
    return forward<Fun>(fun)(forward<Args>(args)...);
}

int main(int argc, char *argv[])
{
    auto ff = [](int i, int j) -> noisy { 
        this_thread::sleep_for(chrono::milliseconds(100));    
        return {}; 
    };
    
    auto profiler = make_profiler(ff);
    auto res = profiler(1,2);
    cout << res << " elapsed=" << profiler.elapsed << endl;
    
    auto res2 = prof([](auto e){ cout << "elapsed=" << e; }, ff, 1, 2);
}