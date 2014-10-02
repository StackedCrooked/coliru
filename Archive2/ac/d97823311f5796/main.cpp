#include <iostream>

class MyObject
{
public:
    virtual void hide(){std::cout<<"Hiding MyObject\n";}
};

class PushButton:public  MyObject
{
public:
    void hide(){std::cout<<"Hiding button\n";}
};

class MainWindow:public  MyObject
{
public:
    void hide(){std::cout<<"Hiding MainWindow\n";}
};


void hideObject(MyObject* object)
{
    object->hide();
}

int main()
{
    PushButton* button=new PushButton;
    MainWindow* window=new MainWindow;

    hideObject(button);//hide button
    hideObject(window);//hide window
}