//
// Created by ztheng on 2023/9/5.
//

#ifndef CLION_BMPFILE_H
#define CLION_BMPFILE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>

#define FILENAME "../test.bmp"




#pragma pack(push, 1)
struct BMP {
    uint16_t fileType;//用来标识文件类型，通常被设置为固定值 0x4D42，它表示这是一个 BMP 图像文件
    uint32_t fileSize;//表示整个 BMP 文件的大小，以字节为单位
    //下面两个参数都是保留字，没有特定的用途
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;//表示图像数据相对于文件起始位置的偏移量，单位是字节
}bmp,newBmp;
#pragma pack(pop)


#pragma pack(push, 1)
struct BMPInfo {
    uint32_t headerSize;//BMP 文件头的大小，通常为 40 字节
    //BMP 文件头的大小，通常为 40 字节
    int32_t width;
    int32_t height;
    //一个 16 位的整数，通常设置为 1。在现代 BMP 文件中，这个值几乎总是为 1。在早期的 BMP 文件格式中，有些图像可能会使用多个平面来表示颜色信息，但这在现代 BMP 图像中已经不再使用。
    uint16_t planes;
    //这是一个 16 位的整数，表示每个像素使用的位数，决定了图像的颜色深度。例如，24 位的图像表示每个像素由 3 个 8 位通道组成（红、绿、蓝）
    uint16_t bitsPerPixel;
    //这是一个 32 位的整数，表示图像的压缩方式。通常，不压缩的 BMP 图像文件中，这个值为 0。
    uint32_t compression;
    //这是一个 32 位的整数，表示图像数据的大小，以字节为单位。它告诉你图像数据占用了多少存储空间。
    uint32_t imageSize;
    //下面这两个参数分别是 32 位的整数，表示图像的水平和垂直像素密度，以像素每米为单位
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    //下面这两个参数是 32 位的整数，通常不太影响非索引颜色的 BMP 图像。它们在索引颜色的 BMP 图像中用于指定调色板中的颜色数量和重要颜色数量。
    uint32_t colorsUsed;
    uint32_t colorsImportant;
}bmpInfo,newBmpInfo;
#pragma pack(pop)


void ImgInfo(const BMP& inBmp,const BMPInfo& inBmpInfo)
{
    std::cout<<"this is a BMP file"<<std::endl
    <<"BMPHeader info:"<<std::endl
    <<"---------------"<<std::endl
    <<"fileType文件类型: "<<inBmp.fileType<<std::endl
    <<"fileSize文件大小: "<<inBmp.fileSize<<std::endl
    <<"reserved1保留字段1: "<<inBmp.reserved1<<std::endl
    <<"reserved2保留字段2: "<<inBmp.reserved2<<std::endl
    <<"dataOffset数据偏移量: "<<inBmp.dataOffset<<std::endl
    <<"---------------"<<std::endl
    <<"BMPInfo:"<<std::endl
    <<"headerSize信息头大小: "<<inBmpInfo.headerSize<<std::endl
    <<"width图像宽度: "<<inBmpInfo.width<<std::endl
    <<"height图像高度: "<<inBmpInfo.height<<std::endl
    <<"planes颜色平面数: "<<inBmpInfo.planes<<std::endl
    <<"bitsPerPixel每像素位数: "<<inBmpInfo.bitsPerPixel<<std::endl
    <<"compression压缩方式: "<<inBmpInfo.compression<<std::endl
    <<"imageSize图像数据大小: "<<inBmpInfo.imageSize<<std::endl
    <<"xPixelsPerMeter水平像素每米数: "<<inBmpInfo.xPixelsPerMeter<<std::endl
    <<"yPixelsPerMeter垂直像素每米数: "<<inBmpInfo.yPixelsPerMeter<<std::endl
    <<"colorsUsed实际使用的颜色数: "<<inBmpInfo.colorsUsed<<std::endl
    <<"colorsImportant重要颜色数: "<<inBmpInfo.colorsImportant<<std::endl
    <<"-----------------"<<std::endl;

}

//void CreateNewBmp()
//{
//    newBmp=bmp;
//    newBmpInfo=bmpInfo;
//
//}
void  ReadBinTxt(std::string inName,std::string outName)
{
    std::ifstream inputFile(inName, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "无法打开输入文件!" << std::endl;;
    }

    std::ofstream outputFile(outName);

    if (!outputFile.is_open()) {
        std::cerr << "无法创建输出文件!" << std::endl;
        inputFile.close();
    }

    char byte;
    while (inputFile.get(byte)) {
        // 将每个字节的十进制值输出到文本文件
        outputFile << static_cast<int>(byte) << " ";
    }

    inputFile.close();
    outputFile.close();

    std::cout << "转换完成!" << std::endl;
}
int OutputToFile(std::vector<uint8_t>& imageData,std::string name) {

    // open output file
    std::ofstream outputFile(name);


    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件!" << std::endl;
        return 1;
    }

    // foreach imageData
    for (uint8_t byte: imageData) {
        outputFile << static_cast<int>(byte) << " ";
    }

    outputFile.close();

    std::cout << "write done!" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "-----------" << std::endl;

}



#endif //CLION_BMPFILE_H
