#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>

struct poster {
    typedef void result_type;

    poster(boost::asio::io_service& ios) : ios_(ios) {}
    boost::asio::io_service& ios_;

    template<typename F> void operator()(F const& f) const {
        ios_.post(f);
    }

    template<typename F> void operator()(F&& f) const {
        ios_.post(std::move(f));
    }
};

class MyClass
{
public:
        MyClass() : work_(ios_)
        {
        }

        ~MyClass() {}

        void func(int arg1, int arg2)
        {
            std::cout << arg1 << " " << arg2 << std::endl;
        }

        void test()
        {
#if 2
            // clumsy workaround
            auto nested = boost::protect(boost::bind(&MyClass::func, this, 7, 42));
            typedef decltype(nested) actual_t; // _bi::protected_bind_t<bind_t<void, mf2<void, MyClass, int, int>, list3<value<MyClass *>, value<int>, value<int> > > >
            typedef void (boost::asio::io_service::*pmf)(actual_t const&);
            
            boost::bind(static_cast<pmf>(&boost::asio::io_service::post), &ios_, nested);
#else
            // more elegant TMP solution
            boost::bind(poster(ios_), boost::protect(boost::bind(&MyClass::func, this, 7, 42)));
#endif
        }

private:
        boost::asio::io_service ios_;
        boost::asio::io_service::work work_;
};


int main()
{
    MyClass obj;
    obj.test();
}
