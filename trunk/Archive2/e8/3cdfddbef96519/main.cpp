#include <boost/thread.hpp>

namespace detail {

    template <typename T>
    struct future_shared_state
    {
    public:

        void wait() const
        {
            boost::mutex::scoped_lock lock(m);
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
            {
                boost::mutex::scoped_lock lock(m);
                state = value;
            }
            available.notify_all();
        }

        void set_exception(boost::shared_ptr<std::exception> e)
        {
            {
                boost::mutex::scoped_lock lock(m);
                error = e;
            }
            available.notify_all();
        }

    private:
        mutable boost::condition_variable available;
        boost::optional<T> state;
        boost::shared_ptr<std::exception> error;

        mutable boost::mutex m;
    };

}

template <typename T>
class promise;

template <typename T>
struct future
{
public:
    future() {}
    ~future() {}

    T get()
    {
        boost::shared_ptr<detail::future_shared_state<T> > old_box;
        swap(box, old_box);

        old_box->wait();
        return old_box->get();
    }

    bool valid() const
    {
        return !!box;
    }

    void wait() const
    {
        boost::mutex::scoped_lock lock(box->m);
        box->wait(box->m);
    }

private:
    boost::shared_ptr<detail::future_shared_state<T> > box;

    friend class promise<T>;
    future(boost::shared_ptr<detail::future_shared_state<T> > const& box) : box(box) {}
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
        box->set_value(value);
    }

    void set_exception(boost::shared_ptr<std::exception> e)
    {
        box->set_exception(e);
    }

private:
    boost::shared_ptr<detail::future_shared_state<T> > box;
};

template<typename T>
void swap(promise<T>& lhs, promise<T>& rhs)
{
    lhs.swap(rhs);
}

#include <iostream>
#include <boost/thread.hpp>

void foo(promise<unsigned int> p)
{
    sleep(1);
    p.set_value(42);
}

int main()
{
    promise<unsigned int> p;
    future <unsigned int> f(p.get_future());

    boost::thread t(&foo, p);
    std::cout << f.get() << std::endl;

    t.join();
}
