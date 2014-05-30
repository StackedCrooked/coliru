#include<iostream>
#include<string>
#include<stack>
using namespace std;

int main()
{
 stack<int> num;

 string line;
 int n,count=0,a,b;
 char c;


 while (getline(cin,line))
 {
     for (string::const_iterator it = line.begin(); it != line.end(); ++ it)
     {
         if (isdigit(static_cast<unsigned char>(*it)))
         {
             cout << it << endl;
             n = (it - 48);
             num.push(n);
             count++;
         }
         else if (ispunct(static_cast<unsigned char>(*it)))
         {
             if (it == '+' || it == '-' || it == '/' || it == '*')
             {
                 cout << "count is " << count << endl;
                 if (count>1)
                 {
                    b =  num.top();
                    num.pop();
                    a = num.top();
                    num.pop();

                    if (it == '+')
                    {
                        cout << "+" <<endl;
                        num.push(a+b);
                        count--;
                    }
                    else if (it == '-')
                    {
                        num.push(a-b);
                        count--;
                    }
                    else if (it == '/')
                    {
                        if (b != 0)
                        {
                            num.push(a/b);
                            count--;
                        }
                        else
                        {
                            cout << "division by zero" << endl;
                            return(0);
                        }
                    }
                    else if (it == '*')
                    {
                        num.push(a*b);
                        count--;
                    }
                    else
                    {
                        cout << "invalid input" << endl;
                        return(0);          
                    }
                 }
                 else
                 {
                     cout << "stack underflow" << c << endl;
                     return(0);
                 }
             }
            cout << c << endl;
     }
    }
 }
 while ( !num.empty() )
 {
     cout << num.top() << endl;
     num.pop();
 }
 return 0;
}