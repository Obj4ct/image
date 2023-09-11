//
// Created by ztheng on 2023/9/5.
// done
#include "BMPFile.h"
void ConvertToGray(std::vector<uint8_t>& newImageData) {
    //OutputToFile(imageData, "GrayBefore");

    for (size_t i = 0; i < newImageData.size(); i += 3) {
        uint8_t r = newImageData[i];
        uint8_t g = newImageData[i + 1];
        uint8_t b = newImageData[i + 2];

        // cal gray
        uint8_t gray = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);

        // gary to every chanel
        newImageData[i] = gray;
        newImageData[i + 1] = gray;
        newImageData[i + 2] = gray;
    }
}

int main() {
    BMP bmp;
    BMPInfo bmpInfo;
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
    //ImgInfo();
    //read data of image
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // get width and height
//    int width = bmpInfo.width;
//    int height = bmpInfo.height;

    // close
    inputFile.close();
    //CreateNewBmp();
    std::vector<uint8_t> newImageData;
    newImageData=imageData;
    // function
    ConvertToGray(newImageData);

    //create file
    std::ofstream outputFile("outputGray.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file" << std::endl;
        return 1;
    }




    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));

    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
    outputFile.seekp(bmp.dataOffset);

    // write
    outputFile.write(reinterpret_cast<const char*>(newImageData.data()),newImageData.size());

    // close file
    outputFile.close();

    std::cout << "success" << std::endl;

    return 0;
}
