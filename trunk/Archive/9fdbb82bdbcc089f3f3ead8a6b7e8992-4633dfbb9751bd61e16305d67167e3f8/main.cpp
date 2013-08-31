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

/*
In file included from src/main.cpp:2:
In file included from include/AudioStream.hpp:4:
/usr/include/c++/4.6/functional:535:20: error: left hand operand to .* must be a class compatible with the right hand operand, but is 'Buffered ()'
        { return ((*__ptr).*__pmf)(std::forward<_ArgTypes>(__args)...); }
                          ^
/usr/include/c++/4.6/functional:557:11: note: in instantiation of function template specialization 'std::_Mem_fn<int (Buffered::*)(const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)>::_M_call<Buffered (*)()>'
      requested here
          return _M_call(__object, &__object,
                 ^
/usr/include/c++/4.6/functional:1144:11: note: in instantiation of function template specialization 'std::_Mem_fn<int (Buffered::*)(const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)>::operator()<Buffered
      (*)()>' requested here
          return _M_f(_Mu<_Bound_args>()
                 ^
/usr/include/c++/4.6/functional:1202:17: note: in instantiation of function template specialization 'std::_Bind<std::_Mem_fn<int (Buffered::*)(const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)> (Buffered
      (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)>::__call<int, const float *&&, unsigned long &&, const PaStreamCallbackTimeInfo *&&, unsigned long &&, 0, 1, 2, 3, 4>' requested here
          return this->__call<_Result>(
                       ^
/usr/include/c++/4.6/functional:1762:9: note: in instantiation of function template specialization 'std::_Bind<std::_Mem_fn<int (Buffered::*)(const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)> (Buffered
      (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)>::operator()<const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long, int>' requested here
        return (*_Base::_M_get_pointer(__functor))(
               ^
/usr/include/c++/4.6/functional:2147:33: note: in instantiation of member function 'std::_Function_handler<int (const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long), std::_Bind<std::_Mem_fn<int
      (Buffered::*)(const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)> (Buffered (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)> >::_M_invoke' requested here
            _M_invoker = &_My_handler::_M_invoke;
                                       ^
include/AudioStream.hpp:45:49: note: in instantiation of function template specialization 'std::function<int (const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)>::function<std::_Bind<std::_Mem_fn<int
      (Buffered::*)(const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)> (Buffered (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)> >' requested here
                                     callback_t callback_function) : callback(callback_function) {
                                                                     ^
include/AudioStream.hpp:83:10: note: in instantiation of function template specialization 'Centurion::AudioIStream<float>::AudioIStream<std::_Bind<std::_Mem_fn<int (Buffered::*)(const float *, unsigned long, const
      PaStreamCallbackTimeInfo *, unsigned long)> (Buffered (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)> >' requested here
                return AudioIStream<input_data_t>(params, sampleRate, framesPerBuffer, flags, callback);
                       ^
src/main.cpp:56:18: note: in instantiation of function template specialization 'Centurion::openAudioIStream<std::_Bind<std::_Mem_fn<int (Buffered::*)(const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)>
      (Buffered (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)>, float>' requested here
        auto instream = Centurion::openAudioIStream(
                        ^
In file included from src/main.cpp:2:
In file included from include/AudioStream.hpp:4:
/usr/include/c++/4.6/functional:1762:9: error: no matching function for call to object of type 'std::_Bind<std::_Mem_fn<int (Buffered::*)(float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)> (Buffered (*)(),
      std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)>'
        return (*_Base::_M_get_pointer(__functor))(
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/usr/include/c++/4.6/functional:2147:33: note: in instantiation of member function 'std::_Function_handler<int (const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long), std::_Bind<std::_Mem_fn<int
      (Buffered::*)(float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)> (Buffered (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)> >::_M_invoke' requested here
            _M_invoker = &_My_handler::_M_invoke;
                                       ^
include/AudioStream.hpp:45:49: note: in instantiation of function template specialization 'std::function<int (const float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)>::function<std::_Bind<std::_Mem_fn<int
      (Buffered::*)(float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)> (Buffered (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)> >' requested here
                                     callback_t callback_function) : callback(callback_function) {
                                                                     ^
include/AudioStream.hpp:83:10: note: in instantiation of function template specialization 'Centurion::AudioIStream<float>::AudioIStream<std::_Bind<std::_Mem_fn<int (Buffered::*)(float *, unsigned long, const PaStreamCallbackTimeInfo *,
      unsigned long)> (Buffered (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)> >' requested here
                return AudioIStream<input_data_t>(params, sampleRate, framesPerBuffer, flags, callback);
                       ^
src/main.cpp:63:19: note: in instantiation of function template specialization 'Centurion::openAudioIStream<std::_Bind<std::_Mem_fn<int (Buffered::*)(float *, unsigned long, const PaStreamCallbackTimeInfo *, unsigned long)> (Buffered
      (*)(), std::_Placeholder<1>, std::_Placeholder<2>, std::_Placeholder<3>, std::_Placeholder<4>)>, float>' requested here
        auto outstream = Centurion::openAudioIStream(
                         ^
/usr/include/c++/4.6/functional:1200:2: note: candidate template ignored: couldn't infer template argument '_Result'
        operator()(_Args&&... __args)
        ^
/usr/include/c++/4.6/functional:1214:2: note: candidate template ignored: couldn't infer template argument '_Result'
        operator()(_Args&&... __args) const
        ^
/usr/include/c++/4.6/functional:1228:2: note: candidate template ignored: couldn't infer template argument '_Result'
        operator()(_Args&&... __args) volatile
        ^
/usr/include/c++/4.6/functional:1242:2: note: candidate template ignored: couldn't infer template argument '_Result'
        operator()(_Args&&... __args) const volatile
        ^
2 errors generated.
*/