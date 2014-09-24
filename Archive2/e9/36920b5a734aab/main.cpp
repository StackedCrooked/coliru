#include <iostream>
#include <cassert>
#include <cstring>

// Greeting.h
std::string getGreeting();

// Greeting.cpp - Code under test
std::string getGreeting() {
  return "Hello world!";
}

// Test.h
void test();

// Test.cpp
void test() {
  auto greeting = getGreeting();
  assert(greeting == "Hello world!");
  std::cout << "Test passes!\n";
}

// main.cpp
void run() {
  std::cout << getGreeting() << "\n";
}

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "-t") == 0)
    test();
  else
    run();
}