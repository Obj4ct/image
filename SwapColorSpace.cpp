//
// Created by ztheng on 2023/9/5.
//done
// 色阶调整分输入色阶调整和输出色阶调整，其中输入色阶调整有3个调整点，即通常所说的黑场、白场及灰场调整
#include "BMPFile.h"
#include <unistd.h>

int RGB2YUV(std::vector<uint8_t>& newImageData,int32_t width,int32_t height)
{
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;
    double_t y=0;
    double_t u=0;
    double_t v=0;
    // for_each pix
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = (i * width + j) * 3;
            uint8_t r = newImageData[index];
            uint8_t g = newImageData[index + 1];
            uint8_t b = newImageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(b);
        }
    }
    y =  0.299 *totalRed + 0.587 *totalGreen + 0.114 *totalBlue;
    u = -0.147 *totalRed - 0.289 *totalGreen + 0.436 *totalBlue;
    v =  0.615 *totalRed - 0.289 *totalGreen + 0.436 *totalBlue;
    // update
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3;
            newImageData[index] = y;
            newImageData[index + 1] = u;
            newImageData[index + 2] = v;
        }
    }

    return 0;

}
int RGB2YIQ(std::vector<uint8_t>& newImageData,int32_t width,int32_t height)
{
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;
    double_t y=0;
    double_t i=0;
    double_t q=0;
    // for_each pix
    for (int j = 0; j < height; ++j)
    {
        for (int k = 0; k < width; ++k)
        {
            int index = (j * width + k) * 3;
            uint8_t r = newImageData[index];
            uint8_t g = newImageData[index + 1];
            uint8_t b = newImageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(b);
        }
    }
    y =  0.299*totalRed + 0.587 * totalGreen + 0.114*totalBlue;
    i =  0.596*totalRed - 0.275 * totalGreen - 0.321*totalBlue;
    q =  0.212 *totalRed - 0.523 * totalGreen + 0.311*totalBlue;
    // update
    for (int l = 0; l < height; ++l) {
        for (int m = 0; m < width; ++m) {
            int index = (l * width + m) * 3;
            newImageData[index] = y;
            newImageData[index + 1] = i;
            newImageData[index + 2] = q;
        }
    }

    return 0;

}
int RGB2YCbCr(std::vector<uint8_t>& newImageData,int32_t width,int32_t height)
{
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;
    double_t y=0;
    double_t i=0;
    double_t q=0;
    // for_each pix
    for (int j = 0; j < height; ++j)
    {
        for (int k = 0; k < width; ++k)
        {
            int index = (j * width + k) * 3;
            uint8_t r = newImageData[index];
            uint8_t g = newImageData[index + 1];
            uint8_t b = newImageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(b);
        }
    }
    y =  0.299*totalRed + 0.587 * totalGreen + 0.114*totalBlue;
    i =  0.596*totalRed - 0.275 * totalGreen - 0.321*totalBlue;
    q =  0.212 *totalRed - 0.523 * totalGreen + 0.311*totalBlue;
    // update
    for (int l = 0; l < height; ++l) {
        for (int m = 0; m < width; ++m) {
            int index = (l * width + m) * 3;
            newImageData[index] = y;
            newImageData[index + 1] = i;
            newImageData[index + 2] = q;
        }
    }

    return 0;

}
int ColorLevelChanel_RGB(std::vector<uint8_t> &newImageData, int32_t width, int32_t height, double_t brightness, double_t contrast)
{
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3;
            uint8_t r = newImageData[index];
            uint8_t g = newImageData[index + 1];
            uint8_t b = newImageData[index + 2];
            //brightness
            r = std::min(255, std::max(0, static_cast<int>(r + brightness)));
            g = std::min(255, std::max(0, static_cast<int>(g + brightness)));
            b = std::min(255, std::max(0, static_cast<int>(b + brightness)));
            //contrast
            r = std::min(255, std::max(0, static_cast<int>((r - 128) * contrast + 128)));
            g = std::min(255, std::max(0, static_cast<int>((g - 128) * contrast + 128)));
            b = std::min(255, std::max(0, static_cast<int>((b - 128) * contrast + 128)));

            // update
            newImageData[index] = r;
            newImageData[index + 1] = g;
            newImageData[index + 2] = b;
        }
    }
    return 0;
}
int main() {
    BMP bmp;
    BMPInfo bmpInfo;
    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open this file" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));

    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));

    //offset
    uint32_t imageDataOffset = bmp.dataOffset;

    //size
    uint32_t imageDataSize = bmpInfo.imageSize;
    //ImgInfo();
    //read data of image
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close
    inputFile.close();
    //CreateNewBmp();
    std::vector<uint8_t> newImageData;
    newImageData=imageData;
    bool isLoop=true;
    while(isLoop)
    {
        int choice=1;
        std::cout<<"select a function:"<<std::endl
                 <<"1.RGB->YUV"<<std::endl
                 <<"2.RGB->YIQ"<<std::endl
                 <<"3.b"<<std::endl
                 <<"4.RGB(All chanel)"<<std::endl
                 <<"5.exit"<<std::endl
                 <<"input:";
        std::cin>>choice;

        switch (choice) {
            case 1:
            {
                std::cout<<"just a moment..."<<std::endl;
                sleep(2);
                RGB2YUV(newImageData,bmpInfo.width,bmpInfo.height);
                std::ofstream outputFile("RGB_TO_YUV.bmp", std::ios::binary);
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
                std::cout<<std::endl;
                isLoop=true;
                break;
            }
            case 2:
            {
                std::cout<<"just a moment..."<<std::endl;
                sleep(2);
                RGB2YIQ(newImageData,bmpInfo.width,bmpInfo.height);
                std::ofstream outputFile("RGB_TO_YIQ.bmp", std::ios::binary);
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
                std::cout<<std::endl;
                isLoop=true;
                break;
            }
//            case 3:
//            {
//                std::cout<<"How much b chanel do you want to increase or decrease?"<<std::endl
//                         << "please input brightness:"<<std::endl;
//                std::cin >> brightness;
//                std::cout<< "please input contrast:"<<std::endl;
//                std::cin>>contrast;
//                ColorLevelChanel_B(newImageData,bmpInfo.width,bmpInfo.height,brightness,contrast);
//                std::ofstream outputFile("changeColorLever_B.bmp", std::ios::binary);
//                if (!outputFile.is_open()) {
//                    std::cout << "unable to create this file" << std::endl;
//                    return 1;
//                }
//                outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
//                outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
//                outputFile.seekp(bmp.dataOffset);
//                // write
//                outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());
//                // close file
//                outputFile.close();
//                std::cout << "success" << std::endl;
//                std::cout<<std::endl;
//                isLoop=true;
//                break;
//            }
//            case 4:
//            {
//
//                inputRGB:
//                std::cout << "How much RGB chanel do you want to increase or decrease?" << std::endl
//                          << "please input brightness:"<<std::endl;
//
//                std::cin >> brightness;
//                std::cout<< "please input contrast:"<<std::endl;
//                std::cin>>contrast;
//                // RGB function
//                int result = ColorLevelChanel_RGB(newImageData, bmpInfo.width, bmpInfo.height,brightness,contrast);
//                if (result == 1)
//                {
//                    goto inputRGB;
//                }
//                else
//                {
//                    std::ofstream outputFile("changeColorLever_RGB.bmp", std::ios::binary);
//                    if (!outputFile.is_open())
//                    {
//                        std::cout << "unable to create this file" << std::endl;
//                        return 1;
//                    }
//                    outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));
//
//                    outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
//                    outputFile.seekp(bmp.dataOffset);
//
//                    // write
//                    outputFile.write(reinterpret_cast<const char *>(newImageData.data()), newImageData.size());
//
//                    // close file
//                    outputFile.close();
//
//                    std::cout << "success" << std::endl;
//                }
//                isLoop = true;
//                break;
//            }
//
//            case 5:
//                exit(0);
            default:
            {
                std::cout<<"input error! try again!"<<std::endl;
            }
        }
    }


}
