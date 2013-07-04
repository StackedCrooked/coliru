typedef struct foo {
} my_other_struct_t;

struct bar {
} mystruct;

int main() {
    void* addr = &mystruct;
    my_other_struct_t* ohyes = addr; // <333
}