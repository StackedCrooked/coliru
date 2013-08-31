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

\tmemoPtr->insert(pair(0, 0));
\tmemoPtr->insert(pair(1, 1));

\tfib_func_ptr fibPtr = std::make_shared<fib_func>([memoPtr, fibPtr](const int n) {

\t\tauto it = memoPtr->find(n);
\t\tint result;

\t\tif (it == memoPtr->end()) {
\t\t\tfib_func& fib = *fibPtr;
\t\t\tresult = fib(n - 1) + fib(n - 2);
\t\t\t(*memoPtr)[n] = result;
\t\t} else {
\t\t\tresult = it->second;
\t\t}

\t\treturn result;
\t});

\treturn fibPtr;
}


int main()
{
\tfib_func_ptr fibonacciPtr = fibonacci();

\tstd::cout << (*fibonacciPtr)(13) << std::endl;

\tstd::cin.get();
}