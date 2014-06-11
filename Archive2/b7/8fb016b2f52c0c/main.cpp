struct B
{
    B() = default;
    B(B&&) = default;
    B(const B&) = delete;
    B& operator=(const B&) = default;
    
    // Successfully takes the place of the copy constructor,
    // but please don't do this!
    operator B() { return B(); }
};

int main()
{
   B b;
   B c;
   c = b;
   // Can't do `B c(b)` though.
   
   const B d;
   B e;
   e = d;
}