//
// Created by ZThenG on 2023/9/23/0023.
//
#include "MyLib/BMPFile.h"
#include "MyLib/BMPFile.cpp"
void ThinFace(std::vector<uint8_t>& imageData, int32_t width, int32_t height, int centerX, int centerY, int radius) {
    // 遍历图像像素，仅处理位于指定半径内的像素
    for (int y = centerY - radius; y < centerY + radius; y++) {
        for (int x = centerX - radius; x < centerX + radius; x++) {
            // 确保像素坐标在图像范围内
            if (x >= 0 && x < width && y >= 0 && y < height) {
                // 计算当前像素到中心点的距离
                double distance = std::sqrt(static_cast<double>((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)));

                // 根据距离来调整像素值，这里使用一个简单的线性插值
                if (distance < radius) {
                    int pixelIndex = (y * width + x) * 3;
                    int diff = static_cast<int>((radius - distance) * 10); // 调整的幅度，可以根据需要调整
                    imageData[pixelIndex] = static_cast<uint8_t>(std::max(imageData[pixelIndex] - diff, 0));
                    imageData[pixelIndex + 1] = static_cast<uint8_t>(std::max(imageData[pixelIndex + 1] - diff, 0));
                    imageData[pixelIndex + 2] = static_cast<uint8_t>(std::max(imageData[pixelIndex + 2] - diff, 0));
                }
            }
        }
    }
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    std::vector<uint8_t> imageData = myValue.imageData;

    // 指定瘦脸中心点和半径
    int centerX = width / 2; // 以图像中心为瘦脸中心
    int centerY = height / 2; // 以图像中心为瘦脸中心
    int radius = 100; // 瘦脸半径，根据需要调整

    // 手动瘦脸
    ThinFace(imageData, width, height, centerX, centerY, radius);

    // 创建文件用于保存瘦脸结果
    MYFunction::WriteBMPFile("outputThinFace.bmp", imageData, myValue.bmp, myValue.bmpInfo);

    return 0;
}
