#pragma once
#include <iostream>
#include <portaudio.h>
#include <functional>
#include <boost/optional/optional.hpp>
#include "SampleFormat.hpp"
#include "AudioDevice.hpp"
#include "AudioStreamParameters.hpp"
#include "Error.hpp"

namespace Centurion {
    class AudioDevice;
    class AudioStream {
        private:
            boost::any dispatchfunctor;
            
        public:
            template<class functor_t, class input_data_t, class output_data_t>
            AudioStream(boost::optional<AudioStreamParameters<input_data_t>> inputParams,
                        boost::optional<AudioStreamParameters<output_data_t>> outputParams,
                        double sampleRate,
                        unsigned long framesPerBuffer, // or 0 for auto
                        int flags, //TODO
                        functor_t callback) {
                PaStreamParameters inparams;
                PaStreamParameters* inparams_ptr = nullptr;
                if(inputParams) {
                    inparams = *inputParams;
                    inparams_ptr = &inparams;
                }
                PaStreamParameters outparams;
                PaStreamParameters* outparams_ptr = nullptr;
                if(outputParams) {
                    outparams = *outputParams;
                    outparams_ptr = &outparams;
                }
                // Store the dispatch functor
                dispatchfunctor = callback;
                //
                paErrorChecked(
                    Pa_OpenStream,
                        &handle,
                        inparams_ptr, //in
                        outparams_ptr,
                        sampleRate,
                        framesPerBuffer,
                        flags,
                        &CallbackDispatcher<functor_t>,
                        // Fix this
                        //reinterpret_cast<void*>(&callback)
                        // However this boost nonsense is supposed to work:
                        reinterpret_cast<void*>(&boost::any_cast<functor_t>( dispatchfunctor ))
                );
            }
            
            void Start() {
                paErrorChecked(Pa_StartStream, handle);
            }
                        
        private:
            PaStream* handle;
            
            template<class functor_t>
            static int CallbackDispatcher(const void* input,
                                          void* output,
                                          unsigned long frameCount,
                                          const PaStreamCallbackTimeInfo* timeInfo,
                                          PaStreamCallbackFlags statusFlags,
                                          void* userData) {
            return (*static_cast<functor_t*>(userData))(
                input, //Todo: make this statically typed
                output, //Todo: make this statically type
                frameCount,
                timeInfo,
                statusFlags
            );
          }
    };
}