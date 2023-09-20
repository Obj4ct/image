//
// Created by ztheng on 2023/9/5.
//done


// 色阶调整分输入色阶调整和输出色阶调整，其中输入色阶调整有3个调整点，即通常所说的黑场、白场及灰场调整
#include "MyLib/BMPFile.h"
#include "Debug.h"
//windows
//#include <windows.h>
//unix
#include <unistd.h>

void RGB2YUV(const std::vector<uint8_t> &imageData, std::vector<uint8_t> &YUVImageData, int width, int height) {
    for (int i = 0; i < width * height; ++i) {
        int r = imageData[i * 3];
        int g = imageData[i * 3 + 1];
        int b = imageData[i * 3 + 2];

        // Convert RGB to YUV
        int y = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);
        int u = static_cast<int>(-0.147 * r - 0.289 * g + 0.436 * b);
        int v = static_cast<int>(0.615 * r - 0.515 * g - 0.100 * b);

        y = std::min(std::max(y, 0), 255);
        u = std::min(std::max(u, 0), 255);
        v = std::min(std::max(v, 0), 255);

        // Store YUV values in the output image
        YUVImageData[i * 3] = static_cast<uint8_t>(y);
        YUVImageData[i * 3 + 1] = static_cast<uint8_t>(u);
        YUVImageData[i * 3 + 2] = static_cast<uint8_t>(v);
    }
}

int RGB2YIQ(std::vector<uint8_t> &YIQImageData, std::vector<uint8_t> &imageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t r = imageData[index];
            uint8_t g = imageData[index + 1];
            uint8_t b = imageData[index + 2];
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

int RGB2LAB(std::vector<uint8_t> &LABImageData, std::vector<uint8_t> &imageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t r = imageData[index];
            uint8_t g = imageData[index + 1];
            uint8_t b = imageData[index + 2];
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

int YUV2RGB(std::vector<uint8_t> &YUVImageData, std::vector<uint8_t> &imageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t y = YUVImageData[index];
            uint8_t u = YUVImageData[index + 1];
            uint8_t v = YUVImageData[index + 2];
            double_t r = y + 1.13983 * v;
            double_t g = y - 0.39465 * u - 0.58060 * v;
            double_t b = y + 2.03211 * u;
            r = std::min(255.0, std::max(0.0, r));
            g = std::min(255.0, std::max(0.0, g));
            b = std::min(255.0, std::max(0.0, b));
            imageData[index] = static_cast<uint8_t>(r);
            imageData[index + 1] = static_cast<uint8_t>(g);
            imageData[index + 2] = static_cast<uint8_t>(b);
        }
    }
    return 0;
}

int YIQ2RGB(std::vector<uint8_t> &YIQImageData, std::vector<uint8_t> &imageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            uint8_t y = YIQImageData[index];
            uint8_t i = YIQImageData[index + 1];
            uint8_t q = YIQImageData[index + 2];
            double_t r = y + 0.956 * i + 0.621 * q;
            double_t g = y - 0.272 * i - 0.647 * q;
            double_t b = y - 1.106 * i + 1.703 * q;
            r = std::min(255.0, std::max(0.0, r));
            g = std::min(255.0, std::max(0.0, g));
            b = std::min(255.0, std::max(0.0, b));
            imageData[index] = static_cast<uint8_t>(r);
            imageData[index + 1] = static_cast<uint8_t>(g);
            imageData[index + 2] = static_cast<uint8_t>(b);
        }
    }
    return 0;
}

int LAB2RGB(std::vector<uint8_t> &LABImageData, std::vector<uint8_t> &imageData, int32_t width, int32_t height) {
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            int index = (j * width + k) * 3;
            double_t x = LABImageData[index];
            double_t y = LABImageData[index + 1];
            double_t z = LABImageData[index + 2];
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

            imageData[index] = static_cast<uint8_t>(r);
            imageData[index + 1] = static_cast<uint8_t>(g);
            imageData[index + 2] = static_cast<uint8_t>(b);
        }
    }
    return 0;
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t  height=myValue.bmpInfo.height;
    int32_t  width=myValue.bmpInfo.width;
    std::vector<uint8_t>imageData=myValue.imageData;
    //outputBinToFile(imageData, "imageData.txt");
    std::vector<uint8_t> YUVImageData(imageData.size());
    YUVImageData = imageData;
    std::vector<uint8_t> YIQImageData(imageData.size());
    YIQImageData = imageData;
    std::vector<uint8_t> LABImageData(imageData.size());
    LABImageData = imageData;


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
                RGB2YUV(imageData, YUVImageData, width, height);
                MYFunction::WriteBMPFile("RGB_TO_YUV.bmp", YUVImageData,myValue.bmp,myValue.bmpInfo);
                //outputBinToFile(YUVImageData, "YUVImage.txt");

                isLoop = true;
                break;
            }
            case 2: {

                RGB2YIQ(YIQImageData, imageData, width, height);
                MYFunction::WriteBMPFile("RGB_TO_YIQ.bmp", YIQImageData,myValue.bmp,myValue.bmpInfo);
                outputBinToFile(YIQImageData, "YIQImageData.txt");

                isLoop = true;
                break;
            }
            case 3: {

                RGB2LAB(LABImageData, imageData, width, height);
                MYFunction::WriteBMPFile("RGB_TO_LAB.bmp", LABImageData,myValue.bmp,myValue.bmpInfo);
                outputBinToFile(LABImageData, "LABImageData.txt");

                isLoop = true;
                break;
            }
            case 4: {

                YUV2RGB(YUVImageData, imageData, width, height);
                MYFunction::WriteBMPFile("YUV_TO_RGB.bmp", imageData,myValue.bmp,myValue.bmpInfo);
                outputBinToFile(imageData, "YUV_TO_RGB.txt");


                isLoop = true;
                break;
            }
            case 5: {

                YIQ2RGB(YIQImageData, imageData, width, height);
                MYFunction::WriteBMPFile("YIQ_TO_RGB.bmp", imageData,myValue.bmp,myValue.bmpInfo);
                outputBinToFile(imageData, "YIQ_TO_RGB.txt");


                isLoop = true;
                break;
            }
            case 6: {
                LAB2RGB(LABImageData, imageData, width, height);
                MYFunction::WriteBMPFile("LAB_TO_RGB.bmp", imageData,myValue.bmp,myValue.bmpInfo);
                outputBinToFile(imageData, "LABImage.txt");
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
