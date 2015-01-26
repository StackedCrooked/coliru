#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

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

int main(int argc, char *argv[])
{
    auto ff = [](int i, int j) -> noisy { 
        this_thread::sleep_for(chrono::milliseconds(100));    
        return {}; 
    };
    
    auto profiler = make_profiler(ff);
    auto res = profiler(1,2);
    cout << res << " elapsed=" << profiler.elapsed;
}