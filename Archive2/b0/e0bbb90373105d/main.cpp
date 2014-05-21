int main() {
    int x = 2147447412;
    int base = 1;
    while (base * 10 <= x) 
        base *= 10; // this loop will run forever.
    
    while ((long long)(base * 10) <= (long long)(x)) 
        base *= 10; // this loop still will run forever
}