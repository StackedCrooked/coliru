#include<iostream>
#include<memory>
    using namespace std;
    class shape
    {
    public:
    virtual void draw()=0;
    virtual ~shape(){}
    };

    class rectangle: public shape
    {
    public:
    void draw()
    {
    cout<<"draw rectangle"<<endl;
    }
    }; 
    class bluerectangle : public rectangle
    {
    public:
    void draw()
    {
    cout<<"draw bluerectangle"<<endl;
    }
    };
    class circle: public shape
    {
    public:
    void draw()
    {
    cout<<"draw circle"<<endl;
    }

    }; 

    class bluecircle : public circle
    {
    public:
    void draw()
    {
    cout<<"draw bluecircle"<<endl;
    }
    };

    int main()
    {
    std::unique_ptr<shape> obj(new circle);
    obj->draw();
    obj.reset(new rectangle);
    obj->draw();
    obj.reset(new bluerectangle);
    obj->draw();
    obj.reset(new bluecircle);
    obj->draw();
    return 1;
    }