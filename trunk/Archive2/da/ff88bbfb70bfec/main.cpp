struct foo {
    bool operator==(foo const& other) const;
};

bool foo::operator==(foo const&) const
{ return true; }

int main()
{
    foo a, b;
    a == b;
}