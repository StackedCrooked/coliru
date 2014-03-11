#include <string.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;
using namespace std::chrono;

template<typename Fun>
void profile_in_micro(Fun&& f)
{
    auto now = high_resolution_clock::now();
    f();
    cout << 
        duration_cast<microseconds>(
            high_resolution_clock::now() - now).count() << endl; 
}

template<size_t N>
void ruota_inplace(int (&v)[N], int n)
{
	while(n--)
	{
		auto temp = v[0];
		for(int j=0; j<N; j++)
		{
			v[j]=v[j+1];
		}
		v[N-1]=temp;
	}
}

void ruota_inplace(vector<int>& v, int n)
{
	const auto N = v.size();
	n = n%N;
	while(n--)
	{
		auto temp = v[0];
		for(auto j=0u; j<N; j++)
		{
			v[j]=v[j+1];
		}
		v[N-1]=temp;
	}
}

template<size_t N>
void ruota_memmove(int (&arr)[N], int n)
{
	if (n<=0)
		return;
	auto rest = (n%N);
	auto toMoveSize = N - rest;
	int tmp[N];

	memcpy( tmp, arr, sizeof(int) * N );
	memmove( arr, &(tmp[rest]), sizeof(int) * toMoveSize );
	memcpy( &arr[toMoveSize], tmp, sizeof(int) * rest );
}

void ruota_memmove(vector<int>& arr, int n)
{
	const auto size = arr.size();
	if (n<=0)
		return;
	auto rest = (n%size);
	auto toMoveSize = size - rest;
	vector<int> tmp(size); 

	memcpy( tmp.data(), arr.data(), sizeof(int) * size );
	memmove( arr.data(), &(tmp[rest]), sizeof(int) * toMoveSize );
	memmove( &arr[toMoveSize], tmp.data(), sizeof(int) * rest);
}

int main()
{
    vector<int> bigVec(800000);
    vector<int> smallVec(65535);
    int arr[65535]{};
	iota(begin(arr), end(arr), 1);
	cout << "stack array memmove: ";
	profile_in_micro([&](){
		ruota_memmove(arr, 100);	
	});
	cout << "stack array inplace: ";
	profile_in_micro([&](){
		ruota_inplace(arr, 100);	
	});
	cout << "small vector memmove: ";
	profile_in_micro([&](){
		ruota_memmove(smallVec, 100);	
	});
	cout << "small vector inplace: ";
	profile_in_micro([&](){
		ruota_inplace(smallVec, 100);	
	});
		cout << "big vector memmove: ";
	profile_in_micro([&](){
		ruota_memmove(bigVec, 100);	
	});
	cout << "big vector inplace: ";
	profile_in_micro([&](){
		ruota_inplace(bigVec, 100);	
	});
}
