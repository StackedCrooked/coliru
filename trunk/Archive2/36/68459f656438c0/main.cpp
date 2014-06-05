#include <iostream>
#include <functional>
#include <memory>
#include <type_traits>

template<typename Lambda, typename... Args> struct Closure {
    typedef typename std::result_of<Lambda(Args...)>::type RetVal;

	template<typename T> Closure(T &&lambda) : lambda(std::forward<T>(lambda)) {}

	static RetVal invoke(Args... args, void *data) {
		return static_cast<Closure *>(data)->lambda(args...);
	}

	static void destroy(void *data) {
		delete static_cast<Closure *>(data);
	}

	Lambda lambda;
};

template<typename... Args, typename Lambda> std::unique_ptr<Closure<typename std::remove_reference<Lambda>::type, Args...>> makeClosure(Lambda &&lambda) {
	typedef Closure<typename std::remove_reference<Lambda>::type, Args...> closure_t;
	return std::unique_ptr<closure_t>{new closure_t{std::forward<Lambda>(lambda)}};
}

int main() {

	void (*fnPtr)(void *);
	void (*delPtr)(void *);
	void *data;

	{
		int num = 3;
		auto lambda = makeClosure<>([=] { std::cout << num << '\n'; });

		fnPtr = lambda->invoke;
		delPtr = lambda->destroy;
		data = lambda.release();
	}

	fnPtr(data);
	delPtr(data);
}
