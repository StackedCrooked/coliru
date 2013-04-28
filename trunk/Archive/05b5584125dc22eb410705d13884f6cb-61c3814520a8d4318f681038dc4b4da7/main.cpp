width = FreeImage_GetWidth(handle);
height = FreeImage_GetHeight(handle);

auto pitch = FreeImage_GetPitch(handle);
BYTE* pixel_it = FreeImage_GetBits(handle);
for(int y = 0; y < height; y++) {
	BYTE* pixel = pixel_it;
	for(int x = 0; x < width; x++) {
		data.push_back(static_cast<float>(pixel[FI_RGBA_RED]) / 255.0f);
		data.push_back(static_cast<float>(pixel[FI_RGBA_GREEN]) / 255.0f);
		data.push_back(static_cast<float>(pixel[FI_RGBA_BLUE]) / 255.0f);
		data.push_back(1.0f);
		pixel += 3;
	}
	pixel_it += pitch;
}