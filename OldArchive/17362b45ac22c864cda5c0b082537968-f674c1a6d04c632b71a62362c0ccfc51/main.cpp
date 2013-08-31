auto stream = Centurion::openAudioOStream(
	Centurion::AudioStreamParameters<float>(Centurion::AudioDevice::defaultOutputDevice(), 2, 10.0),
	44100,
	0,
	0,
	SineWaveGenerator()
);