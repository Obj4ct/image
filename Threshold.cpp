//
// Created by ZThenG on 2023/9/19/0019.
//
#include "BMPFile.h"
#include "BMPFile.cpp"
void ApplyThreshold(std::vector<uint8_t>& imageData, uint32_t threshold) {
    for (size_t i = 0; i < imageData.size(); i += 3) {
        uint8_t r = imageData[i];
        uint8_t g = imageData[i + 1];
        uint8_t b = imageData[i + 2];
        uint32_t gray = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
        if (gray > threshold) {
            imageData[i] = std::min(255, static_cast<int>(r) + 100);
            imageData[i + 1] = std::min(255, static_cast<int>(g) + 100);
            imageData[i + 2] = std::min(255, static_cast<int>(b) + 100);
        } else {
            imageData[i] = std::max(0, static_cast<int>(r) - 100);
            imageData[i + 1] = std::max(0, static_cast<int>(g) - 100);
            imageData[i + 2] = std::max(0, static_cast<int>(b) - 100);
        }
    }
}

int main() {
    std::vector<uint8_t> imageData = MYFunction::ReadBMPFile(FILENAME);

    uint32_t threshold = 0;
    std::cout<<"input threshold:"<<std::endl;
    std::cin>>threshold;

    ApplyThreshold(imageData, threshold);

    MYFunction::WriteBMPFile("outputThreshold.bmp", imageData);

    return 0;
}
