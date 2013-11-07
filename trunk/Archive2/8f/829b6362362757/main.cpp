#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include <cstring>

#define TEXTURE_TYPES \
    textype(DIFFUSE), \
	textype(SPECULAR),\
	textype(ALPHA),   \
	textype(BUMP)

#define textype(tex) TEXTURE_##tex

class TextureType
{
public:

	enum TextureTypeE { TEXTURE_TYPES };

#undef textype
#define textype(tex) #tex

	static std::string toString(TextureTypeE t) 
	{ return TextureType::textureStrings[static_cast<int>(t)]; }

private:
	static const std::string textureStrings[];
};

const std::string TextureType::textureStrings[] = { TEXTURE_TYPES };

int main (int argc, char *argv[])
{
    std::cout << "A texture : " << TextureType::toString(TextureType::TEXTURE_DIFFUSE) << "\n";
    return 0;
}