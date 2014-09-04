union stuff {
    int x;
    int y;
};

void set_up_c_api(stuff* t) {
    t->x = 20;
}

int my_c_api(const stuff* t) {
    return t->x;
}

struct enhanced {
    union { stuff s; int x, y; };

    enhanced() { set_up_c_api(&s); }

    int cpp_api() {
        return my_c_api(&s);
    }
};

int main() {
    enhanced x;
    return x.cpp_api();
}
