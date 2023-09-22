//
// Created by ZThenG on 2023/9/21/0021.
//最近邻插值
//选取最近的像素进行插值 最简单一个
//done

#include "MyLib/BMPFile.h"

std::vector<uint8_t>
SmallImage(const std::vector<uint8_t> &imageData, int32_t width, int32_t height, int32_t newWidth, int32_t newHeight) {
    std::vector<uint8_t> resizedImage(newWidth*newHeight*3);

    // 计算缩放因子
    double scaleX = static_cast<double>(width) / newWidth;
    double scaleY = static_cast<double>(height) / newHeight;

    for (int32_t y = 0; y < newHeight; y++) {
        for (int32_t x = 0; x < newWidth; x++) {
            // 原图坐标
            auto srcX = static_cast<int32_t>(x * scaleX);
            auto srcY = static_cast<int32_t>(y * scaleY);
            // 复制到目标
            int32_t srcIndex = (srcY * width + srcX) * 3;
            int32_t destIndex = (y * newWidth + x) * 3;
            resizedImage[destIndex] = imageData[srcIndex];
            resizedImage[destIndex + 1] = imageData[srcIndex + 1];
            resizedImage[destIndex + 2] = imageData[srcIndex + 2];
        }
    }

    return resizedImage;
}

std::vector<uint8_t>
LargeImage(const std::vector<uint8_t> &imageData, int32_t width, int32_t height, int32_t newWidth, int32_t newHeight) {
    std::vector<uint8_t> enlargedImage(newHeight * newWidth * 3);

    // 放大因子
    double scaleX = static_cast<double>(newWidth) / width;
    double scaleY = static_cast<double>(newHeight) / height;

    for (int32_t y = 0; y < newHeight; y++) {
        for (int32_t x = 0; x < newWidth; x++) {
            // 原图坐标
            auto srcX = static_cast<int32_t>(x / scaleX);
            auto srcY = static_cast<int32_t>(y / scaleY);
            int32_t srcIndex = (srcY * width + srcX) * 3;
            int32_t destIndex = (y * newWidth + x) * 3;
            // 复制到目标
            enlargedImage[destIndex] = imageData[srcIndex];
            enlargedImage[destIndex + 1] = imageData[srcIndex + 1];
            enlargedImage[destIndex + 2] = imageData[srcIndex + 2];
        }
    }

    return enlargedImage;
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t width = myValue.bmpInfo.width;
    int32_t height = myValue.bmpInfo.height;
    std::vector<uint8_t> imageData = myValue.imageData;
    std::vector<uint8_t> smallImageData;
    std::vector<uint8_t> largeImageData;
    //缩小
    int32_t newWidth = width / 2;
    int32_t newHeight = height / 2;
    smallImageData = SmallImage(imageData, width, height, newWidth, newHeight);
    MYFunction::SetBMPHeaderValues(myValue.bmp, myValue.bmpInfo, newWidth, newHeight,
                                   myValue.bmpInfo.bitsPerPixel);
    MYFunction::WriteBMPFile("outputNearestSmall.bmp", smallImageData, myValue.bmp, myValue.bmpInfo);
    //放大
    newWidth = width * 2;
    newHeight = height * 2;
    largeImageData = LargeImage(myValue.imageData, width, height, newWidth, newHeight);
    MYFunction::SetBMPHeaderValues(myValue.bmp, myValue.bmpInfo, newWidth, newHeight,
                                   myValue.bmpInfo.bitsPerPixel);
    MYFunction::WriteBMPFile("outputNearestLarge.bmp", largeImageData, myValue.bmp, myValue.bmpInfo);
}
