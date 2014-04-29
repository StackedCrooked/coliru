#include <stdio.h>

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/bind/protect.hpp>

struct foo_then_smile
{
    typedef void result_type;

    template <typename FUNC>
        void operator()(FUNC handler) const {
            handler();
            printf("Smile!\n");
        }
};

void foo(int a, int b, int c) {
    printf("The important answer is %d\n", a + b + c);
}

int main() {
    boost::asio::io_service ioService;

    ioService.post(boost::bind(foo_then_smile(), boost::protect(boost::bind(foo, 1, 2, 3))));

    ioService.run();
}
