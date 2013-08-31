#include <vector>

template<template<typename... T> class X> struct F {
    typedef X<int> type;
};
template<typename T> using alias = int;

int main() {
    F<alias>::type first;
    F<std::vector>::type second;
}