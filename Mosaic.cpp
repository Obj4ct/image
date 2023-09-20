//
// Created by ztheng on 2023/9/5.

#include "MyLib/BMPFile.h"
#include "Debug.h"
void FullMosaic(std::vector<uint8_t> &imageData, uint32_t width, uint32_t height, uint32_t degree) {
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

int AreaMosaic(std::vector<uint8_t> &imageData, uint32_t width, uint32_t height, uint32_t beginX, uint32_t beginY,
                uint32_t blockWidth, uint32_t blockHeight, uint32_t degree) {

    uint32_t endX = beginX + blockWidth;
    uint32_t endY = beginY + blockHeight;

    if (endX > width) {
        std::cout << "error! mosaic width > image width" << std::endl;
        return 1;
    }

    else if (endY > height) {
        std::cout << "error! mosaic height > image height" << std::endl;
        return 1;
    }

    for (uint32_t y = beginY; y < endY; y++) {
        for (uint32_t x = beginX; x < endX; x++) {
            uint32_t totalR = 0;
            uint32_t totalG = 0;
            uint32_t totalB = 0;
            int mosaic = 0;

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
    return 0;
}


int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t  height=myValue.bmpInfo.height;
    int32_t  width=myValue.bmpInfo.width;
    std::vector<uint8_t>imageData=myValue.imageData;

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
                std::cout << "please input mosaic degree:" << std::endl;
                // Brightness function
                uint32_t degree;
                std::cin >> degree;
                //OutputToFile(imageData,"beforeBrightness");
                FullMosaic(imageData, width, height, degree);
                //OutputToFile(imageData,"afterBrightness");
                MYFunction::WriteBMPFile("outputFullMosaic.bmp", imageData,myValue.bmp,myValue.bmpInfo);

                isLoop = true;
                break;
            }
            case 2: {
                retry:
                uint32_t beginX = width/4;
                uint32_t beginY = height/4;
                uint32_t blockWidth = 100;
                uint32_t blockHeight = 100;

                std::cout<<"你要从哪里开始打码呢？请输入你要开始的X坐标和Y坐标"<<std::endl;
                std::cout<<"x:"<<std::endl;
                std::cin>>beginX;
                std::cout<<"y:"<<std::endl;
                std::cin>>beginX;
                std::cout<<"please input height:"<<std::endl;
                std::cin>>blockHeight;
                std::cout<<"please input width:"<<std::endl;
                std::cin>>blockWidth;
                std::cout << "please input mosaic degree:" << std::endl;

                uint32_t degree = 0;
                std::cin >> degree;


                int result=AreaMosaic(imageData, width, height, beginX, beginY, blockWidth, blockHeight,degree);
                if(result==1)
                {
                    goto retry;
                }
                else{

                    MYFunction::WriteBMPFile("outputAreaMosaic.bmp", imageData,myValue.bmp,myValue.bmpInfo);
                }



                isLoop = true;
                break;
            }
        }
    }
}
