#include <functional>
#include <memory>

#include<stdio.h>
#include<stdlib.h>

struct dispatcher_t {};
struct binder_t {};

struct factories_t
{
    std::function< std::unique_ptr< dispatcher_t >(int/* here is params*/) > m_disp_factory;
	std::function< std::unique_ptr< binder_t >(int) > m_bind_factory;
};

std::unique_ptr< dispatcher_t >create_dispatcher()
{
	return std::unique_ptr< dispatcher_t >(new dispatcher_t());
}

std::unique_ptr< binder_t > create_binder()
{
	return std::unique_ptr< binder_t >(new binder_t());
}

int main(int argn,char**argv)
{
	struct {
		int a;
		int b;
	}b = { 3, 5 };

	factories_t f{
		[b/*here is capture-list*/](int a/* here is params*/) { printf("%d----%d\n", a, b.a); return create_dispatcher(); },
		[&b](int a) { printf("%d----%d\n",a,b.a); return create_binder(); }
	};
	/**
	 * reference:http://en.cppreference.com/w/cpp/language/lambda
	 */

	b.a = 1000;
	f.m_disp_factory(3333); 
	f.m_bind_factory(3333);
	return 0;
}

