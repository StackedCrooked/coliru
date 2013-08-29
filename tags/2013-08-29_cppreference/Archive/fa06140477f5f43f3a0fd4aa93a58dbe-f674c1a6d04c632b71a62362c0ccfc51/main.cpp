struct Point {
    int x, y;    
};

void foo(Point p) {}

int main() {
    foo({3, 6});
}
