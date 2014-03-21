struct NonLiteralType {
    ~NonLiteralType() {}
};

template<class T>
constexpr NonLiteralType can_not_be_constexpr() {
    NonLiteralType not_one_statement;
    return not_one_statement;
}

int main(int argc, char** argv) {
    can_not_be_constexpr<void>();
    return 0;
}