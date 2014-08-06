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

    SharedPromise() :
        mImpl(std::make_shared<Impl>())
    {
    }

    explicit operator bool() const
    {
        return static_cast<bool>(mImpl);
    }

    std::shared_future<T> get_future()
    {
        assert_valid();
        return mImpl->mSharedFuture;
    }

    void set_value(const T& t)
    {
        assert_valid();

        std::shared_ptr<void> scope_guard(nullptr, [&](void*){
            mImpl.reset();
        });

        mImpl->mPromise.set_value(t);
        for (auto& callback : mImpl->mCallbacks)
        {
            try {
                callback(mImpl->mSharedFuture);
            } catch (...) {
            }
        }
    }

    void set_exception(std::exception_ptr ptr)
    {
        assert_valid();

        std::shared_ptr<void> scope_guard(nullptr, [&](void*){
            mImpl.reset();
        });

        mImpl->mPromise.set_exception(ptr);
    }

    template<typename F>
    void add_callback(F&& f)
    {
        assert_valid();
        mImpl->mCallbacks.push_back(std::forward<F>(f));
    }

private:
    void assert_valid() const
    {
        if (!mImpl)
        {
            throw EmptyPromise();
        }
    }

    struct Impl
    {
        Impl() :
            mPromise(),
            mSharedFuture(mPromise.get_future().share())
        {
        }

        std::promise<T> mPromise;
        std::shared_future<T> mSharedFuture;
        std::vector<std::function<void(std::shared_future<T>&)>> mCallbacks;
    };
    std::shared_ptr<Impl> mImpl;
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
