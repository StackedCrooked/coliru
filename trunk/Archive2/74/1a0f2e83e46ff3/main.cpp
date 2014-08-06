#include <syslog.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sstream>
#include <map>
#include <cstdarg>
#include <cstring>


namespace util
{
    class StringConverter
	{
		private:
			std::string input;
			int recordLength;
			int index;
			int address;
			int inputLen;
			int asciiPosBegin;
			std::string result;
			int lineLength;
			int lines;
			int leftover;
			int i;
			char *buffer;
			const char *table = "0123456789ABCDEF";

			char *generateHexLine( int length );

		public:

			StringConverter( std::string &str, int width = 16 ) 
			:	input( str ),
				recordLength( width ),
				index(0),
				address(0),
				inputLen(input.length()),
				asciiPosBegin( 9 + (recordLength * 3)),
				result(""),
				lineLength(7 + (recordLength * 3) + ( 2 + recordLength )),
				lines(inputLen / recordLength),
				leftover(inputLen % recordLength)
			{}

			StringConverter( std::stringstream &data, int width = 16 ) 
			:	input( data.str() ),
				recordLength( width ),
				index(0),
				address(0),
				inputLen(input.length()),
				asciiPosBegin( 9 + (recordLength * 3)),
				result(""),
				lineLength(7 + (recordLength * 3) + ( 2 + recordLength )),
				lines(inputLen / recordLength),
				leftover(inputLen % recordLength)
			{}
			
			std::string &ToHex();
	};
	
	
	int numBytesInStream( std::stringstream &ss );

	
	char *StringConverter::generateHexLine( int length )
	{

		int asciiPos = asciiPosBegin;
		int hexPos = 7;
		int j;
		char temp[8];		// used to hold the address portion of a line in the hex dump

		memset( buffer, ' ', lineLength );
		buffer[lineLength] = 0x00;

		sprintf(temp,"%05d: ", address);
		memcpy( &buffer[0], temp, 7 );

		for( j = 0; j < length; j++ )
		{
			const unsigned char c = input[index++];
			buffer[hexPos++] = table[c >> 4];
			buffer[hexPos++] = table[c & 0x0F];
			hexPos++; // move past space
			
			// add ascii portion
			buffer[asciiPos++] =  (std::isprint(c)) ? c : '.';
		}
		buffer[asciiPos++] = 0x00;

		return( buffer );
	}

	std::string &StringConverter::ToHex()
	{
		if( (buffer = new char[lineLength]) != NULL )
		{
			if( lines > 0 )
			{
				// do all of the full lines
				for( i=0; i < lines; i++ )
				{
					result += generateHexLine( recordLength );
					result += '\n';
					address += recordLength;
				}
			}
			// now do final line of leftover
			if( leftover > 0 )
			{
				result += generateHexLine( leftover );
			}
			delete[] buffer;
		}
		
		// in some cases we may have added a trailing newline. remove it
		if( result.back() == '\n' )
		{
			result.pop_back();		// erases last character of string
		}
		return( result );
	}

	int numBytesInStream( std::stringstream &ss )
	{
		int length = 0;

		ss.seekg (0, ss.end);
		length = ss.tellg();
		ss.seekg (0, ss.beg);	

		return( length );
	}
}


namespace Log
{
	enum LogSource { SYSLOG, NETWORK };
	std::map<const LogSource, std::string> LogLocation =
	{
		{ SYSLOG, "syslog" },
		{ NETWORK, "Log/network.txt" }
	};
	
	class LogEntry
	{
		private:
			int logLevel;
			LogSource src;
			std::stringstream message;
			
		public:
			LogEntry( int level, LogSource src, const char *format, ... );
			LogEntry( int level, LogSource src, std::string s );
			LogEntry( int level, LogSource src );
			LogEntry() {};

			std::string Text() { return( message.str() ); }
			std::string Hex() { return( util::StringConverter(message).ToHex()); }
	};


	LogEntry::LogEntry( int level, LogSource src, const char *format, ... ) : logLevel( level ), src( src )
	{
		char *ptr = NULL;
		char byte;
		int numBytes = 0;
		va_list args;
		std::string result;
		
		// get the size of the buffer that will be needed.
		va_start (args, format);
		numBytes = vsnprintf (&byte,1,format, args) + 1;
		va_end (args);

		// this is all just to avoid having to create a buffer to hold the output of vsnprintf
		result.reserve( numBytes );
		ptr = (char *) &result[0];

		// create buffer and fill it
		va_start (args, format);
		vsnprintf (ptr,numBytes, format, args);
		va_end (args);
	
		message << std::string(ptr);
	}

	LogEntry::LogEntry( int level, LogSource src, std::string s )  : logLevel( level ), src( src )
	{
		message << s;
	}

	LogEntry::LogEntry( int level, LogSource src ) : logLevel( level ), src( src ) {}
}


class StringBuilder
{
	private:
		std::stringstream mStream;

	public:
		template <typename T> inline StringBuilder& operator<<(const T& t)
		{
			mStream << t;
			return * this;
		}
		inline std::string get() const
		{
			return mStream.str();
		}
		inline operator std::string () const
		{
			return get();
		}
};



int main ( int argc, char *argv[] )
{
	int i = 245;
	float f = 3.14159;

	// THIS JUST SHOWS THE NUMBER OF WAYS TO BUILD A LogEntry object which will be put on the Logging Services queue
	std::cout << Log::LogEntry( LOG_NOTICE, Log::NETWORK, StringBuilder() << "LOG1::This is a test " << i).Hex() << std::endl;
	std::cout << Log::LogEntry( LOG_NOTICE, Log::NETWORK, StringBuilder() << "LOG2::This is a test also " << i).Text() << std::endl;
	std::cout << Log::LogEntry( LOG_NOTICE, Log::SYSLOG, "LOG3::%f, %d", f,i ).Hex() << std::endl;
	std::cout << Log::LogEntry( LOG_NOTICE, Log::SYSLOG, "LOG4::THIS IS A TEST" ).Text() << std::endl;
	
	return(1);
}
