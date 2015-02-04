#include <iostream>
#include <vector>
#include <locale>
#include <sstream>
 
struct ctype_russian : std::ctype<char>
{
static const mask* make_table()
{
static std::vector<mask> v{classic_table(), classic_table() + table_size};
for(char c: "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") {
v[(unsigned char)c] &= ~alpha;
v[(unsigned char)c] |= space;
}
for(char c: "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ") {
v[(unsigned char)c] |= alpha;
v[(unsigned char)c] &= ~space;
}
return &v[0];
}
ctype_russian(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
};
 
int main()
{
std::string in = "English words Русские слова English again";
std::istringstream s(in);
s.imbue(std::locale(s.getloc(), new ctype_russian()));
std::string token;
while (s >> token)
std::cout << " " << token << '\n';
}