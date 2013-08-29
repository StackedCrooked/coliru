struct foo {
    ctor a(bar);
    ctor b(qux);
};

void emplace(lazy foo thing) {
    ::new(ptr) thing;
}

void forward_to_emplace(???) {
    emplace(???);
}

int main() {
    forward_to_emplace(???);
    forward_to_emplace(???);
}