#include <iostream>
#include <vector>
using namespace std;

template<int channel_count>
struct Channels {
    static constexpr int channels = channel_count;
};

template< int N, template<int> class T >
class Cable
{
	public:
	const int channels = T<N>::channels;
	vector<float> audio[T<N>::channels];
	
	Cable(){
		for(int i = 0; i < T<N>::channels; i++){
			for(int s = 0; s < 5; s++){
				audio[i].push_back(i);
			}
		}
	}
	
};


int main() {
	
	Cable< 3, Channels > c;
	
	cout << "num: " << c.channels << endl;
	for(int i = 0; i < c.channels; i++){
		cout << i << ": ";
		for(std::size_t s = 0; s < c.audio[i].size(); s++){
			cout << " " << c.audio[i][s];
		}
		cout << endl;
	}
}

