#include <iostream>
#include <unistd.h>

constexpr int something_expensive(int x) { return x; }

int process(int x)
{
    switch (x)
    {
        // hard-coded for common cases
        case 0: return something_expensive(0);
        case 1: return something_expensive(2);a