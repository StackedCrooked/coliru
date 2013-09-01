#include <iostream>

using namespace std;

class lineType
{
public:

    lineType();

    lineType(int x, int y, int z);


    void getSlope(int p, int q, int r);

    bool equalLines(const lineType& otherline);
    bool equalParallel(const lineType& otherline);
    bool equalPerpendicular(const lineType& otherline);

private:
    int a, b, c;
};

lineType::lineType()
{
    a = 0;
    b = 0;
    c = 0;
}

lineType::lineType(int x, int y, int z)
{
    a=x;
    b=y;
    c=z;
}

void lineType::getSlope(int p, int q, int r)

{
    a = p;
    b = q;
    c = r;
    if(a == 0)
    {
        cout<<"The slope of the line is a horizontal line"<<endl;
    }
    else if(b == 0)
    {
        cout<<"The slope of the line is a vertical line and slope of a vertical line is is undefined"<<endl;
    }
}



int main()

{
    lineType line1(1,2,4);
    line1.getSlope(1,0,0);
    return 0;
}
