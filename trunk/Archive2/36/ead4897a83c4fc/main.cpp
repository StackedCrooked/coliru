
#include <memory>

class foo
{
    public:
		foo();

	private:
		class impl;
        struct impl_deleter
        {
            void operator()( impl * ) const;
        };
		std::unique_ptr<impl,impl_deleter> pimpl;
};


// foo.cpp - implementation file

class foo::impl
{
	public:
		void do_internal_work()
		{
			internal_data = 5;
		}

	private:
		int internal_data = 0;
};
void foo::impl_deleter::operator()( impl * ptr ) const
{
    delete ptr;
}

foo::foo()
	: pimpl{new impl}
{
	pimpl->do_internal_work();
}


int main()
{
   
}
