#include <iostream>

namespace feather
{
    namespace shared
	{
		class window
		{
			public:

				virtual void foo()
				{
					std::cout << "shared" << std::endl;
				}
		};
	}

	namespace linux
	{
		class window : shared::window
		{
			public:

				virtual void foo() override
				{
					std::cout << "linux" << std::endl;
				}
		};
	}

	namespace windows
	{
		class window : shared::window
		{
			public:

				virtual void foo() override
				{
					std::cout << "windows" << std::endl;
				}
		};
	}

	using namespace linux;
}

int main()
{
	feather::window window;

	window.foo();
}