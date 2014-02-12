#include <iostream>
#include <string>
#include <stdexcept>

#define interface struct
#define throws throw
#define implements : public
#define new
using RunTimeError = std::runtime_error ;
using String = std::string ;
#define null nullptr

interface OutputDevice {

    virtual ~OutputDevice() = default ;
    virtual void print( int i ) throws(RunTimeError) = 0 ;
    virtual void println( String& s ) throws(RunTimeError) = 0 ;
};


interface InputDevice {

    virtual ~InputDevice() = default ;
    virtual int getInt() throws(RunTimeError) = 0 ;
};


interface OutputDeviceProvider {

    virtual OutputDevice&  getOutputDevice() throws(RunTimeError) = 0 ;
};


interface InputDeviceProvider {

    virtual InputDevice&  getInputDevice() throws(RunTimeError) = 0 ;
};


class StdoutDevice final implements OutputDevice {

    public: void print( int i ) throws(RunTimeError) {

        if( !( std::cout << i ) )
            throw new RunTimeError("output error") ;
    }

    public: void println( String& s ) throws(RunTimeError) {

        if( !( std::cout << s << '\n' ) )
            throw new RunTimeError("output error") ;
    }

    public: operator const void* () const { return std::cout ? this : null  ; }
};


class StdinDevice final implements InputDevice {

    public: virtual int getInt() throws(RunTimeError) {

        int x ;
        if( !( std::cin >> x ) )
            throw new RunTimeError("invalid input") ;
        return x ;
    };
    public: operator const void* () const { return std::cin ? this : null ; }
};


class DefaultOutputDeviceProvider final implements OutputDeviceProvider {

    public: OutputDevice& getOutputDevice() throws(RunTimeError) {

        if( defaultOutputDevice == null )
            throw new RunTimeError( "failed to get a good default output device") ;

        return defaultOutputDevice ;
    }

    private: static StdoutDevice defaultOutputDevice ;
};

StdoutDevice DefaultOutputDeviceProvider::defaultOutputDevice ;


class DefaultInputDeviceProvider final implements InputDeviceProvider {

    public: InputDevice& getInputDevice() throws(RunTimeError) {

        if( defaultInputDevice == null )
            throw new RunTimeError( "failed to get a good default input device") ;

        return defaultInputDevice ;
    }

    private: static StdinDevice defaultInputDevice ;
};

StdinDevice DefaultInputDeviceProvider::defaultInputDevice ;


int main() {

    int iX = 0; // test comment
    
	int iaY[] = {1, 2};

	try {

	    InputDeviceProvider&& defaultInputDeviceProvider = new DefaultInputDeviceProvider() ;
        InputDevice& defaultInputDevice = defaultInputDeviceProvider.getInputDevice() ;

        iX = defaultInputDevice.getInt() ;

        OutputDeviceProvider&& defaultOutputDeviceProvider = new DefaultOutputDeviceProvider() ;
        OutputDevice& defaultOutputDevice = defaultOutputDeviceProvider.getOutputDevice() ;

        for( int iZ = 2 ; iZ < 10; ++iZ ) {

            defaultOutputDevice.print(iZ) ;
            String nullString = new String("") ;
            defaultOutputDevice.println(nullString) ;
        }
	}

    catch(RunTimeError) {

        String errorMessage = new String("this is bad") ;

	    // ErrorMessageProvider&& defaultErrorMessageProvider = new DefaultErrorMessageProvider() ;
        // ErrorMessage errorMessage = defaultErrorMessageProvider.getDefaultErrorMessage() ;

        try {

            // ErrorMessageProvider&& defaultErrorMessageProvider = new DefaultErrorMessageProvider() ;
            // ErrorMessage errorMessage = defaultErrorMessageProvider.getDefaultErrorMessage() ;

            OutputDeviceProvider&& defaultOutputDeviceProvider = new DefaultOutputDeviceProvider() ;
            OutputDevice& defaultOutputDevice = defaultOutputDeviceProvider.getOutputDevice() ;
            defaultOutputDevice.println(errorMessage) ;
        }

        catch( RunTimeError ) {

            // give up
        }
    }
}
