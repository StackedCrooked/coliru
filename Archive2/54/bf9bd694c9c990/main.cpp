template<typename T>
T exchange(T& a, T b);

int main() {
    unsigned int a = 1;
    exchange(a, 0);
    
    return 0;
}
    