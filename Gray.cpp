//
// Created by ztheng on 2023/9/5.
// done

#include "BMPFile.h"
#include "Debug.h"

void ConvertToGray(std::vector<uint8_t>& imageData) {
    //OutputToFile(imageData, "GrayBefore");

    for (size_t i = 0; i < imageData.size(); i += 3) {
        uint8_t r = imageData[i];
        uint8_t g = imageData[i + 1];
        uint8_t b = imageData[i + 2];
        // cal gray
        auto gray = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
        // gary to every chanel
        imageData[i] = gray;
        imageData[i + 1] = gray;
        imageData[i + 2] = gray;
    }
}

int main() {

    std::vector<uint8_t> imageData = ReadBMPFile(FILENAME);
    if (imageData.empty()) {
        std::cout << "Failed to read BMP file." << std::endl;
        return 1;
    }


    BMP newBmp;
    BMPInfo newBmpInfo;
    newBmp=bmp;
    newBmpInfo=bmpInfo;


    ConvertToGray(imageData);
    //create file
    if (WriteBMPFile("output.bmp", imageData, bmp, bmpInfo)) {
        std::cout << "写入成功" << std::endl;
    } else {
        std::cout << "写入失败" << std::endl;
        return 1;
    }
    return 0;
}
