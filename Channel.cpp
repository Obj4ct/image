//
// Created by ztheng on 2023/9/5.
// done
//色彩通道
#include "MyLib/BMPFile.h"
#include "Debug.h"
#include "MyLib/BMPFile.cpp"
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

//饱和度  饱和度函数是在RGB颜色空间下工作的，但这种颜色空间不太适合修改饱和度。通常，会将图像转换为HSV（色相、饱和度、明度）颜色空间，然后在饱和度通道上进行修改，最后再将图像转换回RGB。

// 函数用于将RGB颜色转换为HSV颜色
void RGBtoHSV(uint8_t r, uint8_t g, uint8_t b, double &h, double &s, double &v) {
    double minVal = std::min({r, g, b});
    double maxVal = std::max({r, g, b});
    double delta = maxVal - minVal;

    v = maxVal;

    if (maxVal == 0.0) {
        s = 0;
    } else {
        s = (delta / maxVal);
    }

    if (delta == 0.0) {
        h = 0;
    } else {
        if (r == maxVal) {
            h = (g - b) / delta;
        } else if (g == maxVal) {
            h = 2 + (b - r) / delta;
        } else {
            h = 4 + (r - g) / delta;
        }
        h *= 60;
        if (h < 0) {
            h += 360;
        }
    }
}

// 函数用于将HSV颜色转换回RGB颜色
void HSVtoRGB(double h, double s, double v, uint8_t &r, uint8_t &g, uint8_t &b) {
    if (s == 0.0) {
        r = g = b = static_cast<uint8_t>(v);
    } else {
        h /= 60;
        int i = static_cast<int>(h);
        double f = h - i;
        double p = v * (1 - s);
        double q = v * (1 - s * f);
        double t = v * (1 - s * (1 - f));

        switch (i) {
            case 0: r = static_cast<uint8_t>(v); g = static_cast<uint8_t>(t); b = static_cast<uint8_t>(p); break;
            case 1: r = static_cast<uint8_t>(q); g = static_cast<uint8_t>(v); b = static_cast<uint8_t>(p); break;
            case 2: r = static_cast<uint8_t>(p); g = static_cast<uint8_t>(v); b = static_cast<uint8_t>(t); break;
            case 3: r = static_cast<uint8_t>(p); g = static_cast<uint8_t>(q); b = static_cast<uint8_t>(v); break;
            case 4: r = static_cast<uint8_t>(t); g = static_cast<uint8_t>(p); b = static_cast<uint8_t>(v); break;
            default: r = static_cast<uint8_t>(v); g = static_cast<uint8_t>(p); b = static_cast<uint8_t>(q); break;
        }
    }
}
//HSV 表达彩色图像的方式由三个部分组成：
//
//Hue（色调、色相）
//Saturation（饱和度、色彩纯净度）
//Value（明度）
void Saturation(std::vector<uint8_t> &saturationImageData, int32_t width, int32_t height, double_t saturationValue) {

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3;
            uint8_t r = saturationImageData[index];
            uint8_t g = saturationImageData[index + 1];
            uint8_t b = saturationImageData[index + 2];

            double h, s, v;
            RGBtoHSV(r, g, b, h, s, v);

            // 调整饱和度
            s *= saturationValue;

            // 确保饱和度在0到1之间
            s = std::max(0.0, std::min(1.0, s));

            HSVtoRGB(h, s, v, r, g, b);

            saturationImageData[index] = r;
            saturationImageData[index + 1] = g;
            saturationImageData[index + 2] = b;
        }
    }

}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t  height=myValue.bmpInfo.height;
    int32_t  width=myValue.bmpInfo.width;
    std::vector<uint8_t>imageData=myValue.imageData;
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
                    MYFunction::WriteBMPFile("outColorBrightness.bmp", brightnessImageData,myValue.bmp,myValue.bmpInfo);
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
                    MYFunction::WriteBMPFile("outColorContrastValue.bmp", contrastImageData,myValue.bmp,myValue.bmpInfo);

                }
                isLoop = true;
                break;
            }
            case 3: {
                std::cout << "please input saturation value:" << std::endl;
                double_t saturationValue;
                std::cin >> saturationValue;
                //Saturation function

                Saturation(saturationImageData, width, height, saturationValue);
                MYFunction::WriteBMPFile("outColorSaturation.bmp", saturationImageData,myValue.bmp,myValue.bmpInfo);
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

