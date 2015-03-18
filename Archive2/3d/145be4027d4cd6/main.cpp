#include <functional>
#include <iostream>
#include <memory>

template<typename Func>
struct FCreate_;

template<typename T, typename... Args>
struct FCreate_<void(T::*)(Args...)>
{
    std::function<bool(Args...)> func;

	FCreate_(void(T::*f)(Args...), std::shared_ptr<T> s_ptr)
		: func([&] {
			std::weak_ptr<T> w_ptr = s_ptr;

			return [=](Args&&... args) {
				if (auto ptr = w_ptr.lock())
				{
					(ptr.get()->*f)(args...);
					return true;
				}

				return false;
			};
		}())
	{ }
};

template<typename T, typename... Args>
std::function<bool(Args...)> FCreate(void(T::*func)(Args...), std::shared_ptr<T> s_ptr)
{ return FCreate_<void(T::*)(Args...)>(func, s_ptr).func; }

class B
{
	private:
		int taco_ = 0;

	public:
		void Increment(int i)
		{
			taco_ += i;
			std::cout << "taco: " << taco_ << '\n';
		}
};

int main()
{
	auto b = std::make_shared<B>();
	auto fun = FCreate(&B::Increment, b);

	for (int i : {10, 32, 0})
	{
		if(!i)
			b.reset();

		if(fun(i))
			std::cout << "[success]\n";
		else
			std::cout << "[fail]\n";
	}
}
