#include <iostream>

struct SomeStruct {
    SomeStruct() {
		
	}
	SomeStruct(int x) {
		this->x = x;
	}
	float x;
};


SomeStruct addThings(SomeStruct a, float t) {
    float result = a.x + t;
	return SomeStruct(result);
}

template<typename Func>
SomeStruct passDoThingIntoMe(int start, Func doThing) {
    SomeStruct a = doThing(start);
	SomeStruct b = doThing(a.x);
	SomeStruct c = doThing(b.x);

	return c;
}

int main()
{
    
    SomeStruct myLocalStruct = SomeStruct(7);

	auto doThing = [&](float t) {
		return addThings(myLocalStruct, t);
	};

    // Expect 26
	SomeStruct result = passDoThingIntoMe(5, doThing);
   
    std::cout << result.x << '\n';
}