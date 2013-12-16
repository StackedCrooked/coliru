
struct ant { };
struct ent { ent& operator=(const ent&) &; };
    
int main()
{
    ant() = ant();
    ent() = ent();
    int() = int();
}
