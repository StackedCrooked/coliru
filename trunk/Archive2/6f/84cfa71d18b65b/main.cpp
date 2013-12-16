int main() {
    int b = 3;
    int* bp = &b; 
    int* const &bpr = bp; 
    *bpr = 4;
}