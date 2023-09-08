//
// Created by ztheng on 2023/9/5.
//
#include "BMPFile.h"

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
    //set imageSize imageSize=width*height*字节 480000
    uint32_t imageDataSize = bmpInfo.imageSize;

    ImgInfo(bmp, bmpInfo);

    //move to image data
    std::vector<uint8_t> imageData(imageDataSize);


    inputFile.seekg(imageDataOffset);
    //read
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close

    inputFile.close();

    CreateNewBmp();
    int32_t height;
    int32_t width;
    std::cout << "please input height and width" << std::endl
              << "height: " << std::endl;
    std::cin >> height;
    std::cout << "width: " << std::endl;
    std::cin >> width;
    newBmpInfo.height = height;
    newBmpInfo.width = width;
    newBmpInfo.imageSize = newBmpInfo.width * newBmpInfo.height * (newBmpInfo.bitsPerPixel / 8);
    newBmp.fileSize = sizeof(newBmp) + sizeof(newBmpInfo) + newBmpInfo.imageSize;
    //30000
    uint32_t tempImageDataSize = newBmpInfo.imageSize;
    std::vector<uint8_t> newImageData(newBmpInfo.height * newBmpInfo.width * 3);
    //480000-30000=450000
    uint32_t newImageDataSize =imageDataSize-tempImageDataSize;
    //480000-450000
    //imageData.insert(imageData.end(),newImageData.begin(),newImageData.end());
    OutputToFile(newImageData,"newImageData");
    // fuction
    //TailorImg(height,width,imageData);
    ImgInfo(newBmp, newBmpInfo);
    // create file
    std::ofstream outputFile("outColorTailor.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }
    outputFile.write(reinterpret_cast<const char*>(&newBmp), sizeof(newBmp));
    outputFile.write(reinterpret_cast<const char*>(&newBmpInfo), sizeof(newBmpInfo));
    //write file
    //计算要写入文件的实际字节数，以确保只有有效的图像数据被写入文件，而不会包括任何未使用的内存。
    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageDataSize);
    // close file
    outputFile.close();
    std::cout << "success" << std::endl;

    return 0;

}

