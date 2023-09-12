//
// Created by ztheng on 2023/9/5.
//done
// 色阶调整分输入色阶调整和输出色阶调整，其中输入色阶调整有3个调整点，即通常所说的黑场、白场及灰场调整
#include "BMPFile.h"
//windows
//#include <windows.h>
//unix
#include <unistd.h>


int RGB2YUV(std::vector<uint8_t> &YUVImageData, int32_t width, int32_t height) {
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;
    double_t y = 0;
    double_t u = 0;
    double_t v = 0;
    // for_each pix
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3;
            uint8_t r = YUVImageData[index];
            uint8_t g = YUVImageData[index + 1];
            uint8_t b = YUVImageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(b);
            y = 0.299 * totalRed + 0.587 * totalGreen + 0.114 * totalBlue;
            u = -0.169 * totalRed - 0.331 * totalGreen + 0.5 * totalBlue;
            v = 0.5 * totalRed - 0.419 * totalGreen - 0.081 * totalBlue;
            YUVImageData[index] = y;
            YUVImageData[index + 1] = u;
            YUVImageData[index + 2] = v;
        }
    }
    std::cout << std::endl
              << std::endl
              << std::endl
              << std::endl
              << "change RGB to YUV....." << std::endl;


    return 0;

}

int RGB2YIQ(std::vector<uint8_t> &YIQImageData, int32_t width, int32_t height) {
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;
    double_t y = 0;
    double_t i = 0;
    double_t q = 0;
    // for_each pix
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t r = YIQImageData[index];
            uint8_t g = YIQImageData[index + 1];
            uint8_t b = YIQImageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(b);
            y = 0.299 * totalRed + 0.587 * totalGreen + 0.114 * totalBlue;
            i = 0.596 * totalRed - 0.275 * totalGreen - 0.321 * totalBlue;
            q = 0.212 * totalRed - 0.523 * totalGreen + 0.311 * totalBlue;
            YIQImageData[index] = y;
            YIQImageData[index + 1] = i;
            YIQImageData[index + 2] = q;
        }
    }


    return 0;

}

int RGB2LAB(std::vector<uint8_t> &LABImageData, int32_t width, int32_t height) {
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;
    double_t l = 0;
    double_t a = 0;
    double_t b = 0;
    // for_each pix
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t r = LABImageData[index];
            uint8_t g = LABImageData[index + 1];
            uint8_t bChannel = LABImageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(bChannel);
            l = 0.256789 * totalRed + 0.504129 * totalGreen + 0.097906 * totalBlue + 16;
            a = -0.148223 * totalRed - 0.290992 * totalGreen + 0.439215 * totalBlue + 128;
            b = 0.439215 * totalRed - 0.367789 * totalGreen - 0.071426 * totalBlue + 128;
            LABImageData[index] = l;
            LABImageData[index + 1] = a;
            LABImageData[index + 2] = b;
        }
    }
    return 0;

}

int RGB2XYZ(std::vector<uint8_t> &LABImageData, int32_t width, int32_t height) {
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;
    double_t x = 0;
    double_t y = 0;
    double_t z = 0;
    // for_each pix
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t r = LABImageData[index];
            uint8_t g = LABImageData[index + 1];
            uint8_t b = LABImageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(b);
            //to xyz first
            x = totalRed * 0.4124 + totalGreen * 0.3576 + totalBlue * 0.1805;
            y = totalRed * 0.2126 + totalGreen * 0.7152 + totalBlue * 0.0722;
            z = totalRed * 0.0193 + totalGreen * 0.1192 + totalBlue * 0.9505;
            LABImageData[index] = x;
            LABImageData[index + 1] = y;
            LABImageData[index + 2] = z;

            //xyz to LAB
            x /= 0.95047;
            y /= 1.0;
            z /= 1.08883;
            float FX = x > 0.008856f ? pow(x, 1.0f / 3.0f) : (7.787f * x + 0.137931f);
            float FY = y > 0.008856f ? pow(y, 1.0f / 3.0f) : (7.787f * y + 0.137931f);
            float FZ = z > 0.008856f ? pow(z, 1.0f / 3.0f) : (7.787f * z + 0.137931f);
            LABImageData[index] = 200.f * (FY - FZ);
            LABImageData[index + 1] = 500.f * (FX - FY);
            LABImageData[index + 2] = y > 0.008856f ? (116.0f * FY - 16.0f) : (903.3f * y);

        }
    }

    return 0;

}
int YUV2RGB(std::vector<uint8_t> &YUV2RGBImageData, int32_t width, int32_t height) {
    // count
    double_t totalRed = 0.0;
    double_t totalGreen = 0.0;
    double_t totalBlue = 0.0;
    double_t l = 0;
    double_t a = 0;
    double_t b = 0;
    // for_each pix
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t r = YUV2RGBImageData[index];
            uint8_t g = YUV2RGBImageData[index + 1];
            uint8_t bChannel = YUV2RGBImageData[index + 2];
            totalRed += static_cast<double_t>(r);
            totalGreen += static_cast<double_t>(g);
            totalBlue += static_cast<double_t>(bChannel);
            l = 0.256789 * totalRed + 0.504129 * totalGreen + 0.097906 * totalBlue + 16;
            a = -0.148223 * totalRed - 0.290992 * totalGreen + 0.439215 * totalBlue + 128;
            b = 0.439215 * totalRed - 0.367789 * totalGreen - 0.071426 * totalBlue + 128;
            YUV2RGBImageData[index] = l;
            YUV2RGBImageData[index + 1] = a;
            YUV2RGBImageData[index + 2] = b;
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
    std::vector<uint8_t> YUVImageData(imageDataSize);
    YUVImageData = imageData;
    std::vector<uint8_t> YIQImageData(imageDataSize);
    YIQImageData = imageData;
    std::vector<uint8_t> LABImageData(imageDataSize);
    LABImageData = imageData;
    std::vector<uint8_t> YUV2RGBImageData(imageDataSize);
    YUV2RGBImageData=imageData;
    std::vector<uint8_t> YIQ2RGBImageData(imageDataSize);
    YIQ2RGBImageData=imageData;
    std::vector<uint8_t> LAB2RGBImageData(imageDataSize);
    LAB2RGBImageData=imageData;


    bool isLoop = true;
    while (isLoop) {
        int choice = 1;
        std::cout << "select a function:" << std::endl
                  << "1.RGB->YUV" << std::endl
                  << "2.RGB->YIQ" << std::endl
                  << "3.RGB->LAB" << std::endl
                  << "-------------" << std::endl
                  << "-------------" << std::endl
                  << "4.YUV->RGB" << std::endl
                  << "5.YIQ->RGB" << std::endl
                  << "6.LAB->RGB" << std::endl
                  << "-------------" << std::endl
                  << "-------------" << std::endl
                  << "7.exit" << std::endl
                  << "input:";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "just a moment..." << std::endl;
                //unix
                sleep(2);
                RGB2YUV(YUVImageData, bmpInfo.width, bmpInfo.height);
                std::ofstream outputFile("RGB_TO_YUV.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char *>(YUVImageData.data()), YUVImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout << std::endl;
                isLoop = true;
                break;
            }
            case 2: {
                std::cout << "just a moment..." << std::endl;
                //unix
                sleep(2);
                RGB2YIQ(YIQImageData, bmpInfo.width, bmpInfo.height);
                std::ofstream outputFile("RGB_TO_YIQ.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char *>(YIQImageData.data()), YIQImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout << std::endl;
                isLoop = true;
                break;
            }
            case 3: {
                std::cout << "just a moment..." << std::endl;
                //unix
                sleep(2);
                RGB2LAB(LABImageData, bmpInfo.width, bmpInfo.height);
                std::ofstream outputFile("RGB_TO_LAB.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char *>(LABImageData.data()), LABImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout << std::endl;
                isLoop = true;
                break;
            }
            case 4: {
                std::cout << "just a moment..." << std::endl;
                //unix
                sleep(2);
                RGB2LAB(YUV2RGBImageData, bmpInfo.width, bmpInfo.height);
                std::ofstream outputFile("YUV_TO_RGB.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char *>(YUV2RGBImageData.data()), YUV2RGBImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout << std::endl;
                isLoop = true;
                break;
            }
            case 5: {
                std::cout << "just a moment..." << std::endl;
                //unix
                sleep(2);
                RGB2LAB(LABImageData, bmpInfo.width, bmpInfo.height);
                std::ofstream outputFile("RGB_TO_LAB.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char *>(LABImageData.data()), LABImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout << std::endl;
                isLoop = true;
                break;
            }
            case 6: {
                std::cout << "just a moment..." << std::endl;
                //unix
                sleep(2);
                RGB2LAB(LABImageData, bmpInfo.width, bmpInfo.height);
                std::ofstream outputFile("RGB_TO_LAB.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char *>(LABImageData.data()), LABImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout << std::endl;
                isLoop = true;
                break;
            }
            case 7:
                exit(0);
            default: {
                std::cout << "input error! try again!" << std::endl;
            }
        }
    }


}
