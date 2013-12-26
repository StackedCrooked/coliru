   #include <array>
     
struct line
{
int pos_a;
int pos_b;
int pos_c;
};
 

int main() {
std::array<line, 8> lines = {{
{ 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 }, { 1, 5, 9 }, { 3, 5, 7 }
}};
 
}
