#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;
 void split(vector<string>& destination,string source,bool (*condition)(char),bool (*until)(char)=nullptr) {
    	char* buf=new char[source.length()];
		int temp,count=0;
		for(unsigned int i=0;i<source.length();i++) {
			if(condition(source[i])==true) {
				for(unsigned int j=i+1;j<source.length();j++) {
					if(*until!=nullptr) {
						if(condition(source[j])==true || until(source[j])==true) {
							temp=j-i;
							break;
						}
						else if(j==source.length()-1) {
							temp=j-i+1;
						}
					}
					else {
						if(condition(source[j])==true) {
							temp=j-i;
							break;
						}
						else if(j==source.length()-1) {
							temp=j-i+1;
						}
					}
				}
				if(i!=0 && count!=1) {
					size_t length=source.copy(buf,i,0);
					buf[length]='\0';
					destination.push_back(buf);
					count=1;
				}
				size_t length=source.copy(buf,temp,i);
				buf[length]='\0';
				destination.push_back(buf);
			}
		}
		delete [] buf;	
	}

 
typedef list<pair<int,int> > factorList;
bool chk(char a) {
    if((a=='+'||a=='-'))
	return true;
	else
	return false;
}
bool chk1(char a) {
	if(ispunct(static_cast<int>(a))==true)
	return true;
	else
	return false;
}
bool chk2(char a) {
	if(isalpha(static_cast<int>(a))==true)
	return true;
	else
	return false;
}
int main(int argc,char* argv[],char* env[]) {
    // (x+4)(x+5)=x^2+9x+20
    // (x+4)(x-5)=x^2-x-20
    // (x-4)(x-5)=x^2-9x+20
    // (x-4)(x+5)=x^2+x-20
    factorList f1,f2,f3;
    string expression,e;
    vector<string> term;
    expression="x^2+x-20";
    split(term,expression,chk);
    e=term[1];
	e.pop_back();
    if(e[1]=='\0') {
    	e.append("1");
    }
    int a=stoi(e);
    e=term[2];
    int b=stoi(e);
    int x=abs(b);
    for(int i=1;i<=x;i++) {
        for(int j=1;j<=x;j++) {
            if(i*j==x) {
                f1.push_back(make_pair(i,j));
                f2.push_back(make_pair(-(i),j));
                f3.push_back(make_pair(-(i),-(j)));
            }
        }
    }
	if(a>0 && b>0) {
		for(factorList::iterator it=f1.begin();it!=f1.end();++it) {
			if((*it).first+(*it).second==a) {
				cout<<(*it).first<<" "<<(*it).second<<endl;
			}
		}
	}
	else if((a>0 && b<0) || (a<0 && b<0)) {
		for(factorList::iterator it=f2.begin();it!=f2.end();++it) {
			if((*it).first+(*it).second==a) {
				cout<<(*it).first<<" "<<(*it).second<<endl;
			}
		}
	}
	else if(a<0 && b>0) {
		for(factorList::iterator it=f3.begin();it!=f3.end();++it) {
			if((*it).first+(*it).second==a) {
				cout<<(*it).first<<" "<<(*it).second<<endl;
			}
		}
	}
    system("pause");
    return 0;
}