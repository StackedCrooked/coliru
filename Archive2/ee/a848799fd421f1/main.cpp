struct Abstract
{
virtual void work() = 0;
};

class B : public Abstract
{
void work() const;
};

int main( void )
{
Abstract* a = new B();
a->work();
}