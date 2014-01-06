// BV2.cpp
#include "Bv2.hpp"

void Bv2::something()
{
    ...
}

// BV2.hpp
#ifndef _BV2_HPP
#define _BV2_HPP

class Bv2
{
    void something();
};

#endif //_BV1_HPP

// BV1.cpp
#include "Bv1.hpp"

#include "Bv2.hpp"

void Bv1::something()
{
    Bv2.something();
}

// BV1.hpp
#ifndef _BV1_HPP
#define _BV1_HPP

class Bv1
{
    void something();
};

#endif //_BV1_HPP

// main.cpp
#include "Bv1.hpp"
#include "Bv2.hpp"

int main()
{
    Bv b = (...) ? new Bv1() : new Bv2();
    b.something();
}

