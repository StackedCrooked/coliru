#include <boost/timer/timer.hpp>

int do_stuff(int arg, bool & e)
{
    if (arg == 3333)
	{
		e = true;
		return 0; // error
	}
	else
	{
		e = false;
		return arg + 1;
	}
}

int do_stuff(int arg)
{
	if (arg == 3333)
		throw std::runtime_error("argh!");
	return arg + 1;
}

void outparam()
{
	std::cout << "Out Parameter" << std::endl;
	boost::timer::auto_cpu_timer t;
	for (int i = 0; i < 0x7fffffff; ++i)
	{
		bool error = false;
		int result = do_stuff(i, error);
		if (error)
			std::cout << "Error at " << i << std::endl;
	}
}

void exceptions()
{
	std::cout << "Exceptions" << std::endl;
	boost::timer::auto_cpu_timer t;
	for (int i = 0; i < 0x7fffffff; ++i)
	{
		try
		{
			int result = do_stuff(i);
		}
		catch (...)
		{
			std::cout << "Error at " << i << std::endl;
		}
	}
}

int main(int argc, char ** argv)
{
	outparam();
	exceptions();
}
