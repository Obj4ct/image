//
// Created by ZThenG on 2023/9/16/0016.
//

#include "BMPFile.h"
#include "BMPFile.cpp"
uint32_t CalSquareSum(std::vector<uint8_t> imageData) {
    uint32_t sum = 0;

    for (unsigned int i = 0; i < imageData.size(); ++i) {
        unsigned int pixVal = imageData[i];
        sum += pixVal * pixVal;
    }

    return sum;
}

uint32_t CalVariance(std::vector<uint8_t> imageData) {
    uint32_t aver, tempSum = 0, sum = 0, variance;
    for (int i = 0; i < imageData.size(); i++) {
        sum += imageData[i];
    }
    aver = sum / imageData.size();
    for (int i = 0; i < imageData.size(); ++i) {
        tempSum += ((imageData[i] - aver) * (imageData[i] - aver));

    }
    variance = tempSum / imageData.size();
    return variance;
}

double_t CalStandard(std::vector<uint8_t> imageData) {
    uint32_t aver, tempSum = 0, sum = 0, variance;
    for (int i = 0; i < imageData.size(); i++) {
        sum += imageData[i];
    }
    aver = sum / imageData.size();
    for (int i = 0; i < imageData.size(); ++i) {
        tempSum += ((imageData[i] - aver) * (imageData[i] - aver));

    }
    variance = tempSum / imageData.size();


    double_t standard = std::sqrt(variance);
    return standard;
}

std::vector<int> CalHistogram(const std::vector<uint8_t> &imageData) {
    std::vector<int> histogram(255);


    for (size_t i = 0; i < imageData.size(); i++) {
        uint8_t pixel = imageData[i];
        histogram[pixel]++;
    }

    return histogram;
}

void Save(const std::vector<int> &histogram, const std::string &filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cout << "Unable to create histogram file" << std::endl;
        return;
    }

    for (int i = 0; i < histogram.size(); ++i) {
        outputFile << "直方图数据" << i << ": " << histogram[i] << std::endl;
    }

    outputFile.close();
}

int main() {
    std::vector<uint8_t> imageData = myFunction.ReadBMPFile(FILENAME);
    bool isLoop = true;
    while (isLoop) {
        int choice = 1;
        std::cout << "输入你要的操作::" << std::endl
                  << "1.平方和" << std::endl
                  << "2.方差" << std::endl
                  << "3.标准差" << std::endl
                  << "4.直方图数据" << std::endl
                  << "5.exit" << std::endl
                  << "input:";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                //OutputToFile(imageData,"beforeBrightness");
                uint32_t sum = CalSquareSum(imageData);
                //OutputToFile(imageData,"afterBrightness");
                std::cout << "平方和是: " << sum << std::endl;
                isLoop = true;
                break;
            }
            case 2: {
                uint32_t variance = CalVariance(imageData);
                std::cout << "方差是： " << variance << std::endl;
                isLoop = true;
                break;
            }
            case 3: {
                double_t standard = CalStandard(imageData);
                std::cout << "标准差是：" << standard << std::endl;
                isLoop = true;
                break;
            }
            case 4: {

                std::vector<int> histogram = CalHistogram(imageData);
                Save(histogram, "data.txt");
                std::cout << "直方图数据保存到data.txt" << std::endl;
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

