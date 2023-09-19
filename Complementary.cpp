//
// Created by ztheng on 2023/9/5.
//done

#include "BMPFile.h"
#include "BMPFile.cpp"
void Complementary(std::vector<uint8_t>& imageData) {
//    OutputToFile(newImageData,"C111om");
    for (size_t i = 0; i < imageData.size(); i += 3) {
        size_t r=imageData[i];
        size_t g=imageData[i+1];
        size_t b=imageData[i+2];
        size_t maxRgb=std::max(std::max(r,g),b);
        size_t minRgb=std::min(std::min(r,g),b);
        imageData[i]=maxRgb+minRgb-r;
        imageData[i+1]=maxRgb+minRgb-g;
        imageData[i+2]=maxRgb+minRgb-b;
    }

//    OutputToFile(newImageData,"Com");
}
int main() {

    std::vector<uint8_t> imageData =myFunction.ReadBMPFile(FILENAME);

    // function
    Complementary(imageData);

    // create file
    myFunction.WriteBMPFile("outColorComplementary.bmp", imageData);

}

