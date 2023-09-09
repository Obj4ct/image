////
//// Created by ztheng on 2023/9/5.
////
#include "BMPFile.h"


// RotateImage
void RotateImage(std::vector<uint8_t>& newImageData, int width, int height, double angle) {
    // angle to radian
    double radians = angle * M_PI / 180.0;

    int newWidth = static_cast<int>(std::abs(width * std::cos(radians)) +
                                    std::abs(height * std::sin(radians)));
    int newHeight = static_cast<int>(std::abs(height * std::cos(radians)) +
                                     std::abs(width * std::sin(radians)));
    //RGB
    std::vector<uint8_t> rotatedImageData(newWidth * newHeight * 3, 0);

    // center point
    int centerX = newWidth / 2;
    int centerY = newHeight / 2;

    // for_each each pix
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // before
            double rotatedX = std::cos(radians) * (x - centerX) -
                              std::sin(radians) * (y - centerY) + centerX;
            double rotatedY = std::sin(radians) * (x - centerX) +
                              std::cos(radians) * (y - centerY) + centerY;

            //check range is valid
            if (rotatedX >= 0 && rotatedX < width && rotatedY >= 0 && rotatedY < height) {
                // get old rotate image pix and write that   to new
                int originalIndex = static_cast<int>(rotatedY) * width * 3 +
                                    static_cast<int>(rotatedX) * 3;
                int newIndex = y * newWidth * 3 + x * 3;
                rotatedImageData[newIndex] = newImageData[originalIndex];
                rotatedImageData[newIndex + 1] = newImageData[originalIndex + 1];
                rotatedImageData[newIndex + 2] = newImageData[originalIndex + 2];
                std::cout<<"ok"<<std::endl;
            }
        }
    }

    // update
    bmpInfo.width = newWidth;
    bmpInfo.height = newHeight;
    bmpInfo.imageSize = newWidth * newHeight * 3;
    bmp.fileSize = bmp.dataOffset + bmpInfo.imageSize;

    newImageData = rotatedImageData;
}

int main() {

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
    int imageDataOffset = bmp.dataOffset;
    //set imageSize imageSize=width*height*字节
    int imageDataSize = bmpInfo.imageSize;


    //move to image data
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    //read
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close
    inputFile.close();
    // RotateImage Function
    std::vector<uint8_t> newImageData;
    newImageData=imageData;
    double angle;
    std::cout<<"input rotate angle:"<<std::endl;
    std::cin>>angle;
    RotateImage(newImageData, bmpInfo.width, bmpInfo.height, angle);

    // create file
    std::ofstream outputFile("outputRotate.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }

    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
    //write file
    outputFile.seekp(bmp.dataOffset);

    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);

    // close file
    outputFile.close();

    std::cout << "success！" << std::endl;

    return 0;

}

