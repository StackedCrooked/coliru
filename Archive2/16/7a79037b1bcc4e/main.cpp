class Rectangle
{
public:
    Rectangle() : l(10), b(5){}
    virtual void SetL(const int &rhs){ l = rhs; }
    virtual void SetB(const int &rhs){ b = rhs; }
    int getL() const { return l; }
    int getB() const { return b; }
private:
    int l, b;
};

int main()
{
    Rectangle r;
    return 0;
}