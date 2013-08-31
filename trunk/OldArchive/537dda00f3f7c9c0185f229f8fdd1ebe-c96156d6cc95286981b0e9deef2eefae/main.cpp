//HEADER

struct OperationEnum {
    operator unsigned() const {return value;}
    unsigned get() const {return value;}
    OperationEnum() :value(next()) {}
private:
    unsigned value;
    static unsigned next() {
        static unsigned v1=0;
        return v1++;
    }
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

