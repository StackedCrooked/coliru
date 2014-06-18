#include <boost/progress.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>
#include <list>

struct progress_group {
    struct item {
        size_t current, total;
    
        item(size_t total=100, size_t current=0)
            : current(current), total(total) { }

        void tick() 
        {
            if (current < total)
                current++;
        }
    };
    std::list<boost::weak_ptr<progress_group::item> > members;

    void add(boost::shared_ptr<item> pi) {
        assert(pi);
        members.push_back(pi);
    }

    item get_cumulative() {
        item cumul(0, 0);

        for(auto& wpi : members) {
            auto pi = wpi.lock();

            if (pi) {
                cumul.current += pi->current;
                cumul.total   += pi->total;
            }
        }

        return cumul;
    }

};

struct worker {
    explicit worker(size_t count) : count(count) {}

    template <typename L>
    void attachListener(L&& listener) {
        m_callback = std::forward<L>(listener);
    }

    void operator()()
    {
        for (size_t i = 0; i < count; ++i) {
            boost::this_thread::sleep_for(boost::chrono::microseconds(500));
            m_callback();
        }
    }

  private:
    boost::function<void()> m_callback;
    size_t count;
};

struct group_progress_display {

    group_progress_display() : _display(1000), _reentrancy(0) {
    }

    void add(boost::shared_ptr<progress_group::item> pi) {
        _group.add(pi);
    }

    void update() {
        if (1 == ++_reentrancy) // cheap synch
        {
            auto cumul = _group.get_cumulative();

            if (cumul.total > 0)
            {
                size_t target = (1.0 * cumul.current)/cumul.total * _display.expected_count();

                if (target >= _display.count())
                    _display += target - _display.count();
            }
        }
        --_reentrancy;
    }
  private:
    boost::progress_display _display;
    progress_group          _group;
    boost::atomic_int       _reentrancy;
};

int main()
{
    boost::thread_group workers;
    group_progress_display display;

    for (int i = 0; i < 100; ++i)
    {
        auto load = (rand()%5) * 1500;
        auto progress_item = boost::make_shared<progress_group::item>(load);
        display.add(progress_item);

        worker this_worker(progress_item->total);
        this_worker.attachListener([=,&display]{
                progress_item->tick();
                display.update();
            });

        workers.create_thread(this_worker);
    }

    workers.join_all();
}
