#ifndef ASCII_H
#define ASCII_H

#include "Image.h"
#include <fstream>

class AsciiEngine {
public:
	AsciiEngine(Image& img);
	~AsciiEngine();

	// 4. output the ascii into a file
	void genAsciiArt();

	int getHeightMat();
	int getWidthMat();


private:
	// 1. load image data into 2D array/matrix
	int** genPixelMat();
	// 2. take the avg of R,G,B and store them
	int** genBrightnessMat(int** pixelMat);
	//	  into brightnees matrix
	// 3. map the brightnees to ascii characters-matrix
	char** genAsciiMat(int** brightneesMat);

	void loginfo(const char* func_name);

	Image& image;
	int mHeightMat, mWidthMat;
	std::string ascii_chars = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
};
#endif // !ASCII_H
