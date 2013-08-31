class A
{
    friend void swap(A& first, A& second) {}
    void swap(A& other) {}
    void call_swap(A& other)
    {
        ::swap(*this, other); // note the scope operator
    }
};

int main() { return 0; }