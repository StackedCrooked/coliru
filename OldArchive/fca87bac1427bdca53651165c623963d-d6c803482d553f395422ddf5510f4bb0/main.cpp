#include<iostream.h> 
class IndiaBix
{
    int x; 
    public:
    IndiaBix(short ss)
    {
        cout<< "Short" << endl;
    }
    IndiaBix(int xx)
    {
        cout<< "Int" << endl;
    }
    IndiaBix(char ch)
    {
        cout<< "Char" << endl;
    }
    ~IndiaBix() 
    {
        cout<< "Final";
    }
};
int main()
{
    IndiaBix *ptr = new IndiaBix('B');
    return 0; 
}