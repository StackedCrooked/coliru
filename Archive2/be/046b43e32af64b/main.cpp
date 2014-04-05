#include <new>

int main(){
    int non_const;
    ::new (&non_const) const int(41);
    non_const = 42; // UB
}