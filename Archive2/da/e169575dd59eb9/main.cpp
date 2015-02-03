#include<iostream>
#include<list>

using namespace std;

ostream& operator<<(ostream & os,const list<int>& list){
    for(auto& i:list){
        os<<i<<" ";
    }
    return os;
}
void reverse(list<int> li){
    list<int>::iterator beg=li.begin();
    list<int>::reverse_iterator rbeg=li.rbegin();
    list<int>::iterator end=li.end();
    for(unsigned int i=0;i<(li.size()/2);i++){
        int a=*rbeg;
        *rbeg=*beg;
        *beg=a;
        beg++;
        rbeg++;
       // cout<<beg->next<<endl;
        
    }
    
        //cout<<*beg<<*rbeg;

    cout<<li<<endl;
}

int main()
{
    list<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_back(1);
    cout<<li<<endl;
    reverse(li);
    cout<<li.size()<<endl;
    
}


