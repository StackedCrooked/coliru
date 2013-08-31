#include <memory>
#include <cstdio>
#include <string>
#include <vector>

class CPolygon
{
protected:
    std::string name;
public:
    CPolygon()
    {
        this->name = "Polygon";
    }
    virtual void Print()
    {
        printf("From CPolygon: %s\n", this->name.c_str());
    }
};

class CRectangle: public CPolygon
{
public:
    CRectangle()
    {
        this->name = "Rectangle";
    }
    virtual void Print()
    {
        printf("From CRectangle: %s\n", this->name.c_str());
    }
};

class CTriangle: public CPolygon
{
public:
    CTriangle()
    {
        this->name = "Triangle";
    }
    virtual void Print()
    {
        printf("From CTriangle: %s\n", this->name.c_str());
    }
};

int main()
{
    std::vector< std::shared_ptr<CPolygon> > polygons;
    polygons.push_back( std::make_shared<CRectangle>() );
    polygons.push_back( std::make_shared<CTriangle>() );

    for (auto it = polygons.begin() ; it != polygons.end(); ++it)
    {
        (*it)->Print();
    }

    return 0;
}
