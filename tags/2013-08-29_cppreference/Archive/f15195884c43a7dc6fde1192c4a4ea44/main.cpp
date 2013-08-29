struct Football
{
    virtual const Football & final () const = 0;
};

struct Soccer : Football
{
    Football const & final () const final
    {
        throw Soccer();
    }
};

int main()
{
    Soccer().final();
}