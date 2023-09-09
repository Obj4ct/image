//
// Created by ztheng on 2023/9/5.
// done
#include "BMPFile.h"


void InvertColors(std::vector<uint8_t>& newImageData) {
    for (size_t i = 0; i < newImageData.size(); i +=3) {
        newImageData[i] = 255 - newImageData[i];
        newImageData[i + 1] = 255 - newImageData[i+1];
        newImageData[i + 2] = 255 - newImageData[i+2];
    }
}

int main() {
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
    //ImgInfo();
    std::vector<uint8_t> newImageData;
    newImageData=imageData;
    // fuction
    InvertColors(newImageData);


    //ImgInfo();
    // create file
    std::ofstream outputFile("outColorReverse.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }

    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
    outputFile.seekp(bmp.dataOffset);

    //write file
    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), imageDataSize);

    // close file
    outputFile.close();

    std::cout << "success！" << std::endl;

    return 0;

}
