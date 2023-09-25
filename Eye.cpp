//
// Created by ZThenG on 2023/9/23/0023.
//液化 简而言之就是改变原图像素点的位置

//可以利用插值 ..
#include "MyLib/BMPFile.h"

void Eye(std::vector<uint8_t> &imageData, int32_t width, int32_t height,
         int32_t centerX, int32_t centerY, int32_t radius, double intensity) {
    // 遍历图像像素
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixelIndex = (y * width + x) * 3;

            // 计算像素到中心点的距离
            double distance = std::sqrt(
                    static_cast<double>((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)));

            if (distance < radius) {

                double warpAmount = intensity * std::sin(distance / radius * 3.14159265);

                // 使用线性插值计算目标像素坐标
                double newX = x + warpAmount;
                double newY = y + warpAmount;

                // 使用双线性插值获取目标像素的颜色值
                int x0 = static_cast<int>(newX);
                int y0 = static_cast<int>(newY);
                int x1 = std::min(x0 + 1, width - 1);
                int y1 = std::min(y0 + 1, height - 1);
                double dx = newX - x0;
                double dy = newY - y0;

                int targetPixelIndex00 = (y0 * width + x0) * 3;
                int targetPixelIndex01 = (y0 * width + x1) * 3;
                int targetPixelIndex10 = (y1 * width + x0) * 3;
                int targetPixelIndex11 = (y1 * width + x1) * 3;

                // 使用双线性插值计算目标像素的颜色值
                for (int c = 0; c < 3; c++) {
                    double interpolatedValue =
                            imageData[targetPixelIndex00 + c] * (1 - dx) * (1 - dy) +
                            imageData[targetPixelIndex01 + c] * dx * (1 - dy) +
                            imageData[targetPixelIndex10 + c] * (1 - dx) * dy +
                            imageData[targetPixelIndex11 + c] * dx * dy;

                    imageData[pixelIndex + c] = static_cast<uint8_t>(interpolatedValue);
                }
            }
        }
    }
}


int main() {
    MyValue myValue = MYFunction::ReadBMPFile("../Lenna.bmp");
    int32_t width = myValue.bmpInfo.width;
    int32_t height = myValue.bmpInfo.height;
    std::vector<uint8_t> imageData = myValue.imageData;
    int32_t leftEyeCenterX = 265;
    int32_t leftEyeCenterY = 243;
    int32_t eyeRadius = 20;
    double warpIntensity = 5;

    Eye(imageData, width, height, leftEyeCenterX, leftEyeCenterY, eyeRadius, warpIntensity);

    int32_t rightEyeCenterX = 332;
    int32_t rightEyeCenterY = 243;
    Eye(imageData, width, height, rightEyeCenterX, rightEyeCenterY, eyeRadius, warpIntensity);

    MYFunction::WriteBMPFile("outputResizeEye.bmp", imageData, myValue.bmp, myValue.bmpInfo);

    return 0;
}