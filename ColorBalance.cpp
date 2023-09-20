//
// Created by ztheng on 2023/9/5.
// done

#include "MyLib/BMPFile.h"

//done
void ColorBalance(std::vector<uint8_t> &imageData, int32_t width, int32_t height) {
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;

    // for_each pix
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = (i * width + j) * 3;
            uint8_t r = imageData[index];
            uint8_t g = imageData[index + 1];
            uint8_t b = imageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(b);
        }
    }

    // avg
    double_t avgRed = totalRed / (width * height);
    double_t avgGreen = totalGreen / (width * height);
    double_t avgBlue = totalBlue / (width * height);

    // factor
    double_t redFactor = avgRed > 0.0 ? avgRed / 255.0 : 1.0;
    double_t greenFactor = avgGreen > 0.0 ? avgGreen / 255.0 : 1.0;
    double_t blueFactor = avgBlue > 0.0 ? avgBlue / 255.0 : 1.0;

    // adjust
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = (i * width + j) * 3;
            uint8_t r = imageData[index];
            uint8_t g = imageData[index + 1];
            uint8_t b = imageData[index + 2];

            // adjust new pix by factor
            r = static_cast<uint8_t>(r * redFactor);
            g = static_cast<uint8_t>(g * greenFactor);
            b = static_cast<uint8_t>(b * blueFactor);

            //update pix
            imageData[index] = r;
            imageData[index + 1] = g;
            imageData[index + 2] = b;
        }
    }
}


int main() {
    std::vector<uint8_t> imageData = MYFunction::ReadBMPFile(FILENAME);

    // fuction
    ColorBalance(imageData,bmpInfo.width,bmpInfo.height);


    //ImgInfo();
    // create file
    MYFunction::WriteBMPFile("outColorBalance.bmp", imageData);


    return 0;

}
