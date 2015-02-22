#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

class syncstream : public std::ostringstream
{
public:
    using std::ostringstream::ostringstream;

    syncstream& operator<<(std::ostream&  (*pf)(std::ostream&) ) { pf(*this); return *this; }
    syncstream& operator<<(std::ios&      (*pf)(std::ios&)     ) { pf(*this); return *this; }
    syncstream& operator<<(std::ios_base& (*pf)(std::ios_base&)) { pf(*this); return *this; }

    template<typename T>
    syncstream& operator<<(T&& token)
    {
        static_cast<std::ostringstream&>(*this) << std::forward<T>(token);
        return *this;
    }
};

inline std::ostream& operator&&(std::ostream& s, const syncstream& g) { return s << g.str(); }

#define synced(stream) stream && syncstream()

////////////////////////////////////////////////////////////////////////////////////////////////////
void proc(int n)
{
    synced(std::cout) << "Hello" << ' ' << "world" << ' ' << "from" << ' ' << "thread" << ' ' << n << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(true);

    std::vector<std::thread> threads;
    for(int n = 0; n < 1000; ++n) threads.push_back(std::thread(std::bind(proc, n)));

    for(std::thread& thread: threads) thread.join();
    return 0;
}
