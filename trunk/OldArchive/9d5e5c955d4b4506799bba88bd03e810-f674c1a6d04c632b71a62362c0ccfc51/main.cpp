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