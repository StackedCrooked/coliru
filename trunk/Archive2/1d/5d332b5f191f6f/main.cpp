#include <iostream>
#include <string>
//#pragma warning( disable : 4996 )
// http://bbs.csdn.net/topics/390650931
using namespace std;
const unsigned kMaxStrLen = 20;

string getDate(){
    int t_iYear = 2013;
    int t_iMonth = 11;
    int t_iDay = 23;
    int t_iHour = 16;
    int t_iMin = 45;

    string t_oStrTarget;
    char* pBuf = (char*)malloc(kMaxStrLen);
    if (pBuf) {
        sprintf(pBuf, "%d-%d-%d %d:%d", t_iYear, t_iMonth, t_iDay, t_iHour, t_iMin);
        t_oStrTarget = string(pBuf);
        free(pBuf);
    }
    return t_oStrTarget;
}
string getDate2(){
    int t_iYear = 2013;
    int t_iMonth = 11;
    int t_iDay = 23;
    int t_iHour = 16;
    int t_iMin = 45;

    string t_oStrTarget;
    char* pBuf = (char*)malloc(kMaxStrLen);
    if (pBuf) {
        sprintf(pBuf, "%d-%d-%d %d:%d", t_iYear, t_iMonth, t_iDay, t_iHour, t_iMin);
        t_oStrTarget = pBuf;
        free(pBuf);
    }
    return t_oStrTarget;
}
string getDate3(){
    int t_iYear = 2013;
    int t_iMonth = 11;
    int t_iDay = 23;
    int t_iHour = 16;
    int t_iMin = 45;

    string t_oStrTarget;
    char* pBuf = (char*)malloc(kMaxStrLen);
    if (pBuf) {
        sprintf(pBuf, "%d-%d-%d %d:%d", t_iYear, t_iMonth, t_iDay, t_iHour, t_iMin);
        t_oStrTarget.append(string(pBuf));
        free(pBuf);
    }
    return t_oStrTarget;
}

string getDate4()
{
    int t_iYear = 2013;
    int t_iMonth = 11;
    int t_iDay = 23;
    int t_iHour = 16;
    int t_iMin = 45;
    char sz[kMaxStrLen];
    sprintf(sz, "%d-%d-%d %d:%d", t_iYear, t_iMonth, t_iDay, t_iHour, t_iMin);
    return string(sz);
}

int main()
{
    cout << "getDate() -- " << getDate() << endl;
    cout << "getDate2() -- " << getDate2() << endl;
    cout << "getDate3() -- " << getDate3() << endl;
    cout << "getDate4() -- " << getDate4() << endl;
    return 0;
}

