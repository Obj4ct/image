//
// Created by ztheng on 2023/9/5.
// done

#include "MyLib/BMPFile.h"
#include "Debug.h"

void AverageBlur(std::vector<uint8_t>& imageData, uint32_t width, uint32_t height) {
    std::vector<uint8_t> blurImage(imageData);

    for (uint32_t y = 1; y < height - 1; y++) {
        for (uint32_t x = 1; x < width - 1; x++) {
            uint32_t index = (y * width + x) * 3;
            uint32_t left = imageData[index - 3];
            uint32_t right = imageData[index + 3];
            uint32_t up = imageData[index - width * 3];
            uint32_t down = imageData[index + width * 3];
            uint32_t mid = imageData[index];
            uint32_t leftUp = imageData[index - width * 3 + 3];
            uint32_t rightUp = imageData[index - width * 3 - 3];
            uint32_t leftDown = imageData[index + width * 3 - 3];
            uint32_t rightDown = imageData[index + width * 3 + 3];
            auto averPix = (left + right + up + down + mid + leftUp + rightUp + leftDown + rightDown) / 9;
            imageData[index] = static_cast<uint8_t>(averPix);
        }
    }
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t  height=myValue.bmpInfo.height;
    int32_t  width=myValue.bmpInfo.width;
    std::vector<uint8_t>imageData=myValue.imageData;
    AverageBlur(imageData, width, height);
    MYFunction::WriteBMPFile("outputAverBlur.bmp", imageData,myValue.bmp,myValue.bmpInfo);

    return 0;
}

