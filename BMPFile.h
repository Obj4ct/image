//
// Created by ztheng on 2023/9/5.
//

#ifndef CLION_BMPFILE_H
#define CLION_BMPFILE_H


#include <iostream>
#include <fstream>
#include <vector>
#define FILENAME "/Users/ztheng/Desktop/coding/Dinosaur.bmp"

#pragma pack(1)//确保结构体按照你的声明顺序排列，而不进行额外的内存对齐
struct BMP {
    //用于存储 BMP 文件的文件类型标识。
    uint16_t fileType;
    //于表示整个 BMP 文件的大小
    uint32_t fileSize;
    //保留
    uint16_t reserved1;
    //保留
    uint16_t reserved2;
    //用于表示图像数据在文件中的偏移量。它指示了图像数据从文件的哪个位置开始。
    uint32_t dataOffset;
};




#pragma pack(1)//取消内存对齐
struct BMPInfo {
    //表示信息头的大小
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    //表示图像的颜色平面数
    uint16_t planes;
    //表示每个像素的位数
    uint16_t bitsPerPixel;
    //表示图像的压缩类型
    uint32_t compression;
    //imageSize=width*height*字节
    uint32_t imageSize;
    //像素数
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    //调色板的颜色数量
    uint32_t colorsUsed;
    //调色板的颜色数量
    uint32_t colorsImportant;
};







#endif //CLION_BMPFILE_H
