#include <unordered_set>
#include <functional>
#include <algorithm>

class EmitterBase;
class Listener {
    public:
		Listener() {}

		virtual ~Listener();

	private:
		bool disconnect(EmitterBase* instance);
		friend class EmitterBase;

		std::unordered_set<EmitterBase*> parents;
};

class EmitterBase {
	public:
		bool connect(Listener* instance);
		bool disconnect(Listener* instance);
		void disconnectAll();

	protected:

		std::unordered_set<Listener*> listeners;
};

Listener::~Listener() {
	while(!parents.empty())
		(*parents.begin())->disconnect(this);
}

bool Listener::disconnect(EmitterBase *instance) {
	return parents.erase(instance) > 0;
}

bool EmitterBase::connect(Listener *instance) {
	return listeners.insert(instance).second;
}

bool EmitterBase::disconnect(Listener *instance) {
	std::size_t val = listeners.erase(instance);
	if (val > 0)
		return instance->disconnect(this);

	return false;
}

void EmitterBase::disconnectAll() {
	while(!listeners.empty()) {
		(*listeners.begin())->disconnect(this);
		listeners.erase(listeners.begin());
	}
}

//------------------------------------------------------//

template<typename T> class Emitter : public EmitterBase {
	protected:
		void emmit(std::function<void(T&)> f) {
			for(auto it = listeners.begin(); it != listeners.end(); it++)
				f(*(T*)(*it));
		}
};

//------------------------------------------------------//

#include <iostream>
#include <cstdlib>

class IntListener : public Listener {
public:

	IntListener() {}
	virtual ~IntListener() {}

	virtual void onInt(int value) {
		(void) value;
	}

};

class IntGenerator : public Emitter<IntListener> {
public:
	void Generate(std::size_t num) {
		while(num--)
			emmit([] (IntListener& list) {list.onInt(rand());});
	}
};

class IntPrinter : public IntListener
{
	void onInt(int value) override {
		std::cout << value << std::endl;
	}
};

int main() {
	IntPrinter printer;
	IntGenerator generator;

	generator.connect(&printer);
	generator.Generate(5);
}