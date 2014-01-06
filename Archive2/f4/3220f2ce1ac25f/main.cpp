struct S
{
    bool operator()() const &  { return true; }
    bool operator()() const && { return true; }
};

int main()
{
    S s;

    s();   // works
    S()(); // fails (error: call of '(S) ()' is ambiguous)
}