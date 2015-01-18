int main() {
    int *why = (1 == 1) ? (int[2]) {1,2} : (int[2]) {3,4};
    (void)why; // suppress -Wunused-variable
}