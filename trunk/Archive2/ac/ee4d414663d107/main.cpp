// Approach A
template<typename Container>
Container loadFileContent(std::string filename)
{
	struct FileNotFoundException : public std::exception
	{
		FileNotFoundException() {}
	};

	std::ifstream file(filename, std::ios::binary);
	if(!file)
	{
		throw FileNotFoundException();
	}

	return Container(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}
    
static Texture createTextureFromWebpFile(std::string filepath)
{
	std::vector<char> rawData(util::loadFileContent<std::vector<char>>(filepath));

	int width, height;
	int error = WebPGetInfo(reinterpret_cast<uint8_t*>(rawData.data()), rawData.size() * sizeof(uint8_t), &width, &height);
	assert(error != 0);
    
    //... moar stuff
}

// Approach B
std::ifstream webpImageFile(filepath, std::ios_base::binary);
std::istream_iterator<uint8_t> begin(webpImageFile), end;
std::vector<uint8_t> rawData(begin, end);

int width, height;
// https://developers.google.com/speed/webp/docs/api#headers_and_libraries
int error = WebPGetInfo(rawData.data(), rawData.size() * sizeof(uint8_t), &width, &height);
