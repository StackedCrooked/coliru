class Stream {
public:
	furrovinememberapi virtual StreamFlag Capabilities () = 0;
	furrovinememberapi virtual bool CanSeek () = 0;
	furrovinememberapi virtual bool CanRead () = 0;
	furrovinememberapi virtual bool CanWrite () = 0;
	furrovinememberapi virtual bool CanTimeout () = 0;
	furrovinememberapi virtual bool EoS () = 0;
	furrovinememberapi virtual bool IsOpen () = 0;

	furrovinememberapi virtual int ReadTimeout () = 0;
	furrovinememberapi virtual int WriteTimeout () = 0;

	furrovinememberapi virtual int64 Length () = 0;
	furrovinememberapi virtual int64 Position () = 0;

	furrovinememberapi virtual void Close () = 0;
	furrovinememberapi virtual void Flush () = 0;

	furrovinememberapi virtual int64 Seek (int64 position) = 0;
	furrovinememberapi virtual int64 Seek (int64 offset, SeekOrigin origin) = 0;
	furrovinememberapi virtual int64 SetLength (int64 length) = 0;
	furrovinememberapi virtual int64 SetPosition (int64 position) = 0;

	furrovinememberapi virtual int PeekByte () = 0;
	furrovinememberapi virtual int ReadByte () = 0;
	furrovinememberapi virtual lword Read ( byte* bytes, lword count ) = 0;
	furrovinememberapi virtual lword Read ( byte* bytes, lword start, lword count ) = 0;
	furrovinememberapi virtual lword Read ( void* bytes, lword bytecount ) = 0;

	furrovinememberapi virtual void WriteByte ( byte b ) = 0;
	furrovinememberapi virtual void Write ( byte* bytes, lword count ) = 0;
	furrovinememberapi virtual void Write ( byte* bytes, lword start, lword count ) = 0;

	furrovinememberapi virtual ~Stream () {}
};

int main() {
    
    
}