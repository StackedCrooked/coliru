struct A
{ 
    const A& operator=(const A&){ return A(); }
};

struct B : A
{
    const B& operator=(const B&){ return B(); } //What does that function have to do with the function defined in another class (in our case it's A)?
};

int main(){ }