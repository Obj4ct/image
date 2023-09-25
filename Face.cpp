//
// Created by ZThenG on 2023/9/23/0023.
//液化 简而言之就是改变原图像素点的位置
#include "MyLib/BMPFile.h"
void Face(std::vector<uint8_t> &imageData, int32_t width, int32_t height,
              int32_t centerX, int32_t centerY, int32_t radius, double intensity) {
    // 遍历图像像素
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixelIndex = (y * width + x) * 3;

            // 计算像素到中心点的距离
            double distance = std::sqrt(static_cast<double>((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)));

            if (distance < radius) {

                double warpAmount = intensity * std::sin(distance / radius * 3.14159265);


                int newX = static_cast<int>(x + warpAmount);
                int newY = static_cast<int>(y + warpAmount);

                newX = std::max(0, std::min(width - 1, newX));
                newY = std::max(0, std::min(height - 1, newY));

                int targetPixelIndex = (newY * width + newX) * 3;

                imageData[pixelIndex] = imageData[targetPixelIndex];
                imageData[pixelIndex + 1] = imageData[targetPixelIndex + 1];
                imageData[pixelIndex + 2] = imageData[targetPixelIndex + 2];
            }
        }
    }
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile("../Lenna.bmp");
    int32_t width = myValue.bmpInfo.width;
    int32_t height = myValue.bmpInfo.height;
    std::vector<uint8_t> imageData = myValue.imageData;
    int32_t faceCenterX = 300;
    int32_t faceCenterY = 206;
    int32_t faceRadius = 100;
    double warpIntensity = 10;

    Face(imageData, width, height, faceCenterX, faceCenterY, faceRadius, warpIntensity);

    MYFunction::WriteBMPFile("outputResizeFace.bmp", imageData, myValue.bmp, myValue.bmpInfo);

    return 0;
}