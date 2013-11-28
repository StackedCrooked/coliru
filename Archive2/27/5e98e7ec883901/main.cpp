#include <iostream>
#include <string> 
using namespace std;

char in [(int)2e5],
     out[(int)2e5];

int main(){
	int k, n = 0;

//	cin >> k;
    k = 4;
    in[0] = '1';
    in[1] = '2';
    in[2] = '3';
    in[3] = '2';
    in[4] = '1';
    n = 5;
//    while (cin.peek() != char_traits<char>::eof()){
//		cin >> in[n++];
//	}

	int last = 0;
	for(int i = 0; i < n; i++){
		for(int j = max(k - (n - i), 0); j <= last; j++){
			if(out[j] < in[i]){
				out[j] = in[i];
				if(j + 1 < k){
					last = j + 1;
                    out[last] = 0;
                }
				break;
			}
		}
	}

	for(int i = 0; i < k; i++)
		cout << out[i];
            
	return 0;	
}