#include <iostream>
#include <vector>
using namespace std;

template<int channel_count>
struct Channels {
    static constexpr int channels = channel_count;
};

template< typename T >
class Cable
{
	public:
	const int channels = T::channels;
	vector<float> audio[T::channels];
	
	Cable(){
		for(int i = 0; i < T::channels; i++){
			for(int s = 0; s < 5; s++){
				audio[i].push_back(i);
			}
		}
	}
	
};


int main() {
	
	Cable<Channels<3>> c;
	
	cout << "num: " << c.channels << endl;
	for(int i = 0; i < c.channels; i++){
		cout << i << ": ";
		for(int s = 0; s < c.audio[i].size(); s++){
			cout << " " << c.audio[i][s];
		}
		cout << endl;
	}
}

