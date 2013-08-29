#include "AudioDevice.hpp"
#include "AudioStream.hpp"
#include "AudioStreamParameters.hpp"
#include <iostream>
#include <portaudio.h>
#include <opus/opus.h>

#include <boost/circular_buffer.hpp>

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

	Pa_Initialize();
	std::cout << "-------------------------------\n";
	Buffered b();
	auto instream = Centurion::openAudioIStream(
		Centurion::AudioStreamParameters<float>(Centurion::AudioDevice::defaultInputDevice(), 1, 0.05),
		41100,
		400,
		0,
		std::bind(&Buffered::read, &b, _1, _2, _3, _4) // This doesn't work and can't work out why :(
	);
	auto outstream = Centurion::openAudioIStream(
		Centurion::AudioStreamParameters<float>(Centurion::AudioDevice::defaultOutputDevice(), 1, 0.05),
		41100,
		400,
		0,
		std::bind(&Buffered::write, &b, _1, _2, _3, _4) // This doesn't work and can't work out why :(
	);
	instream.Start();
	outstream.Start();
	Pa_Sleep(6 * 1000);
	return 0;
}