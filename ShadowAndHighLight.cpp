//
// Created by Obj4ct on 2023/9/19.
//
#include "Debug.h"
//just a simple shadow
#include "BMPFile.h"
#include "BMPFile.cpp"
void MakeShadow(std::vector<uint8_t>& imageData,std::vector<uint8_t> &shadowImageData,uint32_t shadowValue)
{
    for (size_t i=0; i < imageData.size(); i += 3) {
        uint8_t r = imageData[i];
        uint8_t g = imageData[i + 1];
        uint8_t b = imageData[i + 2];
        shadowImageData[i] = r-shadowValue;
        shadowImageData[i + 1] = g-shadowValue;
        shadowImageData[i + 2] = b-shadowValue;
    }

}
//亮的地方变暗
void HighLight(std::vector<uint8_t> &imageData,std::vector<uint8_t> &highLightImageData,uint32_t pixel)
{
    for (size_t i = 0; i < imageData.size(); ++i)
    {
        if(imageData[i]>pixel)
        {
            highLightImageData[i]-=100;
        }
    }

}
int main() {

    std::vector<uint8_t> imageData = myFunction.ReadBMPFile(FILENAME);
    std::vector<uint8_t>  shadowImageData(imageData.size());
    shadowImageData=imageData;
    std::vector<uint8_t> highLightImageData(imageData.size());
    highLightImageData=imageData;
    bool isLoop = true;
    while (isLoop) {
        int choice = 1;
        std::cout << "input:" << std::endl
                  << "1。阴影" << std::endl
                  << "2.高光" << std::endl
                  << "3.exit" << std::endl
                  << "input:";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                uint32_t shadow=0;
                std::cout<<"input shadow:"<<std::endl;
                std::cin>>shadow;
                MakeShadow(imageData,shadowImageData,shadow);
                myFunction.WriteBMPFile("outputShadow.bmp",shadowImageData);
                isLoop = true;
                break;
            }
            case 2: {
                uint32_t pixel=0;
                std::cout<<"输入像素值，在此像素值之上的像素将被降低值："<<std::endl;
                std::cin>>pixel;
                HighLight(imageData,highLightImageData,pixel);
                myFunction.WriteBMPFile("outputHighLight.bmp",highLightImageData);
                isLoop = true;
                break;
            }

            case 3:
                exit(0);

            default: {
                std::cout << "input error! try again!" << std::endl;
            }
        }
    }
}

