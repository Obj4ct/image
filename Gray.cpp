//
// Created by ztheng on 2023/9/5.
//
#include "BMPFile.h"

// Gray
void ConvertToGray(std::vector<uint8_t>& imageData) {
    OutputToFile(imageData, "GrayBefore");
    for (size_t i = 0; i < imageData.size(); i++) {

        if (imageData[i] >= 127) {
            imageData[i] = 0;
        } else if (imageData[i] < 127) {
            imageData[i] = 255;
        }
    }
    OutputToFile(imageData, "GrayAfter");
}

//
//void ConvertToGray(std::vector<uint8_t>& imageData) {
//    OutPutToFile(imageData, "GrayBefore");
//
//    for (size_t i = 0; i < imageData.size(); i += 3) {
//        uint8_t R = imageData[i];
//        uint8_t G = imageData[i + 1];
//        uint8_t B = imageData[i + 2];
//
//        // 计算灰度值
//        auto grayValue = static_cast<uint8_t>((R + G + B) / 3);
//
//        // 将灰度值赋值给每个通道
//        imageData[i] = grayValue;
//        imageData[i + 1] = grayValue;
//        imageData[i + 2] = grayValue;
//    }
//
//    OutPutToFile(imageData, "GrayAfter");
//}

int main() {

    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open this file" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));

    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));

    //offset
    uint32_t imageDataOffset = bmp.dataOffset;

    //size
    uint32_t imageDataSize = bmpInfo.imageSize;
    ImgInfo();
    //read data of image
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // get width and height
//    int width = bmpInfo.width;
//    int height = bmpInfo.height;

    // close
    inputFile.close();

    // function
    ConvertToGray(imageData);
    bmp.dataOffset+=1;

    //create file
    std::ofstream outputFile("outputGray.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file" << std::endl;
        return 1;
    }

    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));

    // write
    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);

    // close file
    outputFile.close();

    std::cout << "success" << std::endl;

    return 0;
}
