#include <memory>
#include <iostream>

using namespace std;

#define fn auto

fn lol() -> int { return 42; }

fn main() -> int {
    cout << "Lol I'm some new popular language: " << lol();
    return 0;
}