//
// Created by ztheng on 2023/9/5.
//
#include "BMPFile.h"


void invertColors(std::vector<uint8_t>& imageData) {
    for (size_t i = 0; i < imageData.size(); ++i) {
        //反
        imageData[i] = 255 - imageData[i];
    }
}

int main() {

    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open it!" << std::endl;
        return 1;
    }

    BMP bmp;
    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));

    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }

    // read header
    BMPInfo bmpInfo;
    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));

    // offset
    int imageDataOffset = bmp.dataOffset;

    // size
    int imageDataSize = bmpInfo.imageSize;

    // read data of image
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close
    inputFile.close();

    // fuction
    invertColors(imageData);

    // create file
    std::ofstream outputFile("outColorReverse.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }

    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
    //write file
    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);

    // close file
    outputFile.close();

    std::cout << "success！" << std::endl;

    return 0;
}