#include <bits/stdc++.h>
#define _ std::ios_base::Init i; std::ios_base::sync_with_stdio(false); std::cin.tie(0);

using namespace std;

int main() { _
    string g;
	cin >> g;
	cout << g << endl;
	deque<char> SDS;
	for ( char a = 'A'; a <= 'Z'; a++ ) {
		SDS.push_front(a);
	}
	random_shuffle(SDS.begin(), SDS.end());
	
	for (auto g: SDS ){
		cout << g << " ";
	}
    
}
