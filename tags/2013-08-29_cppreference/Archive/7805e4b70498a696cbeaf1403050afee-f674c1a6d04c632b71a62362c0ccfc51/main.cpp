template<class callback_t, class input_data_t = float, class output_data_t = float>
static AudioStream<input_data_t, output_data_t>
openStream(boost::optional<AudioStreamParameters<input_data_t>> inputParams,
           boost::optional<AudioStreamParameters<output_data_t>> outputParams,
           double sampleRate,
           unsigned long framesPerBuffer,
           int flags,
           callback_t callback)
	{
	return AudioStream<input_data_t, output_data_t>(inputParams, outputParams, sampleRate, framesPerBuffer, flags, callback);
}

auto stream = Centurion::openStream(
	boost::optional<Centurion::AudioStreamParameters<float>>(),                     // I need these explicit boost::optional constructors or else
	boost::make_optional(Centurion::AudioStreamParameters<float>(dev, 2, 10.0)),    // I get "no matching function for call to 'openStream' "
	44100,                                                                          // e.g. the example below fails
	0,                                                                              //   |
	0,                                                                              //   |
	SineWaveGenerator()                                                             //   |
);                                                                                  //   |
//      +--------------------------------------------------------------------------------+
//      |
//     \/
auto stream = Centurion::openStream(
	boost::none,                                            // These cause it to fail 
	Centurion::AudioStreamParameters<float>(dev, 2, 10.0),  //
	44100,
	0,
	0,
	SineWaveGenerator()
);