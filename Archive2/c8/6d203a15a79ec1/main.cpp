#include <iostream>
#include <vector>
using namespace std;

template<int channel_count>
struct Channels {
    static constexpr int channels = channel_count;
};

template< int N >
class Cable
{
	public:
	const int channels = Channels<N>::channels;
	vector<float> audio[Channels<N>::channels];
	
	Cable(){
		for(int i = 0; i < Channels<N>::channels; i++){
			for(int s = 0; s < 5; s++){
				audio[i].push_back(i);
			}
		}
	}
	
};


int main() {
	
	Cable<3> c;
	
	cout << "num: " << c.channels << endl;
	for(int i = 0; i < c.channels; i++){
		cout << i << ": ";
		for(std::size_t s = 0; s < c.audio[i].size(); s++){
			cout << " " << c.audio[i][s];
		}
		cout << endl;
	}
}

