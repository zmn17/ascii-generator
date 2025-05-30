#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/stb_image_write.h"
#include "../include/Image.h"

int main(int argc, char** argv){
	if(argv[1] == NULL){
		std::cerr<<"\033[1;31m[ERROR]:\033[0m"<< "Image path cannot be empty.\n";
		return 1;
	}
	const char* image_path = argv[1];

	// 1. read image and prints its width and height in pixels -> e.g. 640x480
	Image image(image_path);
	std::cout<<"\033[1;32mWidth: \033[0m"<<image.getWidth()<<std::endl;
	std::cout<<"\033[1;32mHeight: \033[0m"<<image.getHeight()<<std::endl;
	std::cout<<"\033[1;32mChannels: \033[0m"<<image.getChannels()<<std::endl;
	int width = image.getWidth();
	int height = image.getHeight();
	int channels = image.getChannels();
	uint8_t* data = image.getData();

	/* 2. load image's pixel data into a 2D array
	*	- JPEG image is represented by a 3D array -> each element contains 3 numbers - 0-255 RGB
	*/
	// 2a - create a pixel matrix
	 int numPixels = width*height;
	// allocate memory for the pixel matrix - CPP 
	// int** pixels = new int*[numPixels];
	// for(int i = 0; i < numPixels; ++i){
	// 	pixels[i] = new int[channels];
	// }
	
	int** pixels = (int**)malloc(numPixels * sizeof(int*));
	for(int i = 0; i < numPixels; ++i){
		// allocate 3 ints for RGB using malloc
		pixels[i] = (int*)malloc(channels* sizeof(int));
	}
	if(pixels == nullptr){
		std::cerr<<"Pixels matrix creation failed.\n";
		return 1;
	}

	// rgb - extracted from image data
	unsigned char r,g,b;

	// creating a new image
	int size = width*height*channels;
	uint8_t *blueImg;
	blueImg = (uint8_t*)malloc(size);

	//	- read all of those elements and store them into a 2D array
	for(int rows = 0; rows < height; rows++){
		for(int cols = 0; cols < width; cols++){
			int idx = (rows * width + cols) * channels;
			r = img[idx + 0];
			g = img[idx + 1];
			b = img[idx + 2];
			// std::cout<<r << " " << g << " "<< b << std::endl;

			// for experiment - image filtering
			blueImg[idx + 0] = r;
			blueImg[idx + 1] = g;

			int blue = (int)b;
			if(blue + 50 >= 255){
				blue = 255;
			}else {
				blue = 50;
			}
			blueImg[idx + 2] = blue;

			int pixelIndex = rows * width + cols;
			pixels[pixelIndex][0] = (int)r;
			pixels[pixelIndex][1] = (int)g;
			pixels[pixelIndex][2] = (int)b;
		}
	}
	std::cout<<"Pixels matrix successfully created.\n";
	std::cout<<"Pixels matrix size: "<< height << "x"<< width<<std::endl;

	//	- so to iterate and access data at a given x, y coordinate
	// accessing the pixes matrix for(int row = 0; row < height; ++row){ for(int col = 0; col < width; ++col){
	// 		int pixelIndex = row * width + col;
	//
	// 		std::cout<<pixels[pixelIndex][0]<<" "<< pixels[pixelIndex][1] << " " << pixels[pixelIndex][2]<<std::endl;
	// 	}
	// 	std::cout<<std::endl;
	// }
	
	// Testing
	// int red = pixels[0][0];
	// int green = pixels[0][1];
	// int bluee = pixels[0][2];
	//
	// int color_code;
	// if(red > 200 && green < 100 && bluee < 100) color_code = 31;
	// else if(red < 100 && green > 200 && bluee < 100) color_code = 32;
	// else if(red < 100 && green < 100 && bluee > 200) color_code = 34;
	// else color_code = 37;
	//
	// std::cout << "\033[1;" << color_code << "m"
	//              << "RGB(" << red << "," << green << "," << bluee << ")"
	//              << "\033[0m" << std::endl;


	/*
		* 3. convert the RGB elemen of the pixels into a single brightness numbers
		*	- map RGB values to brightness
		*	- average: average the R, G, and B values - (R + G + B) / 3
		*	- lightness: average the max and min values out of R, G, and B - max(R, G, B) + min(R, G, B) /2
		*	- luminosity: take a weighted average of the R, G, B values to account for human perception -
		*		- 0.21 R + 0.72 G + 0.07 B
		*	- choose one - average
		*	- iterate through pixel brightness
		*
		* 4. convert brightness numbers to ASCII characters
		*	- map brightness to characters
		*	- "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$" - ordered
		*
	*/

	// create brightness matrix
	int** brightness = (int**)malloc(height * sizeof(int *));
	for(int i = 0; i < height; ++i){
		brightness[i] = (int*)malloc(width * sizeof(int));
	}
	if(brightness == nullptr){
		std::cerr<<"Brightness matrix creation failed.\n";
		return 1;
	}
	// get the average of rgb values
	int average;
	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			int pixelIndex = row * width + col;

			// R, G , B
			int rvalue = pixels[pixelIndex][0];
			int gvalue = pixels[pixelIndex][1];
			int bvalue = pixels[pixelIndex][2];

			// take the average of R,G,B -> brightness value
			average = (rvalue + gvalue + bvalue) / 3;
			brightness[row][col] = average;

		}
		std::cout<<std::endl;
	}
	std::cout<<"Brightness matrix successfully created.\n";
	std::cout<<"Brightness matrix size: "<< height << "x"<< width<<std::endl;
	// for(int row = 0; row < height; ++row){
	// 	for(int col = 0; col < width; ++col){
	// 		std::cout<<"brightness["<<row<<"]["<<col<<"]: "<< brightness[row][col]<<std::endl;
	// 	}
	// }

	// ASCII characters
	std::string ascii_chars = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
	// create ASCII characters matrix
	char** ascii = (char**)malloc(height * sizeof(char*));
	for(int i = 0; i < height; ++i){
		ascii[i] = (char*)malloc(width * sizeof(char));
	}

	if(ascii == nullptr){
		std::cerr<<"ASCII matrix creation failed.\n";
		return 1;
	}

	std::cout<<"ASCII matrix successfully created.\n";
	std::cout<<"ASCII matrix size: "<< height << "x"<< width<<std::endl;

	int num_chars = strlen(ascii_chars.c_str());

	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			// normalize brightness from 0-255 into an index from 0-[num of chars - 1]
			int index = (brightness[row][col] * (num_chars - 1)) / 255;
			char ascii_character = ascii_chars[index];

			ascii[row][col] = ascii_character;
		}
	}

	// for(int row = 0; row < height; row+=2){
	// 	for(int col = 0; col < width; col+=2){
	// 		std::cout<<ascii[row][col];
	// 	}
	// 	std::cout<<std::endl;
	// }

	std::ofstream ascii_file("ascii_art.txt");
	if(!ascii_file.is_open()){
		std::cerr<<"ERROR: failed to open the ascii_art.txt file.\n";
		return 1;
	}

	int row_step = height / 40;
	int col_step = width / 100;
	for(int row = 0; row < height; row+= row_step){
		for(int col = 0; col < width; col+= col_step){
			ascii_file << ascii[row][col];
		}
		ascii_file << '\n';
	}

	// close the file
	ascii_file.close();

	// free memory
	for(int i = 0; i < numPixels; ++i){
		free(pixels[i]);
	}
	for(int i = 0; i < height; ++i){
		free(brightness[i]);
		free(ascii[i]);
	}

	free(pixels);
	free(brightness);
	free(ascii);

	return 0;
}
