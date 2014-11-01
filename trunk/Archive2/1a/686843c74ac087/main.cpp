auto f = [] (bool c1, bool c2) {
    if (c1) return 1;
    if (c2) return 2;
    else    return 3;
};

int main()
{
    f(true, false);
    f(false, true);
    f(false, false);
}