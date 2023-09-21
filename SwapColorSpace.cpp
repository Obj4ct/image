//
// Created by ztheng on 2023/9/5.
//done
//色彩空间


// 色阶调整分输入色阶调整和输出色阶调整，其中输入色阶调整有3个调整点，即通常所说的黑场、白场及灰场调整
#include "MyLib/BMPFile.h"
#include "Debug.h"
//windows
//#include <windows.h>
//unix
#include <unistd.h>

//BT.601
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
            double_t i = 0.596 * r - 0.274 * g - 0.322 * b;
            double_t q = 0.211 * r - 0.523 * g + 0.312 * b;
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
            double rF = r / 255.0;
            double gF = g / 255.0;
            double bF = b / 255.0;
            //RGB to XYZ
            double_t x = rF * 0.4124 + gF * 0.3576 + bF * 0.1805;
            double_t y = rF * 0.2127 + gF * 0.7152 + bF * 0.0722;
            double_t z = rF * 0.0193 + gF * 0.1192 + bF * 0.9503;

            // 对XYZ进行标准化
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

//BT.601
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
            double_t l = LABImageData[index];
            double_t a = LABImageData[index + 1];
            double_t b = LABImageData[index + 2];
            // LAB to XYZ
            double y = (l + 16.0) / 116.0;
            double x = (a / 500.0) + y;
            double z = y - (b / 200.0);

            double rF = (y > 0.008856) ? (3.2406 * pow(x, 3.0) - 1.5372 * pow(y, 3.0) - 0.4986 * pow(z, 3.0))
                                       : (y * 0.008856 - 0.014688);
            double gF = (y > 0.008856) ? (-0.9689 * pow(x, 3.0) + 1.8758 * pow(y, 3.0) + 0.0415 * pow(z, 3.0))
                                       : (y * 0.008856 - 0.014688);
            double bF = (y > 0.008856) ? (0.0557 * pow(x, 3.0) - 0.2040 * pow(y, 3.0) + 1.0570 * pow(z, 3.0))
                                       : (y * 0.008856 - 0.014688);
            double_t r = round((rF <= 0.0031308) ? (rF * 12.92 * 255.0) : ((1.055 * pow(rF, 1.0 / 2.4) - 0.055) * 255.0));
            double_t g = round((gF <= 0.0031308) ? (gF * 12.92 * 255.0) : ((1.055 * pow(gF, 1.0 / 2.4) - 0.055) * 255.0));
            double_t bb = round((bF <= 0.0031308) ? (bF * 12.92 * 255.0) : ((1.055 * pow(bF, 1.0 / 2.4) - 0.055) * 255.0));
            r = std::min(std::max(r, 0.0), 255.0);
            g = std::min(std::max(g, 0.0), 255.0);
            bb = std::min(std::max(bb, 0.0), 255.0);

            imageData[index] = static_cast<uint8_t>(r);
            imageData[index + 1] = static_cast<uint8_t>(g);
            imageData[index + 2] = static_cast<uint8_t>(bb);
        }
    }
    return 0;
}



int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    std::vector<uint8_t> imageData = myValue.imageData;
    outputBinToFile(imageData, "imageData.txt");
    OutputPixToFile(imageData,"beforeImageData.txt");
    std::vector<uint8_t> YUVImageData(imageData.size());

    std::vector<uint8_t> YIQImageData(imageData.size());

    std::vector<uint8_t> LABImageData(imageData.size());

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
                MYFunction::WriteBMPFile("RGB_TO_YUV.bmp", YUVImageData, myValue.bmp, myValue.bmpInfo);
                outputBinToFile(YUVImageData, "YUVImage.txt");

                isLoop = true;
                break;
            }
            case 2: {

                RGB2YIQ(YIQImageData, imageData, width, height);
                MYFunction::WriteBMPFile("RGB_TO_YIQ.bmp", YIQImageData, myValue.bmp, myValue.bmpInfo);
                outputBinToFile(YIQImageData, "YIQImageData.txt");
                OutputPixToFile(YIQImageData,"YIQImageData22.txt");

                isLoop = true;
                break;
            }
            case 3: {

                RGB2LAB(LABImageData, imageData, width, height);
                MYFunction::WriteBMPFile("RGB_TO_LAB.bmp", LABImageData, myValue.bmp, myValue.bmpInfo);
                outputBinToFile(LABImageData, "LABImageData.txt");

                isLoop = true;
                break;
            }
            case 4: {

                YUV2RGB(YUVImageData, imageData, width, height);
                MYFunction::WriteBMPFile("YUV_TO_RGB.bmp", imageData, myValue.bmp, myValue.bmpInfo);
                outputBinToFile(imageData, "YUV_TO_RGB.txt");


                isLoop = true;
                break;
            }
            case 5: {

                OutputPixToFile(YIQImageData,"YIQImageData12.txt");

                YIQ2RGB(YIQImageData, imageData, width, height);
                MYFunction::WriteBMPFile("YIQ_TO_RGB.bmp", imageData, myValue.bmp, myValue.bmpInfo);
                outputBinToFile(imageData, "YIQ_TO_RGB.txt");


                isLoop = true;
                break;
            }
            case 6: {
                LAB2RGB(LABImageData, imageData, width, height);
                MYFunction::WriteBMPFile("LAB_TO_RGB.bmp", imageData, myValue.bmp, myValue.bmpInfo);
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
