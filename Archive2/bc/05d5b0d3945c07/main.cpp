void foo(int *[10]) {}

int main() {
    int arr[10][10];
    foo(arr);
}