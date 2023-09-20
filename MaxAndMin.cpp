//
// Created by ZThenG on 2023/9/20/0020.
//
#include "MyLib/BMPFile.h"

#include "Debug.h"

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t  height=myValue.bmpInfo.height;
    int32_t  width=myValue.bmpInfo.width;
    std::vector<uint8_t>imageData=myValue.imageData;

    uint8_t minValue = imageData[0];
    uint8_t maxValue = imageData[0];

    for (uint8_t pixelValue : imageData) {
        minValue = std::min(minValue, pixelValue);
        maxValue = std::max(maxValue, pixelValue);
    }

    std::cout << "Min pixel value: " << static_cast<int>(minValue) << std::endl;
    std::cout << "Max pixel value: " << static_cast<int>(maxValue) << std::endl;

    return 0;
}
