template <class T>
class Number
{
protected:
    T number;

public:
    Number(T num) { number = num; }

    Number<T> operator+(const Number<T> &an) const
    {
        Number<T> brandNew(0);
        brandNew.number = number + an.number;
        return brandNew;
    }
};

class MyInt : public Number<int>
{
public:
    MyInt() : Number<int>(0) {};
    MyInt(int num) : Number<int>(num) {}
    MyInt(const Number<int> &x) : Number<int>(x) {}
};

int main()
{

    MyInt three = 3;
    MyInt two = 2;
    MyInt five = three + two;
}
