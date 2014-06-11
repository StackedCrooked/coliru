struct my_class
{
    my_class() {}
    my_class(int, int) {}   
};

int main() 
{
  auto* objectPtr = new my_class[3]{{1,2},
                                    {}, 
                                    {3,4}};
}