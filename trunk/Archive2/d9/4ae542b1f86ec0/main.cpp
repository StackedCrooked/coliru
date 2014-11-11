class apple;

class fruit{
    public: int i;
    void set(apple a);
};

class apple{
    public: int j;
    void set(fruit f);
};

void fruit::set(apple a)
{
    apple a2 = a;
}
void apple::set(fruit f)
{
    fruit f2 = f;
}

