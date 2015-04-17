
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>
#include <functional>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <condition_variable>
#include <atomic>

using std::thread;
using std::unique_lock;
using std::transform;
using std::back_inserter;
using std::condition_variable;
using std::map;
using std::vector;
using std::function;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::mutex;
using std::multimap;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
namespace this_thread = std::this_thread;
namespace chrono = std::chrono;

struct timer_manager
{
    typedef function<void()> fun_t;
	using timer_id = int;

	timer_manager()
	{
		thread_m = thread{ [this]{loop(); } };
	}

	~timer_manager()
	{
		{
			unique_lock<mutex> lock{ mutex_m };
			stop_m = true;
			pushed_m.notify_one();
		}
		thread_m.join();
	}

	timer_id add_with_delay(fun_t fun, milliseconds delay)
	{
		return add(fun, milliseconds{ 0 }, delay);
	}

	timer_id add(fun_t fun, milliseconds period)
	{
		return add(fun, period, milliseconds{ 0 });
	}

	void remove(int id)
	{
		unique_lock<mutex> lock{ funs_mutex_m };
		funs_m.erase(id);
	}

private:

	timer_id add(fun_t fun, milliseconds period, milliseconds delay)
	{
		auto id = next_id;
		++next_id;

		auto timer_ptr = make_shared<timer_data>(timer_data{ fun, period });

		{
			unique_lock<mutex> lock{ funs_mutex_m };
			funs_m[id] = timer_ptr;
		}

		{
			unique_lock<mutex> lock{ mutex_m };
			schedule_map.emplace(clock_t::now() + delay, timer_ptr);
			pushed_m.notify_one();
		}

		return id;
	}

	typedef shared_ptr<fun_t> fun_ptr_t;

	void loop()
	{
		while (true)
		{
			time_point_t scheduled_time;
			vector <timer_data_ptr> timers;

			// pull tasks
			{
				unique_lock<mutex> lock{ mutex_m };

				while (!stop_m
					&& (schedule_map.empty() || (clock_t::now() < schedule_map.begin()->first)))
				{
					if (schedule_map.empty())
					{
						pushed_m.wait(lock);
					}
					else
					{
						pushed_m.wait_until(lock, schedule_map.begin()->first);
					}
				}

				if (stop_m)
				{
					break;
				}

				scheduled_time = schedule_map.begin()->first;
				auto range = schedule_map.equal_range(scheduled_time);
				for (auto it = range.first; it != range.second; ++it)
				{
					if (auto locked = it->second.lock())
					{
						timers.push_back(locked);
					}
				}
				schedule_map.erase(range.first, range.second);
			}

			// process
			for (const auto & timer : timers)
			{
				timer->fun();
			}

			// reschedule
			{
				unique_lock<mutex> lock{ mutex_m };

				for (auto timer : timers)
				{
					if (timer->period.count() != 0)
					{
						schedule_map.emplace(scheduled_time + timer->period, timer);
					}
				}
			}
		}
	}

	struct timer_data
	{
		fun_t fun;
		milliseconds period;
	};

	using timer_data_ptr = shared_ptr < timer_data > ;
	using timer_data_weak_ptr = weak_ptr < timer_data >;

	timer_id next_id = 0;
	mutex funs_mutex_m;
	map<timer_id, timer_data_ptr> funs_m;
	thread thread_m;

	using clock_t = chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using schedule_map_t = multimap < time_point_t, timer_data_weak_ptr >;

	schedule_map_t schedule_map;

	condition_variable pushed_m;
	mutex mutex_m;
	bool stop_m = false;
};

template <int value, typename Unit>
void print()
{
	static auto count = 0;
	static auto start = chrono::steady_clock::now();
	std::cout 
		<< count 
		<< "\t" 
		<< (chrono::duration_cast<Unit>(chrono::steady_clock::now() - start).count())
		<< "\t" 
		<< value << "ms" 
		<< std::endl;
	++count;
}

int main()
{
	timer_manager tm;

	tm.add([&]{
		auto id = tm.add(print<200, milliseconds>, milliseconds{ 200 });
		tm.add_with_delay([&,id]{tm.remove(id);}, milliseconds{ 500 });		
	}, seconds{ 1 });

	this_thread::sleep_for(milliseconds{ 10000 });
	return 0;
}
