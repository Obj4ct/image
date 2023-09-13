//
// Created by ztheng on 2023/9/5.
// done
#include "BMPFile.h"


void FullMosaic(std::vector<uint8_t> &imageData, uint32_t width, uint32_t height, int32_t degree) {
    // foreach pix 加上步长应该是移动像素方便处理下一个像素
    for (uint32_t y = 0; y < height; y += degree) {
        for (uint32_t x = 0; x < width; x += degree) {
            uint32_t totalR = 0;
            uint32_t totalG = 0;
            uint32_t totalB = 0;
            int mosaic = 0;
            // avg
            for (uint32_t dy = 0; dy < degree && y + dy < height; dy++) {
                for (uint32_t dx = 0; dx < degree && x + dx < width; dx++) {
                    uint32_t index = ((y + dy) * width + (x + dx)) * 3;
                    totalR += imageData[index];
                    totalG += imageData[index + 1];
                    totalB += imageData[index + 2];
                    mosaic++;
                }
            }
            auto averageR = totalR / mosaic;
            auto averageG = totalG / mosaic;
            auto averageB = totalB / mosaic;
            // set each pix
            for (uint32_t dy = 0; dy < degree && y + dy < height; dy++) {
                for (uint32_t dx = 0; dx < degree && x + dx < width; dx++) {
                    uint32_t index = ((y + dy) * width + (x + dx)) * 3;
                    imageData[index] = averageR;
                    imageData[index + 1] = averageG;
                    imageData[index + 2] = averageB;
                }
            }
        }
    }
}

void AreaMosaic(std::vector<uint8_t> &imageData, uint32_t width, uint32_t beginX, uint32_t beginY, int32_t degree) {

    // 坐标终点
    uint32_t endX = beginX + degree;
    uint32_t endY = beginY + degree;
    uint32_t totalR = 0;
    uint32_t totalG = 0;
    uint32_t totalB = 0;
    int mosaic = 0;
    // foreach pix 加上步长应该是移动像素方便处理下一个像素
    for (uint32_t y = beginY; y < endY; y ++) {
        for (uint32_t x = beginX; x < endX; x ++) {

            uint32_t index = y * width * 3 + x * 3;
            totalR += imageData[index];
            totalG += imageData[index + 1];
            totalB += imageData[index + 2];
            mosaic++;
        }
    }
    auto averageR = totalR / mosaic;
    auto averageG = totalG / mosaic;
    auto averageB = totalB / mosaic;
    // set each pix
    for (uint32_t y = beginY; y < endY; y ++) {
        for (uint32_t x = beginX; x < endX; x ++) {
            uint32_t index = y * width * 3 + x * 3;;
            imageData[index] = averageR;
            imageData[index + 1] = averageG;
            imageData[index + 2] = averageB;
        }
    }
}


int main() {
    BMP bmp;
    BMPInfo bmpInfo;
    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open this file" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char *>(&bmp), sizeof(BMP));

    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char *>(&bmpInfo), sizeof(BMPInfo));

    //offset
    uint32_t imageDataOffset = bmp.dataOffset;

    //size
    uint32_t imageDataSize = bmpInfo.imageSize;
    //ImgInfo();
    //read data of image
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    inputFile.read(reinterpret_cast<char *>(imageData.data()), imageDataSize);


    // close
    inputFile.close();

    bool isLoop = true;
    while (isLoop) {
        int choice = 1;
        std::cout << "which type of mosaic do you want:" << std::endl
                  << "1.full mosaic" << std::endl
                  << "2.area mosaic" << std::endl
                  << "3.exit" << std::endl
                  << "input:";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                inputBrightness:
                std::cout << "please input mosaic degree:" << std::endl;
                // Brightness function
                int32_t degree;
                std::cin >> degree;
                //OutputToFile(imageData,"beforeBrightness");
                FullMosaic(imageData, bmpInfo.width, bmpInfo.height, degree);
                //OutputToFile(imageData,"afterBrightness");
                std::ofstream outputFile("outputFullMosaic.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));

                outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);

                // write
                outputFile.write(reinterpret_cast<const char *>(imageData.data()), imageDataSize);

                // close file
                outputFile.close();

                std::cout << "success" << std::endl;

                isLoop = true;
                break;
            }
            case 2: {
                uint32_t beginX = 200;
                uint32_t beginY = 200;

//                std::cout<<"你要从哪里开始打码呢？请输入你要开始的X坐标和Y坐标"<<std::endl;
//                std::cout<<"x:"<<std::endl;
//                std::cin>>beginX;
//                std::cout<<"y:"<<std::endl;
//                std::cin>>beginX;
//                std::cout<<"please input width:"<<std::endl;
//                std::cin>>targetWidth;
//                std::cout<<"please input height:"<<std::endl;
//                std::cin>>targetHeight;
//                std::cout<<"please input width:"<<std::endl;
//                std::cin>>targetWidth;
//                std::cout << "please input mosaic degree:" << std::endl;
                // Brightness function
                int32_t degree = 100;
//                std::cin >> degree;
                //OutputToFile(imageData,"beforeBrightness");
                AreaMosaic(imageData, 100,beginX, beginY,degree);
                //OutputToFile(imageData,"afterBrightness");
                std::ofstream outputFile("outputAreaMosaic.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));

                outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);

                // write
                outputFile.write(reinterpret_cast<const char *>(imageData.data()), imageDataSize);

                // close file
                outputFile.close();

                std::cout << "success" << std::endl;

                isLoop = true;
                break;
            }
        }
    }
}
