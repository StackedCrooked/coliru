
#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include <cstdint>

#include <iostream>

template <typename T>
class concurrent_queue
{
public:
    typedef T value_type;

private:
	mutable std::mutex m_;
	mutable std::condition_variable cv_;
	std::queue<value_type> q_;

public:
	void push(const value_type& value)
	{
		std::lock_guard<std::mutex> lock(m_);

		q_.push(value);
		cv_.notify_one();
	}

	void push(value_type&& value)
	{
		std::lock_guard<std::mutex> lock(m_);

		q_.push(std::move(value));
		cv_.notify_one();
	}

	bool try_pop(value_type& var)
	{
		std::lock_guard<std::mutex> lock(m_);

		if (!q_.empty())
		{
			var = std::move(q_.front());
			q_.pop();
			return true;
		}

		return false;
	}

	value_type pop()
	{
		std::unique_lock<std::mutex> lock(m_);
		cv_.wait(lock, [this] { return !q_.empty();  });

		auto value = std::move(q_.front());
		q_.pop();

		return value;
	}
};

class thread_pool
{
	std::vector<std::thread> threads_;
	concurrent_queue<std::function<void()>> job_queue_;
	std::atomic_bool stop_;

public:
	thread_pool(std::uint16_t number_of_threads)
		: threads_(number_of_threads)
	{
		for (auto& t : threads_)
		{
			t = std::thread([this] {
				while (!stop_)
				{
					auto job = job_queue_.pop();
					try { job(); }
					catch (...) {}
				}
			});
		}
	}

	~thread_pool()
	{
		if (!stop_)
		{
			stop();
			detach();
		}
	}

	void run(std::function<void()> job)
	{
		job_queue_.push(std::move(job));
	}

	void stop()
	{
		stop_ = true;
		for (std::size_t i = 0; i != threads_.size(); ++i)
			job_queue_.push([] {});
	}

	void join()
	{
		for (auto& t : threads_)
			t.join();
	}

	void detach()
	{
		for (auto& t : threads_)
			t.detach();
	}
};

int main()
{
    std::cout << "Hello, Threads: ";
    
	thread_pool tp(8);

	std::atomic_int c;
	c = 0;

	for (int i = 0; i != 77; ++i)
		tp.run([&] { ++c; });

	tp.run([&] { tp.stop();  });
	tp.join();

	std::cout << c << '\n';
}
