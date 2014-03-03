struct A
{
    // Temporary assigment disallowed by & at the end
    A& operator=(const A& rhs)
    {
        return *this; 
    }
    
    // This disallows e the same but the error message better
    template<class T>
    T operator=(T&& rhs) &&=delete;
};

A operator+(const A& lhs, const A& rhs)
{
    return lhs; 
}

int main()
{
    A a, b, c;
    
    a+b=c; // compiler error
    c=a+b; // OK
    return 0;
}
