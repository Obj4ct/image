//
// Created by Obj4ct on 2023/9/22.
//
#include "MyLib/BMPFile.h"
#include <cmath>

void FishEye(std::vector<uint8_t> &imageData, int32_t width, int32_t height, double strength) {
    std::vector<uint8_t> resultImageData(imageData.size());

    int32_t centerX = width / 2;
    int32_t centerY = height / 2;

    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            int32_t dx = x - centerX;
            int32_t dy = y - centerY;
            double distance = std::sqrt(dx * dx + dy * dy);
            double r = distance / centerX;

            if (r == 0.0) {

                resultImageData[y * width + x] = imageData[y * width + x];
            } else {
                double theta = std::atan(r) * strength;
                double newR = r / std::tan(theta);
                auto newX = static_cast<int32_t>(centerX + newR * dx);
                auto newY = static_cast<int32_t>(centerY + newR * dy);

                if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                    resultImageData[y * width + x] = imageData[newY * width + newX];
                }
            }
        }
    }

    imageData = resultImageData;
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t width = myValue.bmpInfo.width;
    int32_t height = myValue.bmpInfo.height;
    std::vector<uint8_t> imageData = myValue.imageData;

    double strength = 0.8;

    FishEye(imageData, width, height, strength);

    MYFunction::WriteBMPFile("outputFishEye.bmp", imageData, myValue.bmp, myValue.bmpInfo);

    return 0;
}
