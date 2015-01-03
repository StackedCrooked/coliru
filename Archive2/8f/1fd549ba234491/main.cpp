#include <unordered_set>
#include <functional>
#include <algorithm>

#include <iostream>
#include <cstdlib>

class EmitterBase;
class Listener {
    public:
		Listener() {}

		virtual ~Listener();

	private:

		bool connect(EmitterBase* instance);
		bool disconnect(EmitterBase* instance);
		friend class EmitterBase;

		std::unordered_set<EmitterBase*> parents;
};

class EmitterBase {
	public:
		~EmitterBase();

		bool connect(Listener* instance);
		bool disconnect(Listener* instance);
		void disconnectAll();

	protected:

		std::unordered_set<Listener*> listeners;
};

Listener::~Listener() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	while(!parents.empty())
		(*parents.begin())->disconnect(this);
}

bool Listener::connect(EmitterBase *instance) {
	std::cout << __PRETTY_FUNCTION__ << " " << instance << std::endl;
	return parents.insert(instance).second;
}

bool Listener::disconnect(EmitterBase *instance) {
	std::cout << __PRETTY_FUNCTION__ << " " << instance << std::endl;
	return parents.erase(instance) > 0;
}

EmitterBase::~EmitterBase() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	disconnectAll();
}

bool EmitterBase::connect(Listener *instance) {
	std::cout << __PRETTY_FUNCTION__ << " " << instance << std::endl;
	auto ins = listeners.insert(instance);
	bool lis = instance->connect(this);
	return ins.second && lis;
}

bool EmitterBase::disconnect(Listener *instance) {
	std::cout << __PRETTY_FUNCTION__ << " " << instance << std::endl;
	std::size_t val = listeners.erase(instance);
	if (val > 0)
		return instance->disconnect(this);

	return false;
}

void EmitterBase::disconnectAll() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
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
	void generate(std::size_t num) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
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
	IntGenerator generator;
	{
		IntPrinter printer;
		generator.connect(&printer);
		generator.generate(5);
	}
	{
		IntPrinter printer;
		generator.connect(&printer);
		generator.generate(5);
	}

	generator.generate(5);
	IntPrinter printer;
	generator.connect(&printer);
}

