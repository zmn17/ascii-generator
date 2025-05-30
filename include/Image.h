#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
class Image {
public:
	Image(const char* path);
	Image(const Image &) = default;
	~Image();

	uint8_t *getData();
	bool read_image(const char* path);
	bool write_image(const char* path);

	int getWidth();
	int getHeight();
	int getChannels();

private:
	int mWidth,mHeight,mChannels,mSize;
	uint8_t *mData;
	
};
#endif // !IMAGE_H IMAGE_H

