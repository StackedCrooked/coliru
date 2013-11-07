std::ifstream webpImageFile(filepath, std::ios_base::binary);
std::istream_iterator<uint8_t> begin(webpImageFile), end;
std::vector<uint8_t> rawData(begin, end);

int width, height;
// https://developers.google.com/speed/webp/docs/api#headers_and_libraries
int error = WebPGetInfo(rawData.data(), rawData.size() * sizeof(uint8_t), &width, &height);

std::unique_ptr<unsigned char> imageData(WebPDecodeRGBA(rawData.data(), rawData.size() * sizeof(uint8_t), &width, &height));