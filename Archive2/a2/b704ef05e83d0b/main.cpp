typedef struct HWAV__ *HWAV; //public handle to wave data
typedef struct { //private internal data structure
    //blah blah blah
}WAV, *LPWAV;

// Private Internal Functions:
// WavGetHandle - verify that wav pointer is valid,
//    	<lpWav>				(i) pointer to WAV struct
// return corresponding wav handle (NULL if error)
//
static HWAV WavGetHandle(LPWAV lpWav)
{
	BOOL fSuccess = TRUE;
	HWAV hWav;

	if ((hWav = (HWAV) lpWav) == NULL)
		fSuccess = FALSE;

	return fSuccess ? hWav : NULL;
}