template<typename T>
void func(T* ptr, int count) { }

int main()
{
    float f_arr[42] = {};
    float i_arr[84] = {};
    
    func(f_arr, 42);
    func(i_arr, 84);
}