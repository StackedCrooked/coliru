//HEADER

struct OperationEnum {
    operator unsigned() const;
    unsigned get() const;
    OperationEnum();
private:
    unsigned value;
    static unsigned next();
};

struct ComparisonEnum : public OperationEnum {};
extern const ComparisonEnum
    LT,     // "<"
    GT,     // ">"
    EQ,     // "=="
    LTEQ,   // "<="
    GTEQ,   // ">="
    NEQ     // "!="
    ;

struct ArithmeticEnum : public OperationEnum {};
extern const ArithmeticEnum
    ADD,    // "+"
    SUB,    // "-"
    MUL,    // "*"
    DIV,    // "/"
    MOD    // "%"
    ;
    
    
//CPP
//THESE ARE IN THE CPP FOR A REASON DO NOT MOVE TO THE HEADER
OperationEnum::operator unsigned() const {return value;}
unsigned OperationEnum::get() const {return value;}
OperationEnum::OperationEnum() :value(next()) {}
unsigned OperationEnum::next() {static unsigned v1=0; return v1++;}

const ComparisonEnum
    LT,     // "<"
    GT,     // ">"
    EQ,     // "=="
    LTEQ,   // "<="
    GTEQ,   // ">="
    NEQ     // "!="
    ;
const ArithmeticEnum
    ADD,    // "+"
    SUB,    // "-"
    MUL,    // "*"
    DIV,    // "/"
    MOD    // "%"
    ;
    
#include <iostream>
int main() {
    ComparisonEnum first = LT;
    if (first == LT) 
        std::cout << first;
        
    //ArithmeticEnum var = LT; //error: conversion from ‘const ComparisonEnum’ to non-scalar type ‘ArithmeticEnum’ requested
    
    OperationEnum fasfdsaf = MOD;    
}

