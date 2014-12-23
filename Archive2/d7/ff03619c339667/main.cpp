class Setting
{
public:
    Setting(){
     f1();
     f2();
     //...
    }
    virtual void f1();
     virtual void f2();
}
class Setting2:public Setting
{
public:
    Setting(){
    //duplicating same stuffs 
     f1();
     f2();
     //...
    }
    virtual void f1();
     virtual void f2();
}

    

    
