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
//对比度
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
//饱和度
void Saturation(std::vector<uint8_t>& newImageData,int32_t width, int32_t height, double_t saturationValue)
{

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int index = (i * width + j) * 3;
                uint8_t r = newImageData[index];
                uint8_t g = newImageData[index + 1];
                uint8_t b = newImageData[index + 2];

                // calc gray
                uint8_t gray = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);

                // calc color
                r = static_cast<uint8_t>((1 - saturationValue) * gray + saturationValue * r);
                g = static_cast<uint8_t>((1 - saturationValue) * gray + saturationValue * g);
                b = static_cast<uint8_t>((1 - saturationValue) * gray + saturationValue * b);

                // update
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
        std::cout<<"select a function:"<<std::endl
                 <<"1.brightness"<<std::endl
                 <<"2.contrast"<<std::endl
                 <<"3.Saturation"<<std::endl
                 <<"4.exit"<<std::endl
                 <<"input:";
        std::cin>>choice;

        switch (choice) {
            case 1:
            {
                inputBrightness:
                std::cout<<"How much brightness do you want to increase or decrease?"<<std::endl
                         <<"please input:";
                // Brightness function
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
                    std::ofstream outputFile("../Image/outputBrightness.bmp", std::ios::binary);
                    if (!outputFile.is_open()) {
                        std::cout << "unable to create this file" << std::endl;
                        return 1;
                    }
                    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));

                    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                    outputFile.seekp(bmp.dataOffset);

                    // write
                    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());

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
                 //Contrast function
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

                    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());

                    // close file
                    outputFile.close();

                    std::cout << "success！" << std::endl;
                }
                isLoop=true;
                break;
            }
            case 3:
            {
                std::cout<<"please input saturation value:"<<std::endl;
                double_t  saturationValue;
                std::cin>>saturationValue;
                //Saturation function
                Saturation(newImageData,bmpInfo.width,bmpInfo.height,saturationValue);
                std::ofstream outputFile("outputSaturation.bmp", std::ios::binary);
                if (!outputFile.is_open())
                {
                    std::cout << "unable to create this file!" << std::endl;
                    exit(0);
                }

                outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                //write file
                outputFile.seekp(bmp.dataOffset);

                outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());

                // close file
                outputFile.close();

                std::cout << "success！" << std::endl;

                isLoop=true;
                break;
            }
            case 4:
                exit(0);
            default:
            {
                std::cout<<"input error! try again!"<<std::endl;
            }
        }
    }

}

