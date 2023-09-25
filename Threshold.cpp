//
// Created by ZThenG on 2023/9/19/0019.
//阈值
#include "MyLib/BMPFile.h"

//void ApplyThreshold(std::vector<uint8_t>& imageData, uint32_t threshold) {
//    for (size_t i = 0; i < imageData.size(); i += 3) {
//        uint8_t r = imageData[i];
//        uint8_t g = imageData[i + 1];
//        uint8_t b = imageData[i + 2];
//        uint32_t gray = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
//        if (gray > threshold) {
//            imageData[i] = std::min(255, static_cast<int>(r) + 100);
//            imageData[i + 1] = std::min(255, static_cast<int>(g) + 100);
//            imageData[i + 2] = std::min(255, static_cast<int>(b) + 100);
//        } else {
//            imageData[i] = std::max(0, static_cast<int>(r) - 100);
//            imageData[i + 1] = std::max(0, static_cast<int>(g) - 100);
//            imageData[i + 2] = std::max(0, static_cast<int>(b) - 100);
//        }
//    }
//}
void ApplyThreshold(std::vector<uint8_t>& imageData, uint32_t threshold) {
    for (size_t i = 0; i < imageData.size(); i += 3) {
        uint8_t r = imageData[i];
        uint8_t g = imageData[i + 1];
        uint8_t b = imageData[i + 2];

        // 计算灰度值并使用double类型保存
        double gray = 0.299 * r + 0.587 * g + 0.114 * b;

        if (gray > threshold) {
            //阈值处理后，你将颜色通道的值分别增加或减少100。这种硬编码的方式可能会导致颜色通道的值超出合理范围（0-255）。你可以考虑使用一个比例因子，而不是固定的100，以确保颜色通道的值在合理范围内。
            // 使用比例因子来调整颜色通道值
            double factor = (gray - threshold) / (255.0 - threshold);
            imageData[i] = std::min(255, static_cast<int>(r + 100 * factor));
            imageData[i + 1] = std::min(255, static_cast<int>(g + 100 * factor));
            imageData[i + 2] = std::min(255, static_cast<int>(b + 100 * factor));
        } else {
            // 使用比例因子来调整颜色通道值
            double factor = gray / threshold;
            imageData[i] = std::max(0, static_cast<int>(r * factor));
            imageData[i + 1] = std::max(0, static_cast<int>(g * factor));
            imageData[i + 2] = std::max(0, static_cast<int>(b * factor));
        }
    }
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t  height=myValue.bmpInfo.height;
    int32_t  width=myValue.bmpInfo.width;
    std::vector<uint8_t>imageData=myValue.imageData;
    uint32_t threshold = 0;
    std::cout<<"input threshold:"<<std::endl;
    std::cin>>threshold;

    ApplyThreshold(imageData, threshold);

    MYFunction::WriteBMPFile("outputThreshold.bmp", imageData,myValue.bmp,myValue.bmpInfo);

    return 0;
}
