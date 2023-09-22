//
// Created by Obj4ct on 2023/9/22.
//颜色映射 颜色映射 （colormap）是一系列颜色，它们从起始颜色渐变到结束颜色 对灰度图像重新上色
//在一些计算机视觉应用程序中，算法的输出结果是灰度图像。但是，人眼在感知彩色图像的变化时更加敏感，而不擅长观察灰度图像的变化。因此我们常常需要将灰度图像重新着色转换为 等效 的伪彩色图像
//done
#include "MyLib/BMPFile.h"

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

//simple
void ColorMap(std::vector<uint8_t>& imageData, int32_t width, int32_t height) {
    //颜色映射表 3表示channel
    std::vector<uint8_t> colorMap(255 * 3);
    for (int i = 0; i < 256; i++) {
        colorMap[i * 3] = static_cast<uint8_t>(i);
    }
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            int32_t index = (y * width + x) * 3;
            //获取灰度值
            uint8_t gray = imageData[index];

            imageData[index] = colorMap[gray * 3];
            imageData[index+1] = colorMap[gray * 3 + 1];
            imageData[index + 2] = colorMap[gray * 3 + 2];
        }
    }
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t width = myValue.bmpInfo.width;
    int32_t height = myValue.bmpInfo.height;
    std::vector<uint8_t> imageData = myValue.imageData;
    //先转灰度图 我们常常需要将灰度图像重新着色转换为等效的伪彩色图像
    ConvertToGray(imageData);
    ColorMap(imageData, width, height);
    MYFunction::WriteBMPFile("outputColorMap.bmp", imageData, myValue.bmp, myValue.bmpInfo);

    return 0;
}
