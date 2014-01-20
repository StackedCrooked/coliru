int main() {
    int x[] = {1, 2, 3, 4};
    for (int& i : x)
        i += 1;
    return 0; 
}