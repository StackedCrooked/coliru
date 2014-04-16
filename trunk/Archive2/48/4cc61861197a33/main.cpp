#include <thread>
#include <string>
#include <iostream>

template<class T>
void print(T* value, std::string text)
{
   std::cout << "value: " << *value << std::endl;
   std::cout << text << std::endl;
}

template<class T>
void threadPool(T* value)
{
   std::string text = "this is a text with " + std::to_string(*value);
   std::thread(&print<T>, value, text);
}

int main(void)
{
   unsigned int a = 1;
   float b = 2.5;
   threadPool<unsigned int>(&a);
   threadPool<float>(&b);
}