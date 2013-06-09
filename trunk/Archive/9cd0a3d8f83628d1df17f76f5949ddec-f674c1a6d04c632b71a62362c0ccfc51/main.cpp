#include <thread>
#include <vector>
#include <deque>
#include <functional>
#include <iostream>
#include <sstream>
#include <thread>
#include <future>
#include <atomic>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <cstring>


class task
{
public:
    enum state
    {
        init,
        done,
        cancelled
    };
private:
    bool m_detached;
    state m_state;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
    std::function<void()> m_func;
public:
    // constructor
    template<class F,  class ...Args>
    task(const F& f, Args ...args):
        m_detached(false),
        m_state(init),
        m_func(std::bind(f, args...))
    {
    }

    task(const task& t):
        m_detached(t.m_detached),
        m_state(t.m_state),
        m_func(t.m_func)
    {
    }

    task(const task&& t):
        m_detached(std::move(t.m_detached)),
        m_state(std::move(t.m_state)),
        m_func(std::move(t.m_func))
    {
    }

    // A detached task will delete itself after execution or cancellation.
    void detach(bool det = true)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_detached = det;
    }

    // Returns true if task is m_detached.
    bool detached() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_detached;
    }

    // Cancels the task.
    void cancel()
    {
        if(detached())
        {
            delete this;
        }
        else
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_state = cancelled;
            m_cond.notify_all();
        }
    }

    // Runs the task in the current thread.
    // The task is deleted afterwards if it is detached.
    void run()
    {
        m_func();

        if(detached())
        {
            delete this;
        }
        else
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_state = done;
            m_cond.notify_all();
        }
    }

    // Waits for the task to be done or cancelled.
    state wait()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        while(m_state == init)
        {
            m_cond.wait(lock);
        }

        return m_state;
    }
};

class thread_pool
{
    bool m_quit;
    int m_num;
    int m_idle;

    std::vector<std::thread> m_threads;
    std::deque<task*> m_queue;

    typedef std::mutex mutex_type;

    mutable mutex_type m_mutex;
    std::condition_variable m_cond;

    void worker()
    {
        while(1)
        {
            std::unique_lock<mutex_type> lock(m_mutex);

            ++m_idle;

            while(!m_quit && m_queue.empty())
            {
                m_cond.wait(lock); // wait for quit signal or data in queue
            }

            if(m_quit) return;

            task* t = m_queue.front();
            m_queue.pop_front();
            --m_idle;
            lock.unlock();

            t->run();
        }
    }

public:
    thread_pool(int num_threads):
        m_quit(false),
        m_num(num_threads),
        m_idle(0)
    {
        std::lock_guard<mutex_type> lock(m_mutex);

        // create worker threads
        for(int i = 0; i < m_num; ++i)
        {
            m_threads.emplace_back(std::thread(&thread_pool::worker, this));
        }
    }

    ~thread_pool()
    {
        // notify worker threads to stop
        std::unique_lock<mutex_type> lock(m_mutex);
        m_quit = true;
        m_cond.notify_all();
        lock.unlock();

        for(auto &i: m_threads) i.join(); // join worker threads

        for(auto &i: m_queue) i->cancel(); // cancel remaining tasks
    }

    void schedule(task* t)
    {
        std::unique_lock<mutex_type> lock(m_mutex);

        m_queue.push_back(t);
        m_cond.notify_one();
    }

    bool try_run(task* t)
    {
        std::unique_lock<mutex_type> lock(m_mutex);

        if(m_idle < 1)
        {
            return false;
        }
        else
        {
            m_queue.push_back(t);
            m_cond.notify_one();
            return true;
        }
    }

    int num_pending() const
    {
        std::lock_guard<mutex_type> lock(m_mutex);

        return m_queue.size();
    }

    int num_idle() const
    {
        std::lock_guard<mutex_type> lock(m_mutex);

        return m_idle;
    }


};

struct Sudoku;

bool Solve(Sudoku&, int, int&);

struct Sudoku
{
    int fields[9][9] = {};

    int& Field(int x, int y)
    {
        return fields[y][x];
    }

    int Field(int x, int y) const
    {
        return fields[y][x];
    }

    static void CalcPos(int field, int& x, int& y)
    {
        x = field % 9;
        y = field / 9;
    }

    bool CheckField(int x, int y) const
    {
        int val = fields[y][x];

        for(int i = 0; i < 9; ++i)
        {
            if(i != x && fields[y][i] == val) return false;

            if(i != y && fields[i][x] == val) return false;

            int block_y = y / 3 * 3 + i / 3;
            int block_x = x / 3 * 3 + i % 3;

            if(block_y != y && block_x != x && fields[block_y][block_x] == val) return false;
        }

        return true;
    }

    static Sudoku MakeRandom()
    {
        int iter;

        while(1)
        {
            Sudoku s;

            for(int i = 0; i < 20; ++i)
            {
                s.Field(std::rand() % 9, std::rand() % 9) = std::rand() % 9 + 1;
            }

            for(int i = 0; i < 81; ++i)
            {
                int x, y;
                Sudoku::CalcPos(i * 14 % 81, x, y);

                if(!s.CheckField(x, y)) s.Field(x, y) = 0;
            }

            Sudoku s2(s);

            if(Solve(s2, 0, iter)) return s;
        }
    }
};

inline std::istream& operator >> (std::istream& is, Sudoku& sud)
{
    int n = 0;
    int data[81] = {};

    while(is && n < 81)
    {
        char c = is.get();

        if(c >= '1' && c <= '9')
        {
            data[n++] = c - '0';
        }
        else if(c == '.' || c == '0')
        {
            data[n++] = 0;
        }
        else
        {
            continue;
        }
    }

    if(n == 81)
    {
        std::memcpy(sud.fields, data, sizeof(int) * 81);
    }

    return is;
}

inline std::ostream& operator << (std::ostream& os, const Sudoku& sud)
{
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(sud.Field(j, i) != 0) os << sud.Field(j, i);
            else os << '.';

            if(j==2 || j == 5)
            {
                os << " | ";
            }
            else if(j == 8)
            {
                os << '\n';
            }
            else
            {
                os << ' ';
            }
        }

        if(i == 2 || i == 5) os << "- - -   - - -   - - -\n";
    }

    return os;
}

namespace detail
{

void Solve(bool& ok, Sudoku& s, int field, int start, int end, std::atomic_bool& abort, thread_pool& tp)
{
    if(field >= 81)
    {
        ok = true;
        abort.store(true);
        return;
    }

    if(start == end)
    {
        ok = false;
        abort.store(true);
        return;
    }

    int x, y;
    Sudoku::CalcPos(field, x, y);

    if(s.Field(x, y) != 0)
    {
        Solve(ok, s, field + 1, start, end, abort, tp);
        return;
    }

    int old = s.Field(x, y);

    for(int i = start; i != end; ++i)
    {
        // check if other thread has found solution
        if(abort.load())
        {
            ok = false;
            return;
        }


        s.Field(x, y) = i;

        if(!s.CheckField(x, y)) continue;

        Sudoku s_copy1(s);
        Sudoku s_copy2(s);

        bool ok1(false), ok2(false);
        std::atomic_bool abort2(false);
        int mid = std::rand() < RAND_MAX / 2 ? 4 : 5;

        task t1(Solve, std::ref(ok1), std::ref(s_copy1), field + 1, 1,  mid, std::ref(abort2), std::ref(tp));

        if(!tp.try_run(&t1))
        {
            t1.run();
        }

        Solve(ok2, s_copy2, field + 1, mid, 10, abort2, tp);

        t1.wait();


        if(ok1)
        {
            abort.store(true);
            s = s_copy1;
            ok = true;
            return;
        }

        if(ok2)
        {
            abort.store(true);
            s = s_copy2;
            ok = true;
            return;
        }
    }

    s.Field(x, y) = old;

    ok = false;
    return;
}

}

inline bool Solve(Sudoku& s)
{
    int ncpu = 8;
    thread_pool tp(ncpu - 1);
    std::cout << "CPU count: " <<  ncpu << '\n';
    std::atomic_bool abort(false);
    bool ok;

    detail::Solve(ok, s, 0, 1, 10, abort, tp);

    return ok;
}
int main()
{

    std::srand(std::time(nullptr));

    std::stringstream input
    (
        "1 2 . | 4 . . | 3 . .  "
        "3 . . | . 1 . | . 5 .  "
        ". . 6 | . . . | 1 . .  "
        "-------+-------+------ "
        "7 . . | . 9 . | . . .  "
        ". 4 . | 6 . 3 | . . .  "
        ". . 3 | . . 2 | . . .  "
        "-------+-------+------ "
        "5 . . | . 8 . | 7 . .  "
        ". . 7 | . . . | . . 5  "
        ". . . | . . . | . 9 8  "
    );

    Sudoku s;
    input >> s;

    bool ok = Solve(s);

    std::cout << "Solved: " << ok << '\n';
    std::cout << s;
}

