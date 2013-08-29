#include <iostream>
#include <string>

class HelloFactory {
private:
    std::string hello;
public:
    HelloFactory(): hello("Hello") {}
    std::string makeHello() const {
        return hello;
    }
};

class WorldFactory {
private:
    std::string world;
public:
    WorldFactory(): world("World") {}
    std::string makeWorld() const {
        return world;
    }
};

class StringJoiner {
public:
    static std::string joinStringsTogetherWithSpace(const std::string& str1, const std::string& str2) {
        return std::string(str1 + " " + str2);
    }
};

class HelloWorldPrinter {
public:
    static void printHelloWorld(const std::string& str) {
        std::cout << str;
    }
};

int main() {
    HelloFactory hf;
    WorldFactory wf;
    std::string hello = hf.makeHello();
    std::string world = wf.makeWorld();
    std::string helloworld = StringJoiner::joinStringsTogetherWithSpace(hello,world);
    HelloWorldPrinter::printHelloWorld(helloworld);
}