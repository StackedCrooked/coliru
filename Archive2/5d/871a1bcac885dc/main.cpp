struct S
{
    S(const float(&)[12])
    {
    }
};

float v[12];

S f()
{
    return v;
}

int main()
{
}
