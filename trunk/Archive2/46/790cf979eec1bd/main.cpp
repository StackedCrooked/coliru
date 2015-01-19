#include <stdint.h>
#include <stddef.h>

template <typename T>
void PerfectForwarding(T& tValue);

template <typename T>
void PerfectForwarding(T&& tValue);

int main(){
    int i;
    PerfectForwarding(i);
}