AudioStream(AudioDevice& inputDevice,
            int inputChannelCount,
            SampleFormat, inputSampleFormat,
            double suggestedInputLatency
            AudioDevice& outputDevice,
            int outputChannelCount,
            SampleFormat, outputSampleFormat,
            double suggestedOutputLatency
            double sampleRate,
            unsigned long framesPerBuffer,
            flags,
            functor_t callback);