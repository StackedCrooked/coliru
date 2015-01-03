#include <iostream>
#include <functional>
#include <vector>

//chopped up EventManager.h
#include <functional>
class CallbackEvent{
private:
    std::function<void()> functionToCall;

public:
    CallbackEvent( std::function<void()> fn ) : functionToCall(fn) {}

    /*
    template<class TYPE>
	CallbackEvent(TYPE&& fn){
		this->functionToCall = std::forward<TYPE>(fn);
	}
	*/

};

class EventManager{
private:
	std::vector<CallbackEvent> callbackEvents;

public:
	template<class TYPE>
	void watchEvent(TYPE&& fn){
		// CallbackEvent callbackEvent(fn);
		// callbackEvents.push_back(callbackEvent);
		callbackEvents.emplace_back( std::forward<TYPE>(fn) ) ;
	}
};

class Test{
public:
	EventManager eventManager;

	void test_callee(void){
		//do stuff
	}

	void test_callback_creator(){
		// eventManager.watchEvent(&Test::test_callee);
		eventManager.watchEvent( std::bind( &Test::test_callee, this ) );
	}

};

int main()
{
}
