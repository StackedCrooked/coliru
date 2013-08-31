class A; // this and the next line are not needed in VS2012, but
void swap(A& first, A& second); // will make the code compile in g++ and clang++

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