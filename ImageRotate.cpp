////
//// Created by ztheng on 2023/9/5.
////
#include "BMPFile.h"
//done

// RotateImage
void RotateImage(std::vector<uint8_t> &imageData, int32_t width, int32_t height, double_t angle) {
    double_t radians = angle * M_PI / 180.0;
    std::vector<uint8_t> rotatedImageData(width * height * 3);


    int32_t centerX =  width / 2;
    int32_t centerY =  height / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double_t rotatedX = std::cos(radians) * (x - centerX) -
                              std::sin(radians) * (y - centerY) + centerX;
            double_t rotatedY = std::sin(radians) * (x - centerX) +
                              std::cos(radians) * (y - centerY) + centerY;

            if (rotatedX >= 0 && rotatedX < width && rotatedY >= 0 && rotatedY < height)
            {
                int originalIndex = static_cast<int>(std::round(rotatedY)) * width * 3 +
                                    static_cast<int>(std::round(rotatedX)) * 3;
                int newIndex = y * width * 3 + x * 3;
                rotatedImageData[newIndex] = imageData[originalIndex];
                rotatedImageData[newIndex + 1] = imageData[originalIndex + 1];
                rotatedImageData[newIndex + 2] = imageData[originalIndex + 2];

            }
       }
    }


    imageData = rotatedImageData;
}

int main()
{
    BMP bmp;
    BMPInfo bmpInfo;
    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open it!" << std::endl;
        return 1;
    }

    inputFile.read(reinterpret_cast<char *>(&bmp), sizeof(BMP));

    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }


    // read header
    inputFile.read(reinterpret_cast<char *>(&bmpInfo), sizeof(BMPInfo));

    // offset
    uint32_t imageDataOffset = bmp.dataOffset;
    //set imageSize imageSize=width*height*字节
    uint32_t imageDataSize = bmpInfo.imageSize;


    //move to image data
    std::vector<uint8_t> imageData(imageDataSize);

    inputFile.seekg(imageDataOffset);
    //read
    inputFile.read(reinterpret_cast<char *>(imageData.data()), imageDataSize);

    // close
    inputFile.close();
    // RotateImage Function
    double_t angle;
    std::cout<<"input rotate angle:"<<std::endl;
    std::cin>>angle;
    //normal
    RotateImage(imageData, bmpInfo.width, bmpInfo.height, angle);


    // create file
    std::ofstream outputFile("outputRotate.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }

    outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
    //write file
    outputFile.seekp(bmp.dataOffset);

    outputFile.write(reinterpret_cast<const char *>(imageData.data()), imageDataSize);

    // close file
    outputFile.close();

    std::cout << "success！" << std::endl;

    return 0;

}

