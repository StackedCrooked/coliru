#include <Furrovine++/Graphics/Image2D.h>

namespace Furrovine { namespace Pipeline {

    class BMPLoader {
    public:

		bool IgnoreHeader;
		int ColorMapCount, ContainerWidth, ContainerHeight;


		furrovinememberapi BMPLoader ( bool ignoreheader = false, int colormapcount = 0, int containerwidth = 0, int containerheight = 0 );

		Graphics::Image2D Load ( const String& path );
		Graphics::Image2D Load ( IO::Stream& stream );
		Graphics::Image2D Load ( IO::ByteReader& reader );
		Graphics::Image2D operator() ( const String& path );
		Graphics::Image2D operator() ( IO::Stream& stream );
		Graphics::Image2D operator() ( IO::ByteReader& reader );

	};

}}