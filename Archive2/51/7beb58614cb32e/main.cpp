#include <cassert>
#include <iostream>
#include <future>
#include <functional>
#include <vector>


template<typename T>
struct SharedPromise
{
    struct EmptyPromise : virtual std::exception
    {
        const char* what() const noexcept
        {
            return "EmptyPromise";
        }
    };


    SharedPromise() : impl_(std::make_shared<Impl>()) { }

    explicit operator bool() const
    {
        return static_cast<bool>(impl_);
    }

    std::shared_future<T> get_future()
    {
        assert_valid();
        return impl_->fut;
    }

    void set_value(const T& t)
    {
        assert_valid();

        std::shared_ptr<void> scope_guard(nullptr, [&](void*){
            impl_.reset();
        });

        impl_->prom.set_value(t);
        for (auto& callback : impl_->callbacks)
        {
            try { callback(impl_->fut); }
            catch (...) { }
        }
    }

    void set_exception(std::exception_ptr ptr)
    {
        assert_valid();

        std::shared_ptr<void> scope_guard(nullptr, [&](void*){
            impl_.reset();
        });

        impl_->prom.set_exception(ptr);
    }

    template<typename F>
    void add_callback(F&& f)
    {
        assert_valid();
        impl_->callbacks.push_back(std::forward<F>(f));
    }

private:
    void assert_valid() const
    {
        if (!impl_) { throw EmptyPromise(); }
    }

    struct Impl
    {
        Impl() : fut(prom.get_future().share()) { }
        std::promise<T> prom;
        std::shared_future<T> fut;
        std::vector<std::function<void(std::shared_future<T>&)>> callbacks;
    };

    std::shared_ptr<Impl> impl_;
};


int main()
{
    SharedPromise<int> prom;

    assert(prom);

    prom.add_callback([](std::shared_future<int>& fut) {
        std::cout << fut.get() << std::endl;
    });

    prom.add_callback([](std::shared_future<int>& fut) {
        std::cout << "Really " << fut.get() << std::endl;
    });

    auto future = prom.get_future();

    prom.set_value(1);
    assert(!prom);

    std::cout << future.get() << std::endl;

    try
    {
        prom.set_value(2);
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

