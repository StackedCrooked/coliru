
struct item {};

int main()
{
    item i;
    new (&i) item();
}