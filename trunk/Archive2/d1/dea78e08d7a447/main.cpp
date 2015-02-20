#include <iostream>

template<typename Func>
int passDoThingIntoMe(Func doThing) {
    int a = doThing(5);
	int b = doThing(a);

	return b;
}


int main()
{
    int i = 5;
    auto doThing = [&](int x) {
		return i+x;
	};

	int result = passDoThingIntoMe(doThing);
   
    std::cout << result << '\n';
}