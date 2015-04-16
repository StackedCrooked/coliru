
#include <thread>
#include <chrono>
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
using std::condition_variable;
using std::map;
using std::vector;
using std::function;
using std::chrono::milliseconds;
using std::chrono::seconds;


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
			std::unique_lock<std::mutex> lock{ mutex_m };
			stop_m = true;
			pushed_m.notify_one();
		}
		thread_m.join();
	}

	timer_id add(fun_t fun, milliseconds period)
	{
		auto id = next_id;
		++next_id;
		funs_m[id] = { fun, period };

		std::unique_lock<std::mutex> lock{ mutex_m };
		schedule_map.emplace(clock_t::now() + period, id);
		pushed_m.notify_one();

		return id;
	}

	void remove(int id)
	{
		funs_m.erase(id);
	}

	void loop()
	{
		while (true)
		{
			time_point_t scheduled_time;
			vector < timer_id > ids_to_process;

			// pull tasks
			{
				std::unique_lock<std::mutex> lock{ mutex_m };

				while (schedule_map.empty())
				{
					pushed_m.wait(lock);
				}

				if (stop_m)
				{
					break;
				}

				if (schedule_map.empty())
				{
					continue;
				}

				while (clock_t::now() < schedule_map.begin()->first)
				{
					pushed_m.wait_until(lock, schedule_map.begin()->first);
				}

    			if (stop_m)
				{
					break;
				}
                
				if (schedule_map.empty())
				{
					continue;
				}

				scheduled_time = schedule_map.begin()->first;
				auto range = schedule_map.equal_range(scheduled_time);
				std::transform(range.first, range.second, std::back_inserter(ids_to_process),
					[](const schedule_map_t::value_type & p){return p.second; });
				schedule_map.erase(range.first, range.second);
			}

			// process
			for (auto timer_id: ids_to_process)
			{
				funs_m.at(timer_id).fun();
			}

			// reschedule
			{
				std::unique_lock<std::mutex> lock{ mutex_m };

				for (auto timer_id : ids_to_process)
				{
					schedule_map.emplace(scheduled_time + funs_m.at(timer_id).period, timer_id);
				}
			}
		}
	}

private:

	struct timer_data
	{
		fun_t fun;
		milliseconds period;
	};

	timer_id next_id = 0;
	map<timer_id, timer_data> funs_m;
	thread thread_m;

	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using schedule_map_t = std::multimap < time_point_t, timer_id >;

	schedule_map_t schedule_map;

	condition_variable pushed_m;
	std::mutex mutex_m;
	bool stop_m = false;
};

void print(const char * msg)
{
	std::cout << msg << std::endl;
}

int main()
{
	timer_manager tm;

	tm.add([]{print("100ms"); }, milliseconds{ 100 });
	tm.add([]{print("1s"); }, seconds{ 1 });

	std::this_thread::sleep_for(milliseconds{ 10000 });
	return 0;
}
