//
// Created by ztheng on 2023/9/5.
//
#include "BMPFile.h"


void InvertColors(std::vector<uint8_t>& imageData) {
    OutPutToFile(imageData,"before");
    for (unsigned char & i : imageData) {
        //反
        i = 255 - i;
    }
    // 假设已经读取了文件头（bmp）和信息头（bmpInfo）
    bmp.fileSize = sizeof(BMP) + sizeof(BMPInfo) + (bmpInfo.width * bmpInfo.height * (bmpInfo.bitsPerPixel / 8));
    OutPutToFile(imageData,"after");
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
    ImgInfo();
    // fuction
    InvertColors(imageData);

    ImgInfo();
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

