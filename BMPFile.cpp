//
// Created by Obj4ct on 2023/9/19.
//
#include "BMPFile.h"
std::vector<uint8_t> MYFunction::ReadBMPFile(const std::string &fileName) {
    std::ifstream inputFile(fileName, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "Unable to open input file!" << std::endl;
        exit(0);

    }

    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));
    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "File is not a valid BMP!" << std::endl;
        inputFile.close();
        exit(0);
    }

    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));
    uint32_t imageDataOffset = bmp.dataOffset;
    uint32_t imageDataSize = bmpInfo.imageSize;
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);
    inputFile.close();
    return imageData;
}