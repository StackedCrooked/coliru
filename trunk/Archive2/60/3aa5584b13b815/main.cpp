#include <iostream>

class ClassA {
    static int val;
public:
    static void reset() { ClassA::val = 0; }
    void testCase() { val++; }
    void print() { std::cout << "val=" << val << std::endl; }
};

int ClassA::val = 0;

int main() {
    
    for (int i=0; i<3; i++)
    {
		ClassA a;		//instantiate 'a' object locally
		a.print();		//print initial state
		a.testCase();
		a.print();		//not initial state
        ClassA::reset();
	}
}