#include <iostream>
#include <string>
using namespace std;
wstring get_dms_by_location(double location) // -30.91°   to   -30°54′36.00″
{
    wchar_t buf[64]={0};
    bool sign = location > 0.0;
    int d = (int)location;
    location = (location - d) * 60;
    int m = (int)location;
    location = (location - m) * 60;
    if(sign)
        swprintf(buf, 63, L"+%d° %02d′ %05.2lf″", d, m, location);
    else
        swprintf(buf, 63, L"-%d° %02d′ %05.2lf″", d, m, location);
    return buf;
}
int main(void)
{
    wcout<<get_dms_by_location(123.350341);
 
    return 0;
}