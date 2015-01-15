

int main()
{
    struct A{
        template <typename Type>
        void func(const Type*){}
    };
	return 0;
}
