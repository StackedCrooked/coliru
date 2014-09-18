#include<iostream>  
#include<string>  
using namespace std;  
class stack  
{  
    public:  
        void push(char a)  
        {  
            ++top;    
            arr[top]=a;  
        }  
        void pop()  
        {  
            top--;  
        }  
        void initialize(int size)  
        {  
            top=-1;  
            max=size;  
        }  
        bool chckfull()  
        {  
            return (top==max-1);  
        }  
        bool chckempty()  
        {  
            return (top==-1);  
        }  
        char front()  
        {  
            return arr[top];  
        }  
        private:  
            int top;  
            int max;  
            char arr[404];  
};  
int chckalphanum(char y)  
{  
    if((y>='a')&&(y<='z'))  
    return 1;  
    else if ((y>='A')&&(y<'Z'))  
    return 1;  
    else if((y>='0')&&(y<='9'))  
    return 1;  
    return 0;  
}  
int pre(char x)  
{  
    if(chckalphanum(x))  
    return 0;  
    if(x=='(')  
    return -1;  
    else if(x=='^')  
    return 3;  
    else if((x=='/')||(x=='*'))  
    return 2;  
    else  
    return 1;  
}  
int main ()  
{  
    std::ios::sync_with_stdio(false);  
    string s, s1=")";  
    char q[404];  
    int qmax=0,t;  
    stack prs;  
    scanf("%d", &t);  
    while(t--)  
    {  
    cin>>s;  
    prs.initialize(s.length());  
    prs.push('(');  
    s=s+s1;  
    for(int i=0; i<s.length(); i++)  
    {  
        if(s[i]=='(')  
        prs.push('(');  
        else if(chckalphanum(s[i]))  
        {  
            q[qmax]=s[i];  
            qmax++;  
        }  
        else if(s[i]==')')  
        {  
            while(prs.front()!='(')  
            {  
                q[qmax]=prs.front();  
                qmax++;  
                prs.pop();  
            }  
            prs.pop();  
        }  
        else  
        {  
             while(pre(prs.front())>=pre(s[i]))  
             {  
                q[qmax]=prs.front();  
                qmax++;  
                prs.pop();  
             }  
             prs.push(s[i]);  
        }  
    }  
    for(int i=0; i<qmax; i++)  
    cout<<q[i];  
    cout<<"\n";  
    qmax=0;  
    }  
return 0;  
}