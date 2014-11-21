#include <iostream>
#include <vector>
#include <type_traits>

template<typename Ptr, typename T, 
    typename = typename std::enable_if<std::is_same<Ptr, T>::value>::type>
Ptr split_array(Ptr arr, std::vector<int>& dims) {
    return arr;
}

template<typename Ptr, typename T, 
    typename = typename std::enable_if<!std::is_same<Ptr, T>::value>::type>
Ptr split_array(T arr, std::vector<int>& dims) {
	T* out = new T[dims[dims.size()-2]];
	
	for (int i = 0; i < dims[dims.size() - 2]; i++)
		out[i] = &arr[i * dims.back()];
		
	dims.pop_back();
	return split_array<Ptr, T*>(out, dims);
}

int main() {
	int arr[125];
	for (int i = 0; i < 125; i++)
		arr[i] = i;
		
	std::vector<int> dims(3,5);
	int *** ar = split_array<int***>(arr, dims);
	
	std::cout << ar[4][4][4] << std::endl;
	return 0;
}