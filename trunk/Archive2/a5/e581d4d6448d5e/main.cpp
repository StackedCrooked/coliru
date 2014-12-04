class  C {
    public:
        constexpr C(int) { }
        C(const C&) = delete;
        C& operator=(const C&) = delete;
};

int main() {
    constexpr C arr[] = {1, 2};
}