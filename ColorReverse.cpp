//
// Created by ztheng on 2023/9/5.
// done

#include "MyLib/BMPFile.h"


void InvertColors(std::vector<uint8_t>& imageData) {
    for (size_t i = 0; i < imageData.size(); i +=3) {
        imageData[i] = 255 - imageData[i];
        imageData[i + 1] = 255 - imageData[i+1];
        imageData[i + 2] = 255 - imageData[i+2];
    }
}

int main() {

    std::vector<uint8_t> imageData = MYFunction::ReadBMPFile(FILENAME);

    // fuction
    InvertColors(imageData);


    //ImgInfo();
    // create file

    MYFunction::WriteBMPFile("outColorReverse.bmp", imageData);


}
