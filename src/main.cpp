#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "../include/Image.h"
#include "../include/AsciiEngine.h"

int main(int argc, char** argv){
	if(argv[1] == NULL){
		std::cerr<<"\033[1;31m[ERROR]:\033[0m"<< "Image path cannot be empty.\n";
		return 1;
	}
	const char* image_path = argv[1];

	// 1. read image and prints its width and height in pixels -> e.g. 640x480
	Image image(image_path);
	std::cout<<"Image header info: "<<std::endl;
	std::cout<<image.getWidth()<< " "<<image.getHeight() << " "<<image.getChannels()<<std::endl;

	// 2. init ascii engine
	AsciiEngine engine(image);
	engine.genAsciiArt();

	return 0;
}
