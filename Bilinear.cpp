//
// Created by ZThenG on 2023/9/21/0021.
// 双线性插值法 效果要好于最近邻插值，只是计算量稍大一些，算法复杂些
#include "MyLib/BMPFile.h"
std::vector<uint8_t>
SmallImage(const std::vector<uint8_t> &imageData, int32_t width, int32_t height, int32_t newWidth,
           int32_t newHeight) {
    std::vector<uint8_t> resizedImage(newWidth * newHeight * 3);
    // 计算缩小因子
    double scaleX = static_cast<double>(width) / newWidth;
    double scaleY = static_cast<double>(height) / newHeight;
    for (int32_t y = 0; y < newHeight; y++) {
        for (int32_t x = 0; x < newWidth; x++) {
            // 原图坐标
            auto srcX = x * scaleX;
            auto srcY = y * scaleY;
            // 计算最近的像素点坐标?
            auto x1 = static_cast<int32_t>(srcX);
            auto x2 = static_cast<int32_t>(x1 + 1);
            auto y1 = static_cast<int32_t>(srcY);
            auto y2 = static_cast<int32_t>(y1 + 1);
            // 权重? 计算目标像素的权重 w1、w2、w3 和 w4，这些权重表示了目标像素与最近的四个原始像素之间的关系。
            auto tx = srcX - x1;
            auto ty = srcY - y1;
            auto w1 = (1.0 - tx) * (1.0 - ty);
            auto w2 = tx * (1.0 - ty);
            auto w3 = (1.0 - tx) * ty;
            auto w4 = tx * ty;
            // 新像素值?
            int32_t destIndex = (y * newWidth + x) * 3;
            int32_t srcIndex1 = (y1 * width + x1) * 3;
            int32_t srcIndex2 = (y1 * width + x2) * 3;
            int32_t srcIndex3 = (y2 * width + x1) * 3;
            int32_t srcIndex4 = (y2 * width + x2) * 3;
            for (int32_t channel = 0; channel < 3; channel++) {
                resizedImage[destIndex + channel] = static_cast<uint8_t>(
                        w1 * imageData[srcIndex1 + channel] +
                        w2 * imageData[srcIndex2 + channel] +
                        w3 * imageData[srcIndex3 + channel] +
                        w4 * imageData[srcIndex4 + channel]
                );
            }
        }
    }

    return resizedImage;
}

std::vector<uint8_t>
LargeImage(const std::vector<uint8_t> &imageData, int32_t width, int32_t height, int32_t newWidth,
           int32_t newHeight) {
    std::vector<uint8_t> resizedImage(newWidth * newHeight * 3);
    // 计算放大因子
    double scaleX = static_cast<double>(newWidth) / width;
    double scaleY = static_cast<double>(newHeight) / height;
    for (int32_t y = 0; y < newHeight; y++) {
        for (int32_t x = 0; x < newWidth; x++) {
            // 原图坐标
            auto srcX = x / scaleX;
            auto srcY = y / scaleY;
            // 计算最近的像素点坐标
            auto x1 = static_cast<int32_t>(srcX);
            auto x2 = static_cast<int32_t>(x1 + 1);
            auto y1 = static_cast<int32_t>(srcY);
            auto y2 = static_cast<int32_t>(y1 + 1);
            // 权重?
            auto tx = srcX - x1;
            auto ty = srcY - y1;
            auto w1 = (1.0 - tx) * (1.0 - ty);
            auto w2 = tx * (1.0 - ty);
            auto w3 = (1.0 - tx) * ty;
            auto w4 = tx * ty;
            // 新像素值
            int32_t destIndex = (y * newWidth + x) * 3;
            int32_t srcIndex1 = (y1 * width + x1) * 3;
            int32_t srcIndex2 = (y1 * width + x2) * 3;
            int32_t srcIndex3 = (y2 * width + x1) * 3;
            int32_t srcIndex4 = (y2 * width + x2) * 3;
            for (int32_t channel = 0; channel < 3; channel++) {
                resizedImage[destIndex + channel] = static_cast<uint8_t>(
                        w1 * imageData[srcIndex1 + channel] +
                        w2 * imageData[srcIndex2 + channel] +
                        w3 * imageData[srcIndex3 + channel] +
                        w4 * imageData[srcIndex4 + channel]
                );
            }
        }
    }
    return resizedImage;
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
    smallImageData = SmallImage(myValue.imageData, width, height, newWidth, newHeight);
    MYFunction::SetBMPHeaderValues(myValue.bmp, myValue.bmpInfo, newWidth, newHeight, myValue.bmpInfo.bitsPerPixel);
    MYFunction::WriteBMPFile("outputBilinearSmall.bmp", smallImageData, myValue.bmp, myValue.bmpInfo);
    //放大
    newWidth = width * 2;
    newHeight = height * 2;
    largeImageData = LargeImage(myValue.imageData, width, height, newWidth, newHeight);
    MYFunction::SetBMPHeaderValues(myValue.bmp, myValue.bmpInfo, newWidth, newHeight, myValue.bmpInfo.bitsPerPixel);
    MYFunction::WriteBMPFile("outputBilinearLarge.bmp", largeImageData, myValue.bmp, myValue.bmpInfo);
    return 0;
}
