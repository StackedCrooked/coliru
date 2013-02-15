struct final;

struct Football
{
    virtual const Football & final () const = 0;
    virtual final penalty();
};

struct Soccer : Football
{
    Football const & final () const final
    {
        throw Soccer();
    }
};


struct final final : Soccer
{    
    final penalty() final { throw Soccer(); }
};


int main()
{
    final().penalty();
}