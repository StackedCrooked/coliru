struct test
{
    explicit operator bool() const { return true; }
    template<typename T> explicit operator T() const = delete;
};

int main()
{
    test a;
    float b = static_cast<bool>(a);  // b = 1
    float c = static_cast<float>(a); // c = ?
}
