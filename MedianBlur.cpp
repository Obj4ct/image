////
//// Created by ZThenG on 2023/9/21/0021.
////
//done
//中值模糊
#include "MyLib/BMPFile.h"

uint8_t CalculateMedian(std::vector<uint8_t>& window) {
    std::sort(window.begin(), window.end());
    return window[window.size() / 2];
}
void MedianBlur(std::vector<uint8_t>& imageData, uint32_t width, uint32_t height) {
    std::vector<uint8_t> blurImage(imageData);
    for (uint32_t y = 1; y < height - 1; y++) {
        for (uint32_t x = 1; x < width - 1; x++) {
            std::vector<uint8_t> window;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    uint32_t index = ((y + dy) * width + (x + dx)) * 3;
                    window.push_back(imageData[index]);
                }
            }
            uint32_t index = (y * width + x) * 3;
            imageData[index] = CalculateMedian(window);
        }
    }
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    std::vector<uint8_t> imageData = myValue.imageData;
    MedianBlur(imageData, width, height);
    MYFunction::WriteBMPFile("outputMedianBlur.bmp", imageData, myValue.bmp, myValue.bmpInfo);
    return 0;
}
