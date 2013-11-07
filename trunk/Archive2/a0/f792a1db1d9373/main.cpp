#include <iostream>
using namespace std;


 int main()
 {
    int *p,*q ;
p=new int;
*p=9;
q=p;
delete q;
char *a = new char[1024];
*p=7;
cout<<*p; 
 }

/*
int a=3;
int f(int);
int main()
{
int a=5;a++;
cout<<"\n"<<f(a);
}
int f(int a)
{
a++;cout<<(::a);
return a;
}
*/


/*
inline int f(int i)
{while(i)
{i--;
printf("%d",i);
}
return 1;
}

//void f(int, int=10);
//void f(int a,int b ){ cout << a << ' ' << b;}
int main(){
f(5);

//const int i=9;
//int &r=i;

int i=3 ;
int &j=i ;j++;
i=7;j--;
cout<<"i="<<i<<endl;
cout<<"j="<<j<<endl;
}
*/

/*
void test(void)
{
    unsigned int a=6;
    int b=-20;
cout << a+b << endl;
if(a+b>6)
	cout<<a;
else
	cout<<b;
}
*/

/*
void test(void)
{
int *ptr;
if((ptr=(int*)malloc(0))==NULL)
	cout<<"NULL pointer";
else 
cout<<"Valid pointer ";
}

int main()
{
    test();
        cout << endl;

    int a=9,b=4;
float c=(float)a/b;
	cout<<c;
    
    int a=5 ,b=7,c ;
    c=a+++b ;
    
    cout << a << ' ' << b << ' ' << c << endl;
}
*/
/*
#define hours_in_year (365*24)
 
template <class T> class A
{
public:
    void setP();
    static T i;
private:
    static T p;
};
 
int main()
{
    A<int> aaa;
    A<float> bbb;
    A<int> ccc;
 
    aaa.setP();
    cout << aaa.i;
    bbb.setP();
    cout << endl;
    ccc.setP();
    cout << endl;
    char ar=253;
    cout << ar;
    
    //char *a=new char[20];
}

template <class T> void A<T>::setP() { cout << p++; }
template <class T> T A<T>::i = 1;
template <class T> T A<T>::p = 1.2;
*/


/*
#include <iostream>
#include <string>
using namespace std;
 
template <class T>
inline T power(T x, unsigned int e)
{
  T result = 0; // il faut considérer cette variable initialisée
  for(unsigned int inx=0; inx<e; inx++)
    result += x;
  
  return result;
}
 
int main(void)
{   
    cout << power<int>(4,4) << " " << power<string>("ab",3) << "";
    return 0;
}
*/

/*
class A
{
public:
A(const char * string){};
    ~A(){};
};

int main()
{
    A a = "Alice";
    
}
*/

/*
class X { public: int a; };
class Y { public: float a; };
class Z : public X, Y { public: long a; };

int main()
{
    Z z;
    z.a = 500;
}
*/

/*
unsigned short vct[3][3] = {0,1,2,4,5,6,7,8,9};
unsigned short *pc = vct[0];

int main(void)
{       
    cout << ++*(2+pc++);
    return 0;
}
*/

/*
int main()
{
    unsigned short a[4][3] = {0,7,4,5,11,3,10,7,9};
unsigned short a1[3][3] = {0,7,4,5,11,3,10,7,9};
unsigned short a2[][3] = {0,7,4,5,11,3,10,7,9};

    cout << a[2][0];
}
*/

/*
int main(){
    int a = 10;
    double b;
    size_t x = sizeof (++a-b) / sizeof(double);
    size_t y = sizeof (++a-b) / sizeof(int);
    cout << (x>y?"longer":"shorter") << " " << a;

    return 0;
}
*/


/*int main()
{
	int v;
	for (v = 0; v<10; v++){
		if(v==1 || v==0)
			v++;
        std::cout<< v <<std::endl;
		if(v%2==0)
			v += v/2+2;
		else
			v = (v*2)+2;

		std::cout<< v <<std::endl;
	}
	std::cout<< v;
}*/



/*
int main()
{
    int _element = 2;
int number=1;
while (true) { 
std::cout << number;
if (number == 10) break;
number += _element; }
}*/

/*
int main(){
  int a=10;
  float b;
  int x = sizeof(++a-b);
  printf("%d", x);
  printf(" %d",a); 
  return 0;
}*/
/*
int main()
{
    int xmax;
while(xmax<99)
{
      std::cout<<xmax;
      xmax++;
}
}*/