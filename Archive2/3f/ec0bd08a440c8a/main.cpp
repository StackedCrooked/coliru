template<typename out, typename in>
out fnk(out(*ptr)(in))
{ return out(); }
 
template<typename out, typename in>
out fnk(out(*ptr)(in, ...), ...)
{ return out(); }
 
int print(const char*, ...)
{ return 12; }
 
int print(const char*)
{ return 12; }
 
int main()
{
    fnk(static_cast<int (*)(const char*)>(&print));
    fnk(&print, 5);
}