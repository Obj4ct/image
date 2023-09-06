//
// Created by ztheng on 2023/9/5.
//

#ifndef CLION_BMPFILE_H
#define CLION_BMPFILE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


#define FILENAME "../Dinosaur.bmp"



extern int imageDataSize;
extern int height;
extern int width;

extern std::vector<uint8_t> imageData;

#pragma pack(push, 1)
struct BMP {
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
}bmp;
#pragma pack(pop)


#pragma pack(push, 1)
struct BMPInfo {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
}bmpInfo;
#pragma pack(pop)


void ImgInfo()
{
    std::cout<<"this is a BMP file"<<std::endl
    <<"BMPHeader info:"<<std::endl
    <<"---------------"<<std::endl
    <<"fileType文件类型: "<<bmp.fileType<<std::endl
    <<"fileSize文件大小: "<<bmp.fileSize<<std::endl
    <<"reserved1保留字段1: "<<bmp.reserved1<<std::endl
    <<"reserved2保留字段2: "<<bmp.reserved2<<std::endl
    <<"dataOffset数据偏移量: "<<bmp.dataOffset<<std::endl
    <<"---------------"<<std::endl
    <<"headerSize信息头大小: "<<bmpInfo.headerSize<<std::endl
    <<"width图像宽度: "<<bmpInfo.width<<std::endl
    <<"height图像高度: "<<bmpInfo.height<<std::endl
    <<"planes颜色平面数: "<<bmpInfo.planes<<std::endl
    <<"bitsPerPixel每像素位数: "<<bmpInfo.bitsPerPixel<<std::endl
    <<"compression压缩方式: "<<bmpInfo.compression<<std::endl
    <<"imageSize图像数据大小: "<<bmpInfo.imageSize<<std::endl
    <<"xPixelsPerMeter水平像素每米数: "<<bmpInfo.xPixelsPerMeter<<std::endl
    <<"yPixelsPerMeter垂直像素每米数: "<<bmpInfo.yPixelsPerMeter<<std::endl
    <<"colorsUsed实际使用的颜色数: "<<bmpInfo.colorsUsed<<std::endl
    <<"colorsImportant重要颜色数: "<<bmpInfo.colorsImportant<<std::endl
    <<"-----------------"<<std::endl;

}


#endif //CLION_BMPFILE_H
