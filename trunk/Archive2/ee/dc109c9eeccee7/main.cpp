#include <iostream>
#include <functional>
#include <memory>
#include <type_traits>

template<typename Lambda, typename... Args>
struct Closure {
    typedef typename std::result_of<Lambda(Args...)>::type RetVal;
    
    Closure() : data{nullptr} {}

    Closure(const Closure &) = delete;
    Closure(Closure &&other) : data{other.release()} {}

    Closure(const Lambda &lambda) : data{new Lambda{std::forward<const Lambda &>(lambda)}} {}
    Closure(Lambda &&lambda) : data{new Lambda{std::forward<Lambda &&>(lambda)}} {}
    
    ~Closure() { delete data; }

	static RetVal invoke(Args... args, void *data) {
		return (*static_cast<Lambda *>(data))(args...);
	}

	static void destroy(void *data) {
		delete static_cast<Lambda *>(data);
	}
    
    Lambda *release() {
        Lambda *retVal = data;
        data = nullptr;
        return retVal;
    }

	Lambda *data;
};

template<typename... Args, typename Lambda>
Closure<typename std::remove_reference<Lambda>::type, Args...> makeClosure(Lambda &&lambda) {
    return Closure<typename std::remove_reference<Lambda>::type, Args...>{std::forward<Lambda>(lambda)};
}

int main() {
	void (*fnPtr)(void *);
	void (*delPtr)(void *);
	void *data;

	{
        std::string capture = "Help, I've been captured!";
		auto lambda = makeClosure<>([=] { std::cout << capture << '\n'; });

		fnPtr = lambda.invoke;
		delPtr = lambda.destroy;
		data = lambda.release();
	}

	fnPtr(data);
	delPtr(data);
}
