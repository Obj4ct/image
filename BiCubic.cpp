//双立方插值

#include "MyLib/BMPFile.h"
#include <vector>
#include <cmath>

// 计算双立方插值权重
std::vector<double> CalculateWeights(double t) {
    std::vector<double> weights(4);
    double t2 = t * t;
    double t3 = t * t2;

    weights[0] = 0.5 * (-t3 + 2.0 * t2 - t);
    weights[1] = 0.5 * (3.0 * t3 - 5.0 * t2 + 2.0);
    weights[2] = 0.5 * (-3.0 * t3 + 4.0 * t2 + t);
    weights[3] = 0.5 * (t3 - t2);

    return weights;
}

// 双立方插值
std::vector<uint8_t>
SmallImage(const std::vector<uint8_t> &imageData, int32_t width, int32_t height, int32_t newWidth, int32_t newHeight) {
    std::vector<uint8_t> resizedImage(newWidth * newHeight * 3);

    double scaleX = static_cast<double>(width) / newWidth;
    double scaleY = static_cast<double>(height) / newHeight;

    for (int32_t y = 0; y < newHeight; y++) {
        for (int32_t x = 0; x < newWidth; x++) {
            double srcX = x * scaleX;
            double srcY = y * scaleY;
            auto x1 = static_cast<int32_t>(srcX);
            int32_t x0 = std::max(x1 - 1, 0);
            int32_t x2 = std::min(x1 + 1, width - 1);
            int32_t x3 = std::min(x1 + 2, width - 1);
            auto y1 = static_cast<int32_t>(srcY);
            int32_t y0 = std::max(y1 - 1, 0);
            int32_t y2 = std::min(y1 + 1, height - 1);
            int32_t y3 = std::min(y1 + 2, height - 1);
            // 权重
            double tx = srcX - x1;
            double ty = srcY - y1;
            std::vector<double> weightsX = CalculateWeights(tx);
            std::vector<double> weightsY = CalculateWeights(ty);

            // 新像素值
            int32_t destIndex = (y * newWidth + x) * 3;
            int32_t srcIndex1 = (y1 * width + x1) * 3;
            int32_t srcIndex2 = (y1 * width + x2) * 3;
            int32_t srcIndex3 = (y2 * width + x1) * 3;
            int32_t srcIndex4 = (y2 * width + x2) * 3;
            for (int32_t channel = 0; channel < 3; channel++) {
                double sum = 0.0;

                for (int32_t j = 0; j < 4; j++) {
                    for (int32_t i = 0; i < 4; i++) {
                        int32_t newX = x0 + i;
                        int32_t newY = y0 + j;
                        int32_t srcIndex = (newY * width + newX) * 3;
                        sum += imageData[srcIndex + channel] * weightsX[i] * weightsY[j];
                    }
                }

                resizedImage[destIndex + channel] = static_cast<uint8_t>(std::max(0.0, std::min(255.0, sum)));
            }
        }
    }

    return resizedImage;
}

std::vector<uint8_t>
LargeImage(std::vector<uint8_t> &imageData, int32_t width, int32_t height, int32_t newWidth, int32_t newHeight) {
    std::vector<uint8_t> resizedImage(newWidth * newHeight * 3);

    // 计算放大因子
    double scaleX = static_cast<double>(newWidth) / width;
    double scaleY = static_cast<double>(newHeight) / height;

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            // 原图坐标
            double srcX = x / scaleX;
            double srcY = y / scaleY;

            // 计算最近的像素点坐标
            int x1 = static_cast<int>(srcX);
            int x0 = std::max(x1 - 1, 0);
            int x2 = std::min(x1 + 1, width - 1);
            int x3 = std::min(x1 + 2, width - 1);
            int y1 = static_cast<int>(srcY);
            int y0 = std::max(y1 - 1, 0);
            int y2 = std::min(y1 + 1, height - 1);
            int y3 = std::min(y1 + 2, height - 1);

            // 权重
            double tx = srcX - x1;
            double ty = srcY - y1;
            std::vector<double> weightsX = CalculateWeights(tx);
            std::vector<double> weightsY = CalculateWeights(ty);

            // 新像素值
            int destIndex = (y * newWidth + x) * 3;

            for (int channel = 0; channel < 3; channel++) {
                double sum = 0.0;

                for (int j = 0; j < 4; j++) {
                    for (int i = 0; i < 4; i++) {
                        int newX = x0 + i;
                        int newY = y0 + j;
                        int srcIndex = (newY * width + newX) * 3;
                        sum += imageData[srcIndex + channel] * weightsX[i] * weightsY[j];
                    }
                }

                resizedImage[destIndex + channel] = static_cast<uint8_t>(std::max(0.0, std::min(255.0, sum)));
            }
        }
    }

    return resizedImage;
}



int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t width = myValue.bmpInfo.width;
    int32_t height = myValue.bmpInfo.height;
    std::vector<uint8_t> imageData = myValue.imageData;
    std::vector<uint8_t> smallImageData;
    std::vector<uint8_t> largeImageData;

    int32_t newWidth = width / 2;
    int32_t newHeight = height / 2;
    smallImageData = SmallImage(myValue.imageData, width, height, newWidth, newHeight);
    MYFunction::SetBMPHeaderValues(myValue.bmp, myValue.bmpInfo, newWidth, newHeight, myValue.bmpInfo.bitsPerPixel);
    MYFunction::WriteBMPFile("outputBicubicSmall.bmp", smallImageData, myValue.bmp, myValue.bmpInfo);

    newWidth = width * 2;
    newHeight = height * 2;
    largeImageData = LargeImage(myValue.imageData, width, height, newWidth, newHeight);
    MYFunction::SetBMPHeaderValues(myValue.bmp, myValue.bmpInfo, newWidth, newHeight, myValue.bmpInfo.bitsPerPixel);
    MYFunction::WriteBMPFile("outputBicubicLarge.bmp", smallImageData, myValue.bmp, myValue.bmpInfo);

}
