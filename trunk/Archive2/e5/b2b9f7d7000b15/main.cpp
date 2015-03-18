#include <functional>
#include <iostream>
#include <memory>

template<typename T, typename... Args>
std::function<bool(Args...)> fCreate(void(T::*func)(Args...), std::shared_ptr<T> s_ptr)
{
    std::weak_ptr<T> w_ptr = s_ptr;

	return [=](Args&&... args) {
		if (auto ptr = w_ptr.lock())
		{
			(ptr.get()->*func)(args...);
			return true;
		}

		return false;
	};
}

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
	auto fun = fCreate(&B::Increment, b);

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
