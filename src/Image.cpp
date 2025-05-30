#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "../include/Image.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/stb_image_write.h"

Image::Image(const char* path){
	if(!read_image(path)){
		std::cerr<<"\033[1;31m[ERROR]:\033[0m"<<"Failed to read image "<< path<<std::endl;
		exit(EXIT_FAILURE);
	}
	mSize = mWidth * mHeight;
}
Image::~Image(){
	stbi_image_free(mData);
}

bool Image::read_image(const char* path){
	mData = stbi_load(path, &mWidth, &mHeight, &mChannels, 0);
	if(!mData){
		std::cerr<<"\033[1;31m[stb_image ERROR]: \033[0m "<<stbi_failure_reason()<<std::endl;
	}
	else{
		std::cout<<"----------------Loaded Image---------------"<<std::endl;
		std::cout<<"\033[1;32mWidth: \033[0m"<<mWidth<<std::endl;
		std::cout<<"\033[1;32mHeight: \033[0m"<<mHeight<<std::endl;
		std::cout<<"\033[1;32mChannels: \033[0m"<<mChannels<<std::endl;
		std::cout<<"-------------------------------------------"<<std::endl;
	}
	return mData != nullptr;
}

bool Image::write_image(const char* path){
	int size = mSize * mChannels;
	uint8_t* newImg = (uint8_t*)malloc(size);
	if(!newImg)return false;

	memcpy(newImg, mData, size);
	bool success = stbi_write_jpg("newimg.jpg", mWidth,mHeight,3,newImg, mWidth*mChannels);
	free(newImg);
	return success;
}

int Image::getWidth(){return mWidth;}
int Image::getHeight(){return mHeight;}
int Image::getChannels(){return mChannels;}
uint8_t *Image::getData(){return mData;}
