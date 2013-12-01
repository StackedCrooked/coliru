using int10arr = int(&)[10];

struct S {
    int arr[10]{};
    operator int10arr() {return arr;}
};

int main() {
    
}