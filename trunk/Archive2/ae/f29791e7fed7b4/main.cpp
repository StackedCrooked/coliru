#include <iostream>
#include <cstdio>
#include <cstddef>
#include <stdint.h>
#include <cstring>
#include <string>
#include <map>
#include <vector>

typedef uint8_t U8;
typedef uint32_t U32;
typedef uint32_t u32;

#define Warn printf

// Base Event Class
struct Event { 
    Event(U8 type) : m_type(type) { } 
	virtual ~Event() { }

	U8 GetType() const { return m_type; }
	private:
	    U8 m_type;
};

// Custom Event with type = 10
struct SpecialEvent : public Event { 
	const char* text;

	SpecialEvent() 
		: Event(10 /* we'll just say that this is event type 10 */),
		  text("")
	{ }

	SpecialEvent(const char* txt) 
	    : Event(10 /* we'll just say that this is event type 10 */),
	      text(txt)
	{ }
};

// Basic Handler which defines an interface for object which Executes logic on a T*
template<class T> struct Handler { 
	virtual ~Handler() { }

	virtual void Execute(T*) = 0;
};

// Here we expect the T instance to be an Event sub-class
template<class T, class U>
struct EventHandler : public Handler<Event> { 
    typedef void(U::*MemberFunc)(T*);

	EventHandler(U* instance, MemberFunc func)
	    : m_instance(instance), 
	      m_func(func)
	{ }

	// Implements contract for Handler
	void Execute(Event* evt) { 
		// Execute member function casting the base class to the T* implementation
		(m_instance->*m_func)(static_cast<T*>(evt));
	}
    
    private:
        U* m_instance;
        MemberFunc m_func;
};

namespace { 
    std::map<U8, std::vector<Handler<Event>*> > eventListeners;
    
    // We're assuming that T is an Event type again
    template<class T, class U>
    void AddListener(U* instance, void(U::*handler)(T*)) {
        // Quick way to find the event type for an Event
    	U8 eventType = T().GetType();
    
    	// Handler
    	Handler<Event>* h = new EventHandler<T, U>(instance, handler);
    
    	// Add handler to list for the type
    	eventListeners[eventType].push_back(h);
    }
    
    template<class T, class U>
    void RemoveListener(U* instance, void(U::*handler)(T*)) {
    	// We can get the event type...
    	U8 eventType = T().GetType();
    
    	// So we can therefore get the list of handlers...
    	std::vector<Handler<Event>*>* handlers = &eventListeners[eventType];
    
    	for (u32 i = 0; i < handlers->size(); ++i) {
    		Handler<Event>* h = (*handlers)[i];
    
    		// ??? How to know which handler maps to this instance and func ptr?
    		// if (handler->GetId() == IdFor(instance, handler)) { 
    		//     handlers->erase(handlers->begin() + i);
    		//     return;
    		// }
    	}
    }
    
    // Again, assuming T is Event type
    template<class T>
    void DispatchEvent(T* evt) {
    	U8 eventType = T().GetType();
    	std::vector<Handler<Event>*>* handlers = &eventListeners[eventType];
    
    	for (u32 i = 0; i < handlers->size(); ++i) {
    		Handler<Event>* handler = (*handlers)[i];
    		handler->Execute(evt);
    	}
    }
};


// Adds a listener for a special event and then self-destructs once receives the event
struct AutoSpecialEventListener { 
	AutoSpecialEventListener(const char* prefix) : m_prefix(prefix) {
		AddListener(this, &AutoSpecialEventListener::OnSpecialEvent);
	}

	~AutoSpecialEventListener() {
		Warn("Freeing [%s] AutoSpecialEventListener\n", m_prefix);
	}

	void OnSpecialEvent(SpecialEvent* evt) {
		Warn("%s: %s\n", m_prefix, evt->text);

		RemoveListener(this, &AutoSpecialEventListener::OnSpecialEvent);

		// Humor me :-)
		delete this;
	}

	private:
		const char* m_prefix;
};

struct AnotherSpecialListener { 
	AnotherSpecialListener() {

	}

	void OnSpecialEvent(SpecialEvent* evt) {
		Warn("HOORAY! %s!\n", evt->text);
	}
};

int main(int argc, const char* argv[]) {
	// This one automatically adds a listener
	/* AutoSpecialEventListener* s1 = */ new AutoSpecialEventListener("Special Event");
	/* AutoSpecialEventListener* s2 = */ new AutoSpecialEventListener("Less Special Event");

	// This one requires manually adding
	AnotherSpecialListener* s3 = new AnotherSpecialListener();
	AddListener(s3, &AnotherSpecialListener::OnSpecialEvent);
	
	// Output after this line should be:
	//   Special Event: WAT
	//   Freeing [Special Event] AutoSpecialEventListener
	//   Less Special Event: WAT
	//   Freeing [Less Special Event] AutoSpecialEventListener
	//   HOORAY! WAT
	DispatchEvent( new SpecialEvent("WAT") );

	// The important here is that we added two instances of the same class with different,
	// instance data, which is what the static solution would disallow.

	// This issue is that there's not a way to determine the wrapped handler based on the 
	// two inputs (Object Type and Member Function Ptr)

	// Using the existing way, this would've worked because the add and remove were called in the same scope.
	// However, the s1 and s2 examples would not have worked because the Add and Remove are in different scopes.
	// I think this is just because the "member func" data created is done in each scope its accessed (unless it already exists).
	RemoveListener(s3, &AnotherSpecialListener::OnSpecialEvent);

	// At this point:
	// eventListeners[10].size() == 2

	return 0;
}