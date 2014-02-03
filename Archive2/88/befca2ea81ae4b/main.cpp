#include <iostream>
#include <string>
#include <vector>

#include <stdint.h>
#include <stddef.h>
 
template <typename TPin, uint16_t TSmoothFactor>
struct Wrapper {};
 
template <typename Dummy>
struct MyClass {
template <typename TheListPin> struct Helper;
 
 
template <typename ThePin, uint16_t TheSmoothFactor>
struct Helper<Wrapper<ThePin, TheSmoothFactor>> {
using RealPin = ThePin;
};
using Pin = typename Helper<Wrapper<int, 400>>::RealPin;

};
 
using Test = typename MyClass<void>::Pin;
int foo = Test();

int main()
{
}
