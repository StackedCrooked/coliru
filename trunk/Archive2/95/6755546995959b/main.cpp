struct B
{
    operator B() { return B(); }
    
    B() = default;
    B(B&&) = default;
    B(const B&) = delete;
    B& operator=(B) { return *this; };
};

int main()
{
   B b;
   B c;
   c = b;
}