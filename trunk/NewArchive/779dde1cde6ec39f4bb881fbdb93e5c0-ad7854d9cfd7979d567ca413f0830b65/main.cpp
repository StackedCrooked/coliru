#include <iostream>

//These are handy bits that go in a header somewhere
template<class e, class t, int N>
std::basic_istream<e,t>& operator>>(std::basic_istream<e,t>& in, const e(&sliteral)[N]) {
        e buffer[N-1] = {}; //get buffer
        in >> buffer[0]; //skips whitespace
        if (N>2)
                in.read(buffer+1, N-2); //read the rest
        if (strncmp(buffer, sliteral, N-1)) //if it failed
                in.setstate(in.rdstate() | std::ios::badbit); //set the state
        return in;
}
template<class e, class t>
std::basic_istream<e,t>& operator>>(std::basic_istream<e,t>& in, const e& cliteral) {
        e buffer(0);  //get buffer
        in >> buffer; //read data
        if (buffer != cliteral) //if it failed
                in.setstate(in.rdstate() | std::ios::badbit); //set the state
        return in;
}
//redirect mutable char arrays to their normal function
template<class e, class t, int N>
std::basic_istream<e,t>& operator>>(std::basic_istream<e,t>& in, e(&carray)[N]) {
        return std::operator>>(in, carray);
}














//fscanf(fin, "x = %d, y = %d", &x, &y);

std::istream& operator>>(std::istream& in, std::pair<int, int>&data) 
{return in>>'x'>>'='>>data.first>>','>>'y'>>'='>>data.second;}

#include <sstream>
int main() {
    std::stringstream ss;
    std::pair<int,int> data;
    
    ss.clear();
    ss.str("x=12,y=42");
    ss >> data;
    std::cout << data.first << ',' << data.second << '\n';
    
    ss.clear();
    ss.str("x = 23 , y = 53 ");
    ss >> data;
    std::cout << data.first << ',' << data.second << '\n';
}
