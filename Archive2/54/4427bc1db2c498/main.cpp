

struct Human
{
    void puton(struct Shoe& shoe);
};


struct Shoe
{
    void puton(Human& human)
    {
        human.puton(*this);
    }
};


void Human::puton(Shoe& shoe)
{
    shoe.puton(*this);
}


int main()
{
    Human human;
    Shoe shoe;
    shoe.puton(human);
}