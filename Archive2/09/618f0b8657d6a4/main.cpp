struct Normal
{
    Normal() {}
    
    Normal(const Normal &) {}
};


int main()
{
    Normal n;
    Normal n2(n);
}