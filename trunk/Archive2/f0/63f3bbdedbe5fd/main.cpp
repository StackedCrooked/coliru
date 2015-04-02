#include <iostream>
#include <string>


#ifndef functionSig_h
#define functionSig_h

// By Luc Danton: http://chat.stackoverflow.com/transcript/message/21940188#21940188
// http://coliru.stacked-crooked.com/a/015660099e486a80
// Works as function<R, A, B, C> instead of std::function<R(A, B, C)>
#include <utility>
#include <memory>

template<typename R, typename... Args>
struct holder_base {
    virtual ~holder_base() = default;
    
	virtual std::unique_ptr<holder_base> clone() const = 0;
	virtual R call(Args... args) = 0;
};

template<typename Functor, typename R, typename... Args>
struct holder: holder_base<R, Args...> {
	explicit holder(Functor functor): functor(std::move(functor)) {}
	
private:
	Functor functor;

public:
	R call(Args... args) override { return functor(std::forward<Args>(args)...); }
	std::unique_ptr<holder_base<R, Args...>> clone() const override
	{ return std::unique_ptr<holder> { new holder(*this) }; }
};

template<typename Functor, typename... Args>
struct holder<Functor, void, Args...>: holder_base<void, Args...> {
	explicit holder(Functor functor): functor(std::move(functor)) {}
	
private:
	Functor functor;

public:
	void call(Args... args) override { functor(std::forward<Args>(args)...); }
	std::unique_ptr<holder_base<void, Args...>> clone() const override
	{ return std::unique_ptr<holder> { new holder(*this) }; }
};

template<typename R, typename... Args>
struct function {
	template<typename Functor>
	function(Functor functor): functor(new holder<Functor, R, Args...>(std::move(functor))) {}
	
	function(function const& other): functor(other.functor->clone()) {}
	function& operator=(function const& other) { functor = other.functor->clone(); return *this; }
	
	function(function&&) = default;
	function& operator=(function&&) = default;
	
	R operator()(Args... args) { return functor->call(std::forward<Args>(args)...); }
private:
	std::unique_ptr<holder_base<R, Args...>> functor;
};


#endif



std::string foo(
    function<void, function<void, std::string>> bar
) {
    std::string result = "";
    auto collectFunc = [&](
		std::string message
	) {
		result = result + message;
	};
    
    bar(collectFunc);
    
    return result;
}


int main()
{
    std::string result = foo([&](function<void, std::string> collect) {
        collect("asdf");
        collect("qwer");
    });
    
    std::cout << result << std::endl;
    
    return 0;
}

