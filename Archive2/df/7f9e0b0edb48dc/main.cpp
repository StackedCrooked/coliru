
class C
{
  public:
    static const void* noop;
};

const void* C::noop = reinterpret_cast<const void *>(0x1);

int main()
{

}