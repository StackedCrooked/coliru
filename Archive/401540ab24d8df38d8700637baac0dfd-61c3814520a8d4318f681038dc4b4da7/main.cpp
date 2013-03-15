
enum RGB { Red, Green, Blue };
    
int main()
{
    decltype(Blue) red = Green;
    decltype(Red) green = Blue;
    decltype(Green) blue = Red;
}