#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>

typedef std::function<int(int)> fib_func;
typedef std::shared_ptr<fib_func> fib_func_ptr;

fib_func_ptr fibonacci()
{
    typedef std::pair<int, int> pair;

	auto memoPtr = std::make_shared<std::unordered_map<int, int>>();

	memoPtr->insert(pair(0, 0));
	memoPtr->insert(pair(1, 1));

	fib_func_ptr fibPtr = std::make_shared<fib_func>([memoPtr, fibPtr](const int n) {

        auto it = memoPtr->find(n);
		int result;

		if (it == memoPtr->end()) {
			fib_func& fib = *fibPtr;
			result = fib(n - 1) + fib(n - 2);
			(*memoPtr)[n] = result;
		} else {
			result = it->second;
		}

		return result;
	});

	return fibPtr;
}


int main()
{
	fib_func_ptr fibonacciPtr = fibonacci();

	std::cout << (*fibonacciPtr)(13) << std::endl;

	std::cin.get();
}