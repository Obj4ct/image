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
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3;
            uint8_t r = YUVImageData[index];
            uint8_t g = YUVImageData[index + 1];
            uint8_t b = YUVImageData[index + 2];
            double_t y = (0.257 * r) + (0.504 * g) + (0.098 * b) + 16;
            double_t u = (0.439 * r) - (0.368 * g) - (0.071 * b) + 128;
            double_t v = -(0.148 * r) - (0.291 * g) + (0.439 * b) + 128;
            YUVImageData[index] = static_cast<uint8_t>(y);
            YUVImageData[index + 1] = static_cast<uint8_t>(u);
            YUVImageData[index + 2] = static_cast<uint8_t>(v);
        }
    }
    return 0;
}

int RGB2YIQ(std::vector<uint8_t> &YIQImageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t r = YIQImageData[index];
            uint8_t g = YIQImageData[index + 1];
            uint8_t b = YIQImageData[index + 2];
            double_t y = 0.299 * r + 0.587 * g + 0.114 * b;
            double_t i = 0.596 * r - 0.275 * g - 0.321 * b;
            double_t q = 0.212 * r - 0.523 * g + 0.311 * b;
            YIQImageData[index] = static_cast<uint8_t>(y);
            YIQImageData[index + 1] = static_cast<uint8_t>(i);
            YIQImageData[index + 2] = static_cast<uint8_t>(q);
        }
    }
    return 0;
}

int RGB2LAB(std::vector<uint8_t> &LABImageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t r = LABImageData[index];
            uint8_t g = LABImageData[index + 1];
            uint8_t b = LABImageData[index + 2];
            //RGB to XYZ
            double_t x = r * 0.4124 + g * 0.3576 + b * 0.1805;
            double_t y = r * 0.2126 + g * 0.7152 + b * 0.0722;
            double_t z = r * 0.0193 + g * 0.1192 + b * 0.9505;
            // XYZ to LAB 归一化处理先
            x /= 0.95047;
            y /= 1.0;
            z /= 1.08883;
            double_t FX = x > 0.008856 ? pow(x, 1.0 / 3.0) : (7.787 * x + 0.137931);
            double_t FY = y > 0.008856 ? pow(y, 1.0 / 3.0) : (7.787 * y + 0.137931);
            double_t FZ = z > 0.008856 ? pow(z, 1.0 / 3.0) : (7.787 * z + 0.137931);
            LABImageData[index] = static_cast<uint8_t>(200 * (FY - FZ));
            LABImageData[index + 1] = static_cast<uint8_t>(500 * (FX - FY));
            LABImageData[index + 2] = static_cast<uint8_t>(y > 0.008856 ? (116.0 * FY - 16.0) : (903.3 * y));
        }
    }
    return 0;
}

int YUV2RGB(std::vector<uint8_t> &YUV2RGBImageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t y = YUV2RGBImageData[index];
            uint8_t u = YUV2RGBImageData[index + 1];
            uint8_t v = YUV2RGBImageData[index + 2];
            double_t r = y + 1.13983 * v;
            double_t g = y - 0.39465 * u - 0.58060 * v;
            double_t b = y + 2.03211 * u;
            r = std::min(255.0, std::max(0.0, r));
            g = std::min(255.0, std::max(0.0, g));
            b = std::min(255.0, std::max(0.0, b));
            YUV2RGBImageData[index] = static_cast<uint8_t>(r);
            YUV2RGBImageData[index + 1] = static_cast<uint8_t>(g);
            YUV2RGBImageData[index + 2] = static_cast<uint8_t>(b);
        }
    }
    return 0;
}
int YIQ2RGB(std::vector<uint8_t> &YIQ2RGBImageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t y = YIQ2RGBImageData[index];
            uint8_t i = YIQ2RGBImageData[index + 1];
            uint8_t q = YIQ2RGBImageData[index + 2];
            double_t r = y + 0.956 * i + 0.621 * q;
            double_t g = y - 0.272 * i - 0.647 * q;
            double_t b = y - 1.106 * i + 1.703 * q;
            r = std::min(255.0, std::max(0.0, r));
            g = std::min(255.0, std::max(0.0, g));
            b = std::min(255.0, std::max(0.0, b));
            YIQ2RGBImageData[index] = static_cast<uint8_t>(r);
            YIQ2RGBImageData[index + 1] = static_cast<uint8_t>(g);
            YIQ2RGBImageData[index + 2] = static_cast<uint8_t>(b);
        }
    }
    return 0;
}

int LAB2RGB(std::vector<uint8_t> &LAB2RGBImageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            double_t x = LAB2RGBImageData[index];
            double_t y = LAB2RGBImageData[index + 1];
            double_t z = LAB2RGBImageData[index + 2];
            // LAB to XYZ
            y = (y + 16.0) / 116.0;
            x = (x / 500.0) + y;
            z = y - (z / 200.0);
            double_t r = 3.2406 * x - 1.5372 * y - 0.4986 * z;
            double_t g = -0.9689 * x + 1.8758 * y + 0.0415 * z;
            double_t b = 0.0557 * x - 0.2040 * y + 1.0570 * z;
            r = std::min(255.0, std::max(0.0, r));
            g = std::min(255.0, std::max(0.0, g));
            b = std::min(255.0, std::max(0.0, b));

            LAB2RGBImageData[index] = static_cast<uint8_t>(r);
            LAB2RGBImageData[index + 1] = static_cast<uint8_t>(g);
            LAB2RGBImageData[index + 2] = static_cast<uint8_t>(b);
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
    //outputBinToFile(imageData,"put1");

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
                //sleep(2);
                //outputBinToFile(imageData,"RGBBin");

                RGB2YUV(YUVImageData, bmpInfo.width, bmpInfo.height);
               // outputBinToFile(YUVImageData,"YUVBin");
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
                YUV2RGB(YUV2RGBImageData, bmpInfo.width, bmpInfo.height);
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
                YIQ2RGB(YIQImageData, bmpInfo.width, bmpInfo.height);
                std::ofstream outputFile("YIQ_TO_RGB.bmp", std::ios::binary);
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
                LAB2RGB(LABImageData, bmpInfo.width, bmpInfo.height);
                std::ofstream outputFile("LAB_TO_RGB.bmp", std::ios::binary);
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
