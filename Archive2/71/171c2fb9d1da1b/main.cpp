struct B
{
    B() = default;
    B(B&&) = default;
    B(const B&) = delete;
    B& operator=(B) { return *this; };

    operator B() { return B(); }
};

int main()
{
   B b;
   B c;
   c = b;
}