#include <iostream>

#include <boost/circular_buffer.hpp>

struct PaStreamCallbackTimeInfo;
enum PaStreamCallbackFlags { PaStreamCallback_DummyFlag };
constexpr int paContinue = 1;

class Buffered {
    boost::circular_buffer<float> buffer;
    public:
		Buffered() : buffer(1200) {
		}
		int read(const float* input, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags) {
			for(auto i = 0; i != frameCount; i++) {
				buffer.push_back(*(input + i));
			}
			return paContinue;
		}
		int write(float* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags) {
			for(auto i = 0; i != frameCount; i++) {
				if(buffer.empty()) {
					*output++ = 0.0f;
				} else {
					*output++ = buffer.front();
					buffer.pop_front();
				}
			}
			return paContinue;
		}
};

int main() {
	using namespace std::placeholders;

	Buffered b {};
    std::bind(&Buffered::read, &b, _1, _2, _3, _4) (nullptr, 1ul, nullptr, PaStreamCallback_DummyFlag);
    std::bind(&Buffered::write, &b, _1, _2, _3, _4)(nullptr, 1ul, nullptr, PaStreamCallback_DummyFlag);
}
