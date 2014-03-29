template<int>
int *map() {
    static int var = 0;
    return &var;
}

int main() {
    *map<'a'>() = 42;
    *map<'z'>() = 1337;

    return *map<0>(); //returns 42
}