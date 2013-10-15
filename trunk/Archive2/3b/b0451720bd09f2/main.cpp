#include <iostream>

class HasDefaultConstructor {
    public:
		HasDefaultConstructor() {};
		void doThing() { std::cout << "Hello, World!" << std::endl; }
};

class DoesntInitializeButOkay {
	public:
		DoesntInitializeButOkay() {};
		void doThing() { c.doThing(); };
	private:
		HasDefaultConstructor c;
};

class DoesntInitializeAndWrong {
	public:
		DoesntInitializeAndWrong() { c = nullptr; };
		void doThing() { c->doThing(); };
	private:
		HasDefaultConstructor *c;
};

class DoesInitialize {
	public:
		DoesInitialize() { c = new HasDefaultConstructor(); }
		void doThing() { c->doThing(); };
	private:
		HasDefaultConstructor *c;
};

int main() {
	DoesntInitializeButOkay  A; A.doThing(); // works
	DoesInitialize C; C.doThing(); // works
	DoesntInitializeAndWrong B; B.doThing(); // crashes
	return 0;
}