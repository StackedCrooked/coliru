#include <iostream>
#include <functional>
#include <memory>
#include <type_traits>

template<typename Lambda, typename... Args> struct Closure {
    typedef typename std::result_of<Lambda(Args...)>::type RetVal;

	//template<typename T> Closure(T &&lambda) : lambda{new Lambda{std::forward<Lambda>(lambda)}} {}
    Closure(const Lambda &lambda) : lambda(new Lambda(lambda)) {}
    ~Closure() { delete lambda; }

	static RetVal invoke(Args... args, void *data) {
		return (*static_cast<Lambda *>(data))(args...);
	}

	static void destroy(void *data) {
		delete static_cast<Lambda *>(data);
	}
    
    void *data() const { // should this be const?
        return lambda;
    }
    
    void release() {
        lambda = nullptr;
    }

protected:
	Lambda *lambda;
};

template<typename... Args, typename Lambda> Closure<typename std::remove_reference<Lambda>::type, Args...> makeClosure(Lambda &&lambda) {
    //return Closure<typename std::remove_reference<Lambda>::type, Args...>{std::forward<Lambda>(lambda)};
    return Closure<typename std::remove_reference<Lambda>::type, Args...>{lambda};
}

int main() {

	void (*fnPtr)(void *);
	void (*delPtr)(void *);
	void *data;

	{
        struct A {
            A() {}
            A(const A &) {}
            void operator()() { std::cout << "Hi!\n"; }
        };
        
        auto lambda = makeClosure(A{});
        //int num = 3;
		//auto lambda = makeClosure<>([=] { std::cout << num << '\n'; });

		fnPtr = lambda.invoke;
		delPtr = lambda.destroy;
		data = lambda.data();
        lambda.release(); // better name?
	}

	fnPtr(data);
	delPtr(data);
}
