//
// Created by ztheng on 2023/9/5.
//done

#include "BMPFile.h"
void Complementary(std::vector<uint8_t>& imageData) {
//    OutputToFile(newImageData,"C111om");
    for (size_t i = 0; i < imageData.size(); i += 3) {
        size_t r=imageData[i];
        size_t g=imageData[i+1];
        size_t b=imageData[i+2];
        size_t maxRgb=std::max(std::max(r,g),b);
        size_t minRgb=std::min(std::min(r,g),b);
        imageData[i]=maxRgb+minRgb-r;
        imageData[i+1]=maxRgb+minRgb-g;
        imageData[i+2]=maxRgb+minRgb-b;
    }

//    OutputToFile(newImageData,"Com");
}
int main() {
    BMP bmp;
    BMPInfo bmpInfo;
    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open it!" << std::endl;
        return 1;
    }
    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));
    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }
    // read header
    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));
    // offset
    uint32_t imageDataOffset = bmp.dataOffset;
    //set imageSize
    uint32_t imageDataSize = bmpInfo.imageSize;
    //move to image data
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    //read
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);
    // close
    inputFile.close();

    // function
    Complementary(imageData);

    // create file
    std::ofstream outputFile("outColorComplementary.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }
    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
    outputFile.seekp(bmp.dataOffset);
    //write file
    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);

    // close file
    outputFile.close();

    std::cout << "success！" << std::endl;

    return 0;
}

