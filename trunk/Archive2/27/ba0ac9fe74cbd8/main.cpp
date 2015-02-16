struct Deleted
{
    Deleted() {}
    
    Deleted(const Deleted &) {}
    
    Deleted(Deleted&&) = delete;
};


int main()
{
    Deleted d(Deleted{});
}