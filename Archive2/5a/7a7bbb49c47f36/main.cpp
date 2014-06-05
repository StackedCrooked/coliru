struct xyz {
    xyz() {}
};

void func(xyz) {}

int main() {
    func({});
}