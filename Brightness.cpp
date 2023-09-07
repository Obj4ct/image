//
// Created by ztheng on 2023/9/5.
//
#include "BMPFile.h"


int Brightness(std::vector<uint8_t>& imageData,float brightnessValue) {
    if (brightnessValue>=-150&&brightnessValue<=150)
    {
        for (size_t i = 0; i < imageData.size(); i += 3) {

            imageData[i] = std::max<float>(0, std::min<float>(255, imageData[i] + brightnessValue));
            imageData[i + 1] = std::max<float>(0, std::min<float>(255, imageData[i + 1] + brightnessValue));
            imageData[i + 2] = std::max<float>(0, std::min<float>(255, imageData[i + 2] + brightnessValue));
        }
        return 0;
    }

    else
    {
        std::cout<<"out of range,brightnessValue is between -150 to 150, please try again!"<<std::endl;
        return 1;
    }

}
int Contrast(std::vector<uint8_t>& imageData,float contrastValue)
{
    if (contrastValue>=-50&&contrastValue<=100)
    {
        float factor = (100.0 + contrastValue) / 100.0;
        for (size_t i = 0; i < imageData.size(); i += 3) {

            imageData[i] = std::max(0, std::min(255, static_cast<int>(factor * (imageData[i] - 128) + 128)));
            imageData[i + 1] = std::max(0, std::min(255, static_cast<int>(factor * (imageData[i + 1] - 128) + 128)));
            imageData[i + 2] = std::max(0, std::min(255, static_cast<int>(factor * (imageData[i + 2] - 128) + 128)));
        }
        return 0;
    }
    else
    {
        std::cout<<"out of range,contrastValue is between -50 to 100, please try again!"<<std::endl;
        return 1;
    }
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
    else
    {
        std::cout<<"this is a BMP file "<<std::endl;
    }
    // read header
    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));

    // offset
    int imageDataOffset = bmp.dataOffset;
    //set imageSize
    int imageDataSize = bmpInfo.imageSize;
    ImgInfo();
    //move to image data
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    //read
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close
    inputFile.close();
    bool isLoop=true;
    while(isLoop)
    {
        int choice;
        std::cout<<"select a fuction:"<<std::endl
                 <<"1.brightness"<<std::endl
                 <<"2.contrast"<<std::endl
                 <<"input:";
        std::cin>>choice;

        switch (choice) {
            case 1:
            {
                inputBrightness:
                std::cout<<"How much brightness do you want to increase or decrease?"<<std::endl
                         <<"please input:";
                // Brightness fuction
                float brightnessValue;
                std::cin>>brightnessValue;
                int result=Brightness(imageData,brightnessValue);
                if (result==1)
                {
                    goto inputBrightness;
                }
                else
                {
                    std::ofstream outputFile("outputBrightness.bmp", std::ios::binary);
                    if (!outputFile.is_open())
                    {
                        std::cout << "unable to create this file!" << std::endl;
                        exit(0);
                    }

                    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
                    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                    //write file
                    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);

                    // close file
                    outputFile.close();

                    std::cout << "success！" << std::endl;
                }
                isLoop=false;
                break;
            }
            case 2:
            {
                inputContrastValue:
                std::cout<<"How much contrast do you want to increase or decrease?"<<std::endl
                         <<"please input:";
                float contrastValue;
                std::cin>>contrastValue;
                // Brightness fuction
                int result=Contrast(imageData,contrastValue);
                if(result==1)
                {
                    goto inputContrastValue;
                }
                else
                {
                    std::ofstream outputFile("outputContrastValue.bmp", std::ios::binary);
                    if (!outputFile.is_open())
                    {
                        std::cout << "unable to create this file!" << std::endl;
                        exit(0);
                    }

                    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
                    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                    //write file
                    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);

                    // close file
                    outputFile.close();

                    std::cout << "success！" << std::endl;
                }
                isLoop=false;
                break;
            }
            default:
            {
                std::cout<<"input error! try again!"<<std::endl;
            }

        }
    }

}

