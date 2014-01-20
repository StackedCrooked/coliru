class Foo {
public :
    Foo() {}

	const static int samplerate = 44100;
	const static unsigned short tempo = 120;
	const static int numSamples = int( ( 4.0 / (tempo/60.0) ) * double(samplerate) );
};

