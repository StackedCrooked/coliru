struct Point {
    int x, y;    
}

int foo(Point p) {}

int main() {
    foo({3, 6});
}
