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
	
    /* * /
	function(function&& other)
        : functor { std::move(other.functor) }
    {
        
    }
	function& operator=(function&& other) {
        functor = std::move(other.functor);
        
        return *this;
	}
    /* */
    
    /* */
    function(function&&) = default;
	function& operator=(function&&) = default;
    /* */
	
	R operator()(Args... args) { return functor->call(std::forward<Args>(args)...); }
private:
	std::unique_ptr<holder_base<R, Args...>> functor;
};


#endif



struct Mocha {
    
    Mocha() {
        
    };
    
    typedef function<void, std::string, function<bool>> itFunc;
    
    void describe(
        std::string description,
        function<void, itFunc> cb
    ) {
        currentDepth += 1;
        
        std::string depthString = "";
        for(unsigned int i = 0; i < currentDepth-1; i++) {
            depthString += "\t";
        }
        std::string childDepthString = "";
        for(unsigned int i = 0; i < currentDepth; i++) {
            childDepthString += "\t";
        }
        
        this->resultantString += depthString + description + "\n";
        auto itFunc = [&](std::string testDescription, function<bool> it) {
            this->resultantString += childDepthString + (it() ? "Pass" : "Fail") + ": " + testDescription + "\n";
        };
        
        cb(itFunc);
        
        
        currentDepth -= 1;
    };
    
    
    std::string getResultantString() {
        return this->resultantString;  
    };
    
    private:
        unsigned int currentDepth = 0;
        std::string resultantString = "";
};


int main()
{
    Mocha myMocha;
    
    myMocha.describe("The box", [&](Mocha::itFunc it) {
        it("should sit", [&]() {
            return true; 
        });
        it("should be 3d", [&]() {
            return true; 
        });
        
        myMocha.describe("when red", [&](Mocha::itFunc it) {
            it("should be red", [&]() {
                return true; 
            });
        });
        
        it("should be enclosed", [&]() {
            return true; 
        });
    });
    
    
    std::cout << myMocha.getResultantString() << std::endl;
    
    return 0;
}


