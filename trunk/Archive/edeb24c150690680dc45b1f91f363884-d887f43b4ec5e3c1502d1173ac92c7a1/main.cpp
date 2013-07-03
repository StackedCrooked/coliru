#!/bin/bash

# Write message.h
cat >message.h <<EOF
#include <string>
std::string get_message();
EOF

# Write message.cpp
cat >message.cpp <<EOF
#include "message.h"
std::string get_message() { return "Hello World!"; }
EOF

# Write main.cpp
cat >main.cpp <<EOF
#include "message.h"
#include <iostream>

int main()
{
    std::cout << get_message() << std::endl;
}
EOF

# Compile, link and run
g++ -c -Wall -pedantic -O2 main.cpp
g++ -c -Wall -pedantic -O2 message.cpp
g++ *.o
./a.out
