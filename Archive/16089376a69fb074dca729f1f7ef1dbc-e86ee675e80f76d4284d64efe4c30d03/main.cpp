//
                                                                                                                                                                                                                                #include <fstream>
                                                                                                                                                                                                                                #include <memory>
                                                                                                                                                                                                                                
                                                                                                                                                                                                                                
                                                                                                                                                                                                                                struct Dump : std::ofstream
                                                                                                                                                                                                                                {
                                                                                                                                                                                                                                    Dump(const char* name, const char* text) : f(new std::ofstream(name))
                                                                                                                                                                                                                                    {
                                                                                                                                                                                                                                        (*f) << text;
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                    Dump(Dump&& rhs) : f(std::move(rhs.f)) {}
                                                                                                                                                                                                                                    std::unique_ptr<std::ofstream> f;
                                                                                                                                                                                                                                };


                                                                                                                                                                                                                                                Dump files[] = { Dump("main.cpp", R"delim(
// main.cpp
#include "a.h"
#include <iostream>

int main()
{
    std::cout << sum(3, 4) << std::endl;
}    
                                                                                                                                                                                                                                                )delim"), Dump("a.h", R"delim(
// a.h
int sum(int, int);
                                                                                                                                                                                                                                                )delim"), Dump("a.cpp", R"delim(
                                                                                
// a.cpp
int sum(int a, int b) { return a + b; }
                                                                                                                                                                                                                                                )delim") };
                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                int main(){}