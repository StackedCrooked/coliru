struct A
{ 
    A& operator=(const A&){ }
};

struct B
{
    B& operator=(const B&){ } //What does that function have to do with the function defined in another class (in our case it's A)?
};

int main(){ }