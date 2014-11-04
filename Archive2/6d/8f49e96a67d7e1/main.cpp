# include <iostream>
# include <string>
using namespace std;

struct person
{
    int name;
    int age;
};
class sp
{
    private : person *p;
    public: sp(int n=18,string s="zyz")
    {
        p=new(person);
        p->age=n;
        p->name=s;
    }
    ~sp()
    {
        delete(p);
    }
    int operator* ()
    {
     return *p;   
    }
    int* operator-> ()
    {
    return p;
    }
};
    
int main()
{
    sp s1(4,"baby");
    cout<<s1->name<<"  "<<s1->age<<endl;
    return 0;
}