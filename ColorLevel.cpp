//
// Created by ztheng on 2023/9/5.
//done

// 色阶调整分输入色阶调整和输出色阶调整，其中输入色阶调整有3个调整点，即通常所说的黑场、白场及灰场调整
#include "BMPFile.h"

void ColorLevelChanel_R(std::vector<uint8_t> &rImageData, int32_t width, int32_t height, double_t brightness,
                        double_t contrast) {

    for (int i = 0; i < rImageData.size(); i += 3) {
        uint8_t r = rImageData[i];

        // brightness
        r = std::min(255, std::max(0, static_cast<int>(r + brightness)));
        // contrast
        //128：midGray
        r = std::min(255, std::max(0, static_cast<int>((r - 128) * contrast + 128)));
        rImageData[i] = r;
    }
}

void ColorLevelChanel_G(std::vector<uint8_t> &gImageData, int32_t width, int32_t height, double_t brightness,
                        double_t contrast) {

    for (int i = 0; i < gImageData.size(); i += 3) {
        uint8_t G = gImageData[i + 1];

        // brightness
        G = std::min(255, std::max(0, static_cast<int>(G + brightness)));
        // contrast
        //128：midGray
        G = std::min(255, std::max(0, static_cast<int>((G - 128) * contrast + 128)));
        gImageData[i + 1] = G;
    }


}

void ColorLevelChanel_B(std::vector<uint8_t> &bImageData, int32_t width, int32_t height, double_t brightness,
                        double_t contrast) {

    for (int i = 0; i < bImageData.size(); i += 3) {
        uint8_t B = bImageData[i + 2];

        // brightness
        B = std::min(255, std::max(0, static_cast<int>(B + brightness)));
        // contrast
        //128：midGray
        B = std::min(255, std::max(0, static_cast<int>((B - 128) * contrast + 128)));
        bImageData[i + 2] = B;
    }


}

void ColorLevelChanel_RGB(std::vector<uint8_t> &rgbImageData, int32_t width, int32_t height, double_t brightness,
                          double_t contrast) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3;
            uint8_t r = rgbImageData[index];
            uint8_t g = rgbImageData[index + 1];
            uint8_t b = rgbImageData[index + 2];
            //brightness
            r = std::min(255, std::max(0, static_cast<int>(r + brightness)));
            g = std::min(255, std::max(0, static_cast<int>(g + brightness)));
            b = std::min(255, std::max(0, static_cast<int>(b + brightness)));
            //contrast
            r = std::min(255, std::max(0, static_cast<int>((r - 128) * contrast + 128)));
            g = std::min(255, std::max(0, static_cast<int>((g - 128) * contrast + 128)));
            b = std::min(255, std::max(0, static_cast<int>((b - 128) * contrast + 128)));

            // update
            rgbImageData[index] = r;
            rgbImageData[index + 1] = g;
            rgbImageData[index + 2] = b;
        }
    }
}

int main() {
    std::vector<uint8_t> imageData = ReadBMPFile(FILENAME);
    //CreateNewBmp();
    std::vector<uint8_t> rImageData(imageData.size());
    rImageData = imageData;
    std::vector<uint8_t> gImageData(imageData.size());
    gImageData = imageData;
    std::vector<uint8_t> bImageData(imageData.size());
    bImageData = imageData;
    std::vector<uint8_t> rgbImageData(imageData.size());
    rgbImageData = imageData;

    double_t brightness, contrast;
    bool isLoop = true;
    while (isLoop) {
        int choice = 1;
        std::cout << "which chanel do you like to change:" << std::endl
                  << "1.r" << std::endl
                  << "2.g" << std::endl
                  << "3.b" << std::endl
                  << "4.RGB(All chanel)" << std::endl
                  << "5.exit" << std::endl
                  << "input:";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "How much r chanel do you want to increase or decrease?" << std::endl
                          << "please input brightness:" << std::endl;
                std::cin >> brightness;
                std::cout << "please input contrast:" << std::endl;
                std::cin >> contrast;
                ColorLevelChanel_R(rImageData, bmpInfo.width, bmpInfo.height, brightness, contrast);
                WriteBMPFile("changeColorLever_R.bmp", rImageData, bmp, bmpInfo);

                isLoop = true;
                break;
            }
            case 2: {
                std::cout << "How much g chanel do you want to increase or decrease?" << std::endl
                          << "please input brightness:" << std::endl;
                std::cin >> brightness;
                std::cout << "please input contrast:" << std::endl;
                std::cin >> contrast;
                ColorLevelChanel_G(gImageData, bmpInfo.width, bmpInfo.height, brightness, contrast);
                WriteBMPFile("changeColorLever_G.bmp", gImageData, bmp, bmpInfo);
                isLoop = true;
                break;
            }
            case 3: {
                std::cout << "How much b chanel do you want to increase or decrease?" << std::endl
                          << "please input brightness:" << std::endl;
                std::cin >> brightness;
                std::cout << "please input contrast:" << std::endl;
                std::cin >> contrast;
                ColorLevelChanel_B(bImageData, bmpInfo.width, bmpInfo.height, brightness, contrast);
                WriteBMPFile("changeColorLever_B.bmp", bImageData, bmp, bmpInfo);

                isLoop = true;
                break;
            }
            case 4: {
                std::cout << "How much RGB chanel do you want to increase or decrease?" << std::endl
                          << "please input brightness:" << std::endl;
                std::cin >> brightness;
                std::cout << "please input contrast:" << std::endl;
                std::cin >> contrast;
                // RGB function
                ColorLevelChanel_RGB(rgbImageData, bmpInfo.width, bmpInfo.height, brightness, contrast);
                std::ofstream outputFile("changeColorLever_RGB.bmp", std::ios::binary);
                WriteBMPFile("changeColorLever_RGB.bmp", rgbImageData, bmp, bmpInfo);
                isLoop = true;
                break;
            }

            case 5:
                exit(0);
            default: {
                std::cout << "input error! try again!" << std::endl;
            }
        }
    }


}
