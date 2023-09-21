//
// Created by ztheng on 2023/9/5.
//done
//补色

#include "MyLib/BMPFile.h"

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
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t  height=myValue.bmpInfo.height;
    int32_t  width=myValue.bmpInfo.width;
    std::vector<uint8_t>imageData=myValue.imageData;
    // function
    Complementary(imageData);

    // create file
    MYFunction::WriteBMPFile("outColorComplementary.bmp", imageData,myValue.bmp,myValue.bmpInfo);

}

