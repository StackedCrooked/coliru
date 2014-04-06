#include <new>

int main(){
    int non_const;
    ::new (&non_const) const int(41);
    ::new (&non_const) const int(42);
}