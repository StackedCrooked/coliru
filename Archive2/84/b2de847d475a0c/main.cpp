struct Layers
{
    typedef struct Widgets { } Widgets;
    
    virtual void fun(void) 
    {
        struct Widgets w;
    }
    
    Widgets w, x, y, z ;
};

int main() { }