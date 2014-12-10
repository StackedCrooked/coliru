struct x
{
    float get1() const
    {
        float fx = 4;
        fx += 1.5f;
        return fx;
    }

    float& get2() const
    {
        float fx = 4;
        fx += 1.5f;
        return fx;
    }
};

int main()
{
    x t;
    float x1 = t.get1();
    float/*&*/ x2 = t.get2();
    cout << x1 << endl;
    cout << x2 << endl;
    cin.get();
}