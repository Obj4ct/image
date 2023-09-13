//
// Created by ZThenG on 2023/9/14/0014.
//

#ifndef IMAGE_DEBUG_H
#define IMAGE_DEBUG_H
#include "BMPFile.h"

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

int  ReadBinTxt(const std::string& inName,const std::string& outName)
{
    std::ifstream inputFile(inName, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "无法打开输入文件!" << std::endl;;
        inputFile.close();
        return 1;
    }
    std::ofstream outputFile(outName);

    if (!outputFile.is_open()) {
        std::cerr << "无法创建输出文件!" << std::endl;
        outputFile.close();
        return 1;
    }

    char byte;
    while (inputFile.get(byte)) {
        outputFile << static_cast<int>(byte) << " ";
    }

    inputFile.close();
    outputFile.close();

    std::cout << "转换完成!" << std::endl;
    return 0;

}
//保存二进制
int outputBinToFile(std::vector<uint8_t>& imageData,const std::string& name)
{
    // open output file
    std::ofstream outputFile(name,std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件!" << std::endl;
        return 1;
    }
    outputFile.write(reinterpret_cast<const char*>(imageData.data()), static_cast<std::streamsize>(imageData.size()));
    outputFile.close();
    std::cout << "-----------" << std::endl;
    std::cout << "二进制生成！!" << std::endl;
    std::cout << "-----------" << std::endl;

    return 0;

}
//保存像素
int OutputPixToFile(std::vector<uint8_t>& imageData,const std::string& name) {

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
    std::cout << "-----------" << std::endl;
    std::cout << "像素信息生成！" << std::endl;
    std::cout << "-----------" << std::endl;
    return 0;

}

//temp image for debug
int TempImage(std::vector<uint8_t>& imageData,const std::string& name,BMP& bmp,BMPInfo& bmpInfo)
{
    // open output file
    std::ofstream outputFile(name);


    if (!outputFile.is_open()) {
        std::cout << "unable to create this file" << std::endl;
        return 1;
    }
    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(bmp));

    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(bmpInfo));
    //  outputFile.seekp(bmp.dataOffset);

    // write
    outputFile.write(reinterpret_cast<const char*>(imageData.data()),static_cast<std::streamsize>(imageData.size()));

    // close file
    outputFile.close();


    std::cout << "-----------" << std::endl;
    std::cout << "中间图像生成！" << std::endl;
    std::cout << "-----------" << std::endl;

    return 0;

}




#endif //IMAGE_DEBUG_H
