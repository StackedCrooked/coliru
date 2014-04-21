#include <iostream>
using namespace std;

template <typename T, typename Fn>
size_t partition(T arr[], size_t size, Fn&& fun)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    
    size_t index = 0;
    for(size_t i = 0; i < size; i++)
    {
        if (fun(arr[i]))
        {
            T tmp = arr[index];
            arr[index] = arr[i];
            arr[i] = tmp;
            index = i;
        }
        else
        {
            if(index == 0)
                index = i;
        }
    }
    return index;
}

template <typename T>
void printTable(T arr[], size_t size)
{
    cout << "[ ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "]\n";
}

template <typename T>
bool less10(T a)
{
    return a < 10;
}

int main() {
    int arri[] = {1,20,3,50,6,7};
    size_t sizi = sizeof(arri)/sizeof(arri[0]);
    printTable(arri, sizi);
    
    size_t fi = partition(arri,sizi, less10<int>);
    printTable(arri,sizi);
    cout << "index: " << fi << endl << endl;
    
    double arrd[] = {1,20,3,50,6,7};
    size_t sizd = sizeof(arrd)/sizeof(arrd[0]);
    printTable(arrd, sizd);
    
    size_t fd = partition(arrd,sizd, [] (double x) -> bool {return x > 10;});
    printTable(arrd,sizd);
    cout << "index: " << fd << endl;
}