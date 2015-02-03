#include<iostream>

float abso(float, float);
float fnc(float);

int main(void)
{
    float a, b, c, d, fa, fb, fc,tole;
/**    std::cout<<"a:";
	std::cin>>a;
	std::cout<<"b:";
	std::cin>>b;
**/	
    a = 1;
    b=-3;
    tole = 0.00001;
    d = abso(a,b);
    
	while(d > tole)
	{
	c = (a+b)/2;
	fa = fnc(a);
	fb = fnc(b);
	fc = fnc(c);
	
	if ((fa*fc)>0){
                  a=c;
                  }
                  
                  else{
                       b=c;
                       }
                       d = abso(a,b);
	}
	
	std::cout<<a<<std::endl;
}

float abso(float a,float b)
{
	float abs;
	abs = a-b;
    if(abs < 0)
    {
        abs = abs*-1;
    }
    
    return abs;
}


float fnc(float x)
{
      float fnctn;
      fnctn =  (x*x*x+1*x*x-5*x-6);
      return fnctn;
}
