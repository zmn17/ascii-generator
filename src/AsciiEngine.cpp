#include "../include/AsciiEngine.h"
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "../include/Image.h"

AsciiEngine::AsciiEngine(Image& img):image(img){
}

AsciiEngine::~AsciiEngine(){
}

// 1. load image data into 2D array/matrix
int** AsciiEngine::genPixelMat(){
	// Image data and info
	int width = image.getWidth();
	int height = image.getHeight();
	int channels = image.getChannels();
	uint8_t* data = image.getData();

	// create a 2D matrix
	int** pixels = (int**)malloc(height * sizeof(int*));
	if(pixels == nullptr){
		std::cerr<<"\033[1;31m[ERROR]:\033[0m"<<"Failed to create pixel matrix.\n"<<std::endl;
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < height; ++i){
		pixels[i] = (int*)malloc(width * channels * sizeof(int));
	}

	// fill the matrix with the image data
	for(int rows = 0; rows < height; ++rows){
		for(int cols = 0; cols < width; ++cols){
			int index = (rows * width + cols) * channels;
			unsigned char r = data[index + 0];
			unsigned char g = data[index + 1];
			unsigned char b = data[index + 2];

			// fill into pixels matrix
			int pixelIndex = rows * image.getWidth() + cols;
	 		pixels[rows][cols * channels + 0] = (int)r;
			pixels[rows][cols * channels + 1] = (int)g;
			pixels[rows][cols * channels + 2] = (int)b;
		}
	}

	loginfo("Pixels Matrix");
	return pixels;

}
// 2. take the avg of R,G,B and store them
int** AsciiEngine::genBrightnessMat(int** pixelsMat){
	// create matrix
	int** brightness = (int**)malloc(image.getHeight() * sizeof(int *));
	if(brightness == nullptr){
		std::cerr<<"Brightness matrix creation failed.\n";
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < image.getHeight(); ++i){
		brightness[i] = (int*)malloc(image.getWidth() * sizeof(int));
	}
	// get the average of rgb values = brightness
	int average;
	for(int row = 0; row < image.getHeight(); ++row){
		for(int col = 0; col < image.getWidth(); ++col){
			// R, G , B - get it from pixels matrix
			int channels = image.getChannels();
			int rvalue = pixelsMat[row][col * channels + 0];
			int gvalue = pixelsMat[row][col * channels + 1];
			int bvalue = pixelsMat[row][col * channels + 2];

			// take the average of R,G,B -> brightness value
			average = (rvalue + gvalue + bvalue) / 3;
			brightness[row][col] = average;

		}
	}
	loginfo("Brightness Matrix");

	return brightness;
}
//	  into brightnees matrix
// 3. map the brightnees to ascii characters-matrix
char** AsciiEngine::genAsciiMat(int** brightneesMat){
	// create ASCII characters matrix
	char** ascii = (char**)malloc(image.getHeight() * sizeof(char*));

	if(ascii == nullptr){
		std::cerr<<"ASCII matrix creation failed.\n";
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < image.getHeight(); ++i){
		ascii[i] = (char*)malloc(image.getWidth() * sizeof(char));
	}


	int num_chars = strlen(ascii_chars.c_str());

	for(int row = 0; row < image.getHeight(); ++row){
		for(int col = 0; col < image.getWidth(); ++col){
			// normalize brightness from 0-255 into an index from 0-[num of chars - 1]
			int index = (brightneesMat[row][col] * (num_chars - 1)) / 255;
			char ascii_character = ascii_chars[index];

			ascii[row][col] = ascii_character;
		}
	}

	loginfo("ASCII Characters Matrix");
	return ascii;
}

// 4. output the ascii into a file
void AsciiEngine::genAsciiArt(){
	// 1. pixel mat
	int** pixels = genPixelMat();
	// 2. brightness mat
	int** brightness = genBrightnessMat(pixels);
	// 3. ascii mat
	char** ascii = genAsciiMat(brightness);

	// 4. open and create a file
	std::ofstream ascii_file("ascii.txt");
	if(!ascii_file.is_open()){
		std::cerr<<"\033[1;32m[ERROR]\033[0m"<<"Failed to open the ascii file.\n";
		exit(EXIT_FAILURE);
	}
	int row_step = image.getHeight() / 40;
	int col_step = image.getWidth() / 100;

	for(int row = 0; row < image.getHeight(); row+= row_step){
		for(int col = 0; col < image.getWidth(); col+= col_step){
			ascii_file << ascii[row][col];
		}
		ascii_file << '\n';
	}
	ascii_file.close();

	for(int i = 0; i < image.getHeight(); ++i){
		free(pixels[i]);
		free(brightness[i]);
		free(ascii[i]);
	}
	free(pixels);
	free(brightness);
	free(ascii);

}

int AsciiEngine::getHeightMat(){return mHeightMat;}
int AsciiEngine::getWidthMat(){return mWidthMat;}

void AsciiEngine::loginfo(const char* func_name){
	std::cout<<func_name << " created successfully.\n";
}
