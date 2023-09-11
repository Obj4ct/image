//
// Created by ztheng on 2023/9/5.
// done
#include "BMPFile.h"

//done
void ColorBalance(std::vector<uint8_t> &newImageData, int32_t width, int32_t height) {
    // count
    double totalRed = 0.0;
    double totalGreen = 0.0;
    double totalBlue = 0.0;

    // for_each pix
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = (i * width + j) * 3;
            uint8_t r = newImageData[index];
            uint8_t g = newImageData[index + 1];
            uint8_t b = newImageData[index + 2];
            totalRed += static_cast<double>(r);
            totalGreen += static_cast<double>(g);
            totalBlue += static_cast<double>(b);
        }
    }

    // avg
    double avgRed = totalRed / (width * height);
    double avgGreen = totalGreen / (width * height);
    double avgBlue = totalBlue / (width * height);

    // factor
    double redFactor = avgRed > 0.0 ? avgRed / 255.0 : 1.0;
    double greenFactor = avgGreen > 0.0 ? avgGreen / 255.0 : 1.0;
    double blueFactor = avgBlue > 0.0 ? avgBlue / 255.0 : 1.0;

    // adjust
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = (i * width + j) * 3;
            uint8_t r = newImageData[index];
            uint8_t g = newImageData[index + 1];
            uint8_t b = newImageData[index + 2];

            // adjust new pix by factor
            r = static_cast<uint8_t>(r * redFactor);
            g = static_cast<uint8_t>(g * greenFactor);
            b = static_cast<uint8_t>(b * blueFactor);

            //update pix
            newImageData[index] = r;
            newImageData[index + 1] = g;
            newImageData[index + 2] = b;
        }
    }
}


int main() {
    BMP bmp;
    BMPInfo bmpInfo;
    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open it!" << std::endl;
        return 1;
    }

    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));

    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }

    // read header
    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));

    // offset
    uint32_t imageDataOffset = bmp.dataOffset;
    //set imageSize
    uint32_t imageDataSize = bmpInfo.imageSize;
    //move to image data
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    //read
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close
    inputFile.close();
    //ImgInfo();
    std::vector<uint8_t> newImageData;
    newImageData=imageData;
    // fuction
    ColorBalance(newImageData,bmpInfo.width,bmpInfo.height);


    //ImgInfo();
    // create file
    std::ofstream outputFile("outColorBalance.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }

    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
    //you can ignore it I think …
    outputFile.seekp(bmp.dataOffset);

    //write file
    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());

    // close file
    outputFile.close();

    std::cout << "success！" << std::endl;

    return 0;

}