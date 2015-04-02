#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>

using namespace std;

bool task1(const string& first, const string& second)
{
    if (first.size() != second.size()) return false;
    size_t pos = first.find(*second.begin());
    if (pos == string::npos) return false;
    size_t len = first.size();
    return (first.compare(pos,len-1,second.c_str(),len-pos) == 0 && second.compare(pos,len-1,first.c_str(),len-pos)==0);
}

void getMisssingLetter(const string& str,string& ret)
{
    static string arr("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    string res;
    for_each(arr.begin(),arr.end(),
             [&](char c) {  bool found = false;
                            for (auto it = str.begin();it !=str.end(); it++)
                                if (c == toupper(*it)) found = true;
                            if (!found) ret.append(1,c);  });
}

bool task3(const string& str, vector<string>& res,int vel)
{
    if (vel < 1 || vel > 10) return false;
    if (str.size() > 50 || str.empty()) return false;
    if (!all_of(str.begin(),str.end(),[](char c){ return (c== 'R' || c == 'L' || c == '.'); } ))
        return false;
        
    vector<char> arrR;
    transform(str.begin(),str.end(), back_inserter(arrR),[](char c){ if (c == 'R') return '1'; return '0'; });
    vector<char> arrL;
    transform(str.begin(),str.end(), back_inserter(arrL),[](char c){ if (c == 'L') return '1'; return '0'; });

    string s1;
    transform(str.begin(),str.end(),back_inserter(s1),[](char c){  if (c == 'R' || c == 'L') return 'X'; return '.'; });
    res.push_back(s1);
    cout << s1 << endl;

    int arrSize = arrR.size();
    //assert(arrR.size() == arrL.size());
    int num = 0;
    do {
        for (int i = arrSize - 1; i >= 0 ; i--) {
            if (i + vel < arrSize)
                swap(arrR[i],arrR[i+vel]);
            else
                arrR[i] = '0';
        }
        for (int i = 0; i < arrSize; i++) {
            if (i - vel >= 0)
                swap(arrL[i],arrL[i-vel]);
            else
                arrL[i] = '0';
        }
        num = 0;
        string sres;
        for (int i = 0; i < arrSize; ++i) {
            if (arrR[i] == '1' || arrL[i] == '1') {
                sres.append(1,'X');
                num++;
            }
            else
                sres.append(1,'.');
        }
        res.push_back(sres);
        cout << sres << endl;
    } while(num > 0);
    return true;
}

int main()
{
    cout << "========= task 1 ===========" << endl;
    string s1("hewloworld");
    string s2("worldhewlo");
    cout << (task1(s1,s2) ? "Yes" : "No") << endl;

    cout << "========= task 2 ===========" << endl;
    string sentence("Abc db g fac");
    string result;
    getMisssingLetter(sentence,result);
    cout << result << endl;

    cout << "========= task 3 ===========" << endl;
    vector<string> res3;
    task3("..RL...",res3,2);
    return 0;
}