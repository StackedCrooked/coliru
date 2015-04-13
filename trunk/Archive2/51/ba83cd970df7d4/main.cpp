#!/bin/bash
cat <<END_OF_COMMON_PART >common_part.cpp
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cinttypes>

using namespace std;

#include "second_part.h"
END_OF_COMMON_PART

cp common_part.cpp first_part.cpp
cat << END_OF_FIRST_PART >> first_part.cpp

int main()
{
    Fos f;
    IFos& i = f;
    i.f();
    ChildFos& c = getGane();
    int* mem = reinterpret_cast<int*>(&c);
    mem[0] = 0;
    i.f();
    c.f();
    cout << sizeof(IFos) << " " << sizeof(Fos) << " " << sizeof(ChildFos) << endl;
    return 0;
}

END_OF_FIRST_PART

cat << END_OF_SECOND_PART_H > second_part.h
class IFos
{
public:
    virtual void f() = 0;
};

class Fos : public IFos
{
public:
    virtual void f() override;
    int i;
};

class ChildFos /*final*/ : public Fos
{
public:
    virtual void f() override;
    int i;
};

ChildFos& getGane();
END_OF_SECOND_PART_H

cp common_part.cpp second_part.cpp
cat << END_OF_SECOND_PART >> second_part.cpp

class Gane : public ChildFos
{
public:
    virtual void f()
    {
        cout << "Jazannyát" << endl;
    }
};

ChildFos& getGane()
{
    static Gane g;
    return g;
}

void Fos::f()
{
    ChildFos cf;
    cout << "Fos" << endl;
    cf.f();
    Gane g;
    ChildFos& fg = g;
    fg.f();
}

void ChildFos::f()
{
    cout << "ChildFos" << endl;
}
END_OF_SECOND_PART

clang++ -ggdb -std=c++11 -O2 -c -o first_part.o first_part.cpp && clang++ -ggdb -std=c++11 -O2 -c -o second_part.o second_part.cpp && ls && clang++ -ggdb first_part.o second_part.o && ls && objdump -SCtT ./a.out

//command: . main.cpp && time ./a.out