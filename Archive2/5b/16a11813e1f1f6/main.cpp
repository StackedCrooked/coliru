#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <stdexcept>


template <typename T>
class future;

template <typename T>
class promise;

namespace detail {
    
	template <typename T>
	struct future_shared_state
	{
	public:
		future_shared_state()
			: error(0)
		{};
		
		void wait(boost::mutex& mutex) const
		{
			// http://stackoverflow.com/a/16909012/560648
			boost::mutex::scoped_lock lock(mutex, boost::adopt_lock);
			while (!(state || error))
				available.wait(lock);
		}

		T& get()
		{
			if (state)
				return *state;
			
			if (error)
				throw *error;
			
			throw std::runtime_error("WTF");
		}

		template <typename U>
		void set_value(const U& value)
		{
			state = value;
			available.notify_all();
		}
		
		void set_exception(std::exception* e)
		{
			error = e;
			available.notify_all();
		}

	private:
		mutable boost::condition_variable available;
		boost::optional<T> state;
		std::exception* error;
		
		friend class promise<T>;
		friend class future<T>;
		boost::mutex lock;
	};
	
}

template <typename T>
struct future
{
public:
	future() {}
	~future() {}
	
	T get()
	{
		boost::mutex::scoped_lock lock(box->lock);
		box->wait(box->lock);
		return box->get();
	}
	
	bool valid() const
	{
		return !!box;
	}
	
	void wait() const
	{
		boost::mutex::scoped_lock lock(box->lock);
		box->wait(box->lock);
	}

private:
	boost::shared_ptr<detail::future_shared_state<T> > box;
	
	friend class promise<T>;
	future(boost::shared_ptr<detail::future_shared_state<T> > const& box) : box(box) {}
	
	//future(future const& other); // disable
	//future& operator=(future const& other); // disable
};

template <typename T>
struct promise
{
public:
	promise() : box(new detail::future_shared_state<T>) {}
	~promise() {}	
	
	void swap(promise& other)
	{
		box.swap(other.box);
	}
	
	future<T> get_future()
	{
		return future<T>(box);
	}
	
	void set_value(T const& value)
	{
		boost::mutex::scoped_lock l(box->lock);
		box->set_value(value);
	}
	
	void set_exception(std::exception* e)
	{
		boost::mutex::scoped_lock l(box->lock);
		box->set_exception(e);
	}

private:
	boost::shared_ptr<detail::future_shared_state<T> > box;
	
	//promise(promise const& other); // disable
	//promise& operator=(promise const& rhs); // disable
};

template<typename T>
void swap(promise<T>& lhs, promise<T>& rhs)
{
	lhs.swap(rhs);
}

