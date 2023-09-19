//
// Created by ztheng on 2023/9/5.
// done

#include "BMPFile.h"
#include "Debug.h"

#include "BMPFile.cpp"
int Brightness(std::vector<uint8_t> &brightnessImageData, double_t brightnessValue) {
    if (brightnessValue >= -150 && brightnessValue <= 150) {
        for (unsigned char &i: brightnessImageData) {
            double_t newValue = static_cast<double_t>(i) + brightnessValue;
            if (newValue < 0) {
                newValue = 0;
            } else if (newValue > 255) {
                newValue = 255;
            }
            i = static_cast<uint8_t>(newValue);
        }
        return 0;
    } else {
        std::cout << "out of range,brightnessValue is between -150 to 150, please try again!" << std::endl;
        return 1;
    }

}

//对比度
int Contrast(std::vector<uint8_t> &contrastImageData, double_t contrastValue) {
    if (contrastValue >= -50 && contrastValue <= 100) {
        double_t factor = (100.0 + contrastValue) / 100.0;
        for (size_t i = 0; i < contrastImageData.size(); i += 3) {

            contrastImageData[i] = std::max(0, std::min(255,
                                                        static_cast<int>(factor * (contrastImageData[i] - 128) + 128)));
            contrastImageData[i + 1] = std::max(0, std::min(255,
                                                            static_cast<int>(factor * (contrastImageData[i + 1] - 128) +
                                                                             128)));
            contrastImageData[i + 2] = std::max(0, std::min(255,
                                                            static_cast<int>(factor * (contrastImageData[i + 2] - 128) +
                                                                    128)));
        }
        return 0;
    } else {
        std::cout << "out of range,contrastValue is between -50 to 100, please try again!" << std::endl;
        return 1;
    }
}

//饱和度
void Saturation(std::vector<uint8_t> &saturationImageData, int32_t width, int32_t height, double_t saturationValue) {

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3;
            uint8_t r = saturationImageData[index];
            uint8_t g = saturationImageData[index + 1];
            uint8_t b = saturationImageData[index + 2];

            // calc gray
            uint8_t gray = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);

            // calc color
            r = static_cast<uint8_t>((1 - saturationValue) * gray + saturationValue * r);
            g = static_cast<uint8_t>((1 - saturationValue) * gray + saturationValue * g);
            b = static_cast<uint8_t>((1 - saturationValue) * gray + saturationValue * b);

            // update
            saturationImageData[index] = r;
            saturationImageData[index + 1] = g;
            saturationImageData[index + 2] = b;
        }
    }

}

int main() {
    std::vector<uint8_t> imageData = MYFunction::ReadBMPFile(FILENAME);

    std::vector<uint8_t> brightnessImageData(imageData.size());
    brightnessImageData = imageData;
    std::vector<uint8_t> contrastImageData(imageData.size());
    contrastImageData = imageData;
    std::vector<uint8_t> saturationImageData(imageData.size());
    saturationImageData = imageData;

    bool isLoop = true;
    while (isLoop) {
        int choice = 1;
        std::cout << "select a function:" << std::endl
                  << "1.brightness" << std::endl
                  << "2.contrast" << std::endl
                  << "3.Saturation" << std::endl
                  << "4.exit" << std::endl
                  << "input:";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                inputBrightness:
                std::cout << "How much brightness do you want to increase or decrease?" << std::endl
                          << "please input:";
                // Brightness function
                double_t brightnessValue;
                std::cin >> brightnessValue;
                //OutputToFile(imageData,"beforeBrightness");
                int result = Brightness(brightnessImageData, brightnessValue);
                //OutputToFile(imageData,"afterBrightness");
                if (result == 1) {
                    goto inputBrightness;
                } else {
                    MYFunction::WriteBMPFile("outColorBrightness.bmp", brightnessImageData);
                }
                isLoop = true;
                break;
            }
            case 2: {
                inputContrastValue:
                std::cout << "How much contrast do you want to increase or decrease?" << std::endl
                          << "please input:";
                double_t contrastValue;
                std::cin >> contrastValue;
                //Contrast function
                int result = Contrast(contrastImageData, contrastValue);
                if (result == 1) {
                    goto inputContrastValue;
                } else {
                    MYFunction::WriteBMPFile("outColorContrastValue.bmp", contrastImageData);

                }
                isLoop = true;
                break;
            }
            case 3: {
                std::cout << "please input saturation value:" << std::endl;
                double_t saturationValue;
                std::cin >> saturationValue;
                //Saturation function

                Saturation(saturationImageData, bmpInfo.width, bmpInfo.height, saturationValue);
                MYFunction::WriteBMPFile("outColorSaturation.bmp", saturationImageData);
                isLoop = true;
                break;
            }
            case 4:
                exit(0);
            default: {
                std::cout << "input error! try again!" << std::endl;
            }
        }
    }

}

