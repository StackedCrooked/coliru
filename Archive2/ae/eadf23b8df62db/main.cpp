struct foo;

void bar(foo f);

struct foo {
    int i;
};

void bar(foo f) {
    f.i = 0;   
}

int main() {
    bar({});   
}


