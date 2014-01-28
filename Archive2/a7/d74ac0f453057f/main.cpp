void foo(int(&)[5]) {}

int main() {
    int arr[4];
    foo(arr);
}
