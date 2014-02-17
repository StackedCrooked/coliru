#include <iostream>

int value = 4;

auto func = [] {
    std::cout << "This is the new shit" << std::endl;
};

auto gimmeFunc(int wot) {
    static int counter = 0;
    return [=] {
    ++counter;
	return wot + counter;
    };
}

int main() {
    int localvalue = 12;
    
    auto fn = [=](auto times) {
	return times * (value + localvalue);
    };
    
    std::cout << fn(4) << ", " << fn(2.6) << std::endl;
    func();
    auto myfunc = gimmeFunc(9001);
    for (int i = 0; i < 10; ++i) {
	std::cout << myfunc() << '\n';
    }
}