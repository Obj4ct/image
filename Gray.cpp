//
// Created by ztheng on 2023/9/5.
// done

#include "MyLib/BMPFile.h"

#include "Debug.h"
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

int main() {
    std::vector<uint8_t> imageData =MYFunction::ReadBMPFile(FILENAME);

    ConvertToGray(imageData);
    //create file
    MYFunction::WriteBMPFile("outColorGray.bmp", imageData);

}
