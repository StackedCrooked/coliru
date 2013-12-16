#include <vector>
#include <iostream>
#include <cstring>
using namespace std;
template<typename T>
class Hash{
    private:
        T* m_pData;
        unsigned int m_size;
        unsigned int djb2(const char* key){
            unsigned int hash=5381;
            for(unsigned int i=0;i<strlen(key);i++)
                hash=((hash<<5)+hash)+(unsigned int) key[i];
            return hash%m_size;
        }
    public:
        Hash(unsigned int hash_size):m_size(hash_size){m_pData=new T[m_size];}
        ~Hash(){delete [] m_pData;}
        void set(const char*key,const T&val){
            unsigned int index=djb2(key);
            cout<<"Index: "<<index<<endl;
            m_pData[index]=val;
            
        }
        T get(const char*key){
            return m_pData[djb2(key)];
        }
};

int main()
{
    Hash<float> hash(50);
    hash.set("Hello",20.5);
    hash.set("World",30.5);
    
    cout<<hash.get("Hello")<<endl;
    cout<<hash.get("World")<<endl;
    return 0;
}