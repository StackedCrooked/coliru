#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class MyString{
char *p;
size_t len;
char *p1;
public:
MyString(const char*);
MyString();
MyString(MyString&);
~MyString();
MyString& operator=(const MyString&);
char& operator[](const size_t);
char* operator()(size_t,size_t);

friend ostream& operator<<(ostream&,MyString&);
friend MyString operator+(const MyString&,const MyString&);
friend MyString operator+(const char*,const MyString&);
friend MyString operator+=(MyString&,MyString&);
friend MyString operator+=(MyString& a,char* b);
friend bool operator<(const MyString&,const MyString&);
friend bool operator==(const MyString&,const MyString&);
friend bool operator>(const MyString&,const MyString&);
};
MyString::MyString(const char* str){
if(!str){
p=NULL;
p1=NULL;
len=0;
}
else{
len=strlen(str);
p=new char[len+1];
strcpy(p,str);
p1=NULL;
}
}

MyString::MyString(){
p=NULL;
len=0;
p1=NULL;
}

MyString::MyString(MyString& a){
len=a.len;
p=new char[a.len+1];
strcpy(p,a.p);
}

MyString::~MyString(){
if(p) delete[] p;
}

ostream& operator<<(ostream& cout,MyString& a){
if(a.p) cout<<a.p;
return cout;
}

MyString operator+(const MyString& a,const MyString& b){
MyString c;
c.len=a.len+b.len;
c.p=new char[c.len+1];
strcpy(c.p,a.p);
strcat(c.p,b.p);
return c;
}

MyString operator+(const char* a,const MyString& b){
MyString c;
c.len=strlen(a)+b.len;
c.p=new char[c.len+1];
strcpy(c.p,a);
strcat(c.p,b.p);
return c;
}

MyString& MyString::operator=(const MyString& a){
if(p) delete[] p;
len=a.len;
p=new char[len+1];
strcpy(p,a.p);
return *this;
}

char&  MyString::operator[](const size_t a){
return *(p+a);
}

char* MyString::operator()(size_t a,size_t b){
p1=new char[b+1];
strncpy(p1,p+a,b);
p1[b]=0;
return p1;
}

MyString operator+=(MyString& a,MyString& b){
a=a+b;
return a;
}

MyString operator+=(MyString& a,char* b){
MyString c(b);
a=a+c;
return c;
}

bool operator<(const MyString& a,const MyString& b){
if(strcmp(a.p,b.p)<0) return true;
else return false;
}

bool operator==(const MyString& a,const MyString& b){
if(strcmp(a.p,b.p)==0) return true;
else return false;
}

bool operator>(const MyString& a,const MyString& b){
if(strcmp(a.p,b.p)>0) return true;
else return false;
}

int CompareString( const void * e1, const void * e2) {
    MyString * s1 = (MyString * ) e1;
    MyString * s2 = (MyString * ) e2;
    if( * s1 < *s2 )     return -1;
    else if( *s1 == *s2) return 0;
    else if( *s1 > *s2 ) return 1;
}
int main()   {
MyString s1("abcd-"),s2,
s3("efgh-"),s4(s1);
MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
cout << "11. " << s1 << endl;
qsort(SArray,4,sizeof(MyString), CompareString); 
    for( int i = 0;i < 4;++i )
        cout << SArray[i] << endl;
//输出s1从下标0开始长度为4的子串
    cout << s1(0,4) << endl; 
//输出s1从下标为5开始长度为10的子串
    cout << s1(5,10) << endl; 
}