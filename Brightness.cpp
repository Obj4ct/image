//
// Created by ztheng on 2023/9/5.
// done
#include "BMPFile.h"

int Brightness(std::vector<uint8_t>& newImageData, double_t brightnessValue) {
    if(brightnessValue>=-150&&brightnessValue<=150)
    {
        for (unsigned char & i : newImageData) {
            double_t newValue = static_cast<double_t>(i) + brightnessValue;
            if (newValue < 0)
            {
                newValue = 0;
            } else if (newValue > 255) {
                newValue = 255;
            }
            i = static_cast<uint8_t>(newValue);
        }
        return 0;
    }
    else
    {
        std::cout<<"out of range,brightnessValue is between -150 to 150, please try again!"<<std::endl;
        return 1;
    }

}

int Contrast(std::vector<uint8_t>& newImageData,double_t contrastValue)
{
    if (contrastValue>=-50&&contrastValue<=100)
    {
        double_t factor = (100.0 + contrastValue) / 100.0;
        for (size_t i = 0; i < newImageData.size(); i += 3) {

            newImageData[i] = std::max(0, std::min(255, static_cast<int>(factor * (newImageData[i] - 128) + 128)));
            newImageData[i + 1] = std::max(0, std::min(255, static_cast<int>(factor * (newImageData[i + 1] - 128) + 128)));
            newImageData[i + 2] = std::max(0, std::min(255, static_cast<int>(factor * (newImageData[i + 2] - 128) + 128)));
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
    uint32_t imageDataOffset = bmp.dataOffset;
    //set imageSize
    uint32_t imageDataSize = bmpInfo.imageSize;
    //ImgInfo();
    //move to image data
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    //read
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);
    std::vector<uint8_t> newImageData;
    newImageData=imageData;
    // close
    inputFile.close();
    bool isLoop=true;
    while(isLoop)
    {
        int choice=1;
        std::cout<<"select a fuction:"<<std::endl
                 <<"1.brightness"<<std::endl
                 <<"2.contrast"<<std::endl
                 <<"3.exit"<<std::endl
                 <<"input:";
        std::cin>>choice;

        switch (choice) {
            case 1:
            {
                inputBrightness:
                std::cout<<"How much brightness do you want to increase or decrease?"<<std::endl
                         <<"please input:";
                // Brightness fuction
                double_t brightnessValue;
                std::cin>>brightnessValue;
                //OutputToFile(imageData,"beforeBrightness");
                int result=Brightness(newImageData,brightnessValue);
                //OutputToFile(imageData,"afterBrightness");

                if (result==1)
                {
                    goto inputBrightness;
                }
                else
                {
                    std::ofstream outputFile("outputBrightness.bmp", std::ios::binary);
                    if (!outputFile.is_open()) {
                        std::cout << "unable to create this file" << std::endl;
                        return 1;
                    }
                    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));

                    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                    outputFile.seekp(bmp.dataOffset);

                    // write
                    outputFile.write(reinterpret_cast<const char*>(newImageData.data()),imageDataSize);

                    // close file
                    outputFile.close();

                    std::cout << "success" << std::endl;
                }
                isLoop=true;
                break;
            }
            case 2:
            {
                inputContrastValue:
                std::cout<<"How much contrast do you want to increase or decrease?"<<std::endl
                         <<"please input:";
                double_t  contrastValue;
                std::cin>>contrastValue;
                 //Contrast fuction
                int result=Contrast(newImageData,contrastValue);
                if(result==1)
                {
                    goto inputContrastValue;
                }
                else
                {
                    std::ofstream outputFile("outputContrast.bmp", std::ios::binary);
                    if (!outputFile.is_open())
                    {
                        std::cout << "unable to create this file!" << std::endl;
                        exit(0);
                    }

                    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
                    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                    //write file
                    outputFile.seekp(bmp.dataOffset);

                    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), imageDataSize);

                    // close file
                    outputFile.close();

                    std::cout << "success！" << std::endl;
                }
                isLoop=true;
                break;
            }
            case 3:
                exit(0);
            default:
            {
                std::cout<<"input error! try again!"<<std::endl;
            }

        }
    }

}

