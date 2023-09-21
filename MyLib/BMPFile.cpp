//
// Created by Obj4ct on 2023/9/19.
//done
#include "BMPFile.h"

MyValue MYFunction::ReadBMPFile(const std::string &fileName) {
    BMP bmp;
    BMPInfo bmpInfo;
    MyValue myValue;

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
    myValue.imageData=imageData;
    myValue.bmp=bmp;
    myValue.bmpInfo=bmpInfo;
    inputFile.close();
    return myValue;
}


void MYFunction::WriteBMPFile(const std::string& fileName, const std::vector<uint8_t>& imageData,BMP& bmp,BMPInfo& bmpInfo) {

    std::ofstream outputFile("../outImage/"+fileName, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "Unable to create output file!" << std::endl;

    }
    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
    outputFile.seekp(bmp.dataOffset);
    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());
    outputFile.close();
    std::cout<<"success write ,file called "<<fileName<<std::endl;

}

void MYFunction::SetBMPHeaderValues(BMP& bmp, BMPInfo& bmpInfo, int width, int height, uint16_t bitsPerPixel) {
    // 设置 BMP 文件头信息
    bmp.fileType = 0x4D42; // BMP 文件类型标识 "BM"
    bmp.fileSize = sizeof(BMP) + sizeof(BMPInfo) + (width * height * (bitsPerPixel / 8)); // 文件总大小
    bmp.reserved1 = 0; // 保留字段1，通常设置为0
    bmp.reserved2 = 0; // 保留字段2，通常设置为0
    bmp.dataOffset = sizeof(BMP) + sizeof(BMPInfo); // 图像数据在文件中的偏移量

    // 设置 BMP 信息头信息
    bmpInfo.headerSize = sizeof(BMPInfo); // BMP 文件头大小
    bmpInfo.width = width; // 图像宽度
    bmpInfo.height = height; // 图像高度
    bmpInfo.planes = 1; // 位图平面数，通常为1
    bmpInfo.bitsPerPixel = bitsPerPixel; // 每像素位数
    bmpInfo.compression = 0; // 压缩方式，通常不压缩
    bmpInfo.imageSize = bmp.fileSize - bmp.dataOffset; // 图像数据大小
    bmpInfo.xPixelsPerMeter = 0; // 水平像素密度
    bmpInfo.yPixelsPerMeter = 0; // 垂直像素密度
    bmpInfo.colorsUsed = 0; // 使用的颜色数，通常不使用调色板
    bmpInfo.colorsImportant = 0; // 重要颜色数，通常不指定
}