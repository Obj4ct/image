//
// Created by ZThenG on 2023/9/19/0019.
//
#include "BMPFile.h"
#include "BMPFile.cpp"

//均值代表了图像的亮度平均值
double CalAver(const std::vector<uint8_t> &imageData) {
    double sum = 0.0;
    for (uint8_t pixel: imageData) {
        sum += pixel;
    }
    return sum / imageData.size();
}

//标准差衡量了像素值的分散程度
double CalStandard(const std::vector<uint8_t> &imageData, double aver) {
    uint32_t tempSum = 0, sum = 0, variance;
    for (int i = 0; i < imageData.size(); i++) {
        sum += imageData[i];
    }
    aver = sum / imageData.size();
    for (int i = 0; i < imageData.size(); ++i) {
        tempSum += ((imageData[i] - aver) * (imageData[i] - aver));

    }
    variance = tempSum / imageData.size();


    double_t standard = std::sqrt(variance);
    return standard;
}

void AutoContrast(std::vector<uint8_t> &imageData) {
    double aver = CalAver(imageData);
    double standard = CalStandard(imageData, aver);
    //缩放因子 中间亮度值
    double factor = 128.0 / standard;

    for (size_t i = 0; i < imageData.size(); i += 3) {

        imageData[i] = std::max(0, std::min(255,
                                            static_cast<int>(factor * (imageData[i] - aver) + 128)));
        imageData[i + 1] = std::max(0, std::min(255,
                                                static_cast<int>(factor * (imageData[i + 1] - aver) +
                                                                 128)));
        imageData[i + 2] = std::max(0, std::min(255,
                                                static_cast<int>(factor * (imageData[i + 2] - aver) +
                                                                 128)));
    }
}

int main() {
    std::vector<uint8_t> imageData =MYFunction::ReadBMPFile(FILENAME);

    AutoContrast(imageData);
    MYFunction::WriteBMPFile("outputAutoContrast.bmp", imageData);
    return 0;
}
