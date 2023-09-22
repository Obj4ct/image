#include "MyLib/BMPFile.h"

// 锐化

double Gaussian(double sigma, int x, int y);

std::vector<uint8_t> Gauss(const std::vector<uint8_t> &imageData, int width, int height, double sigma) {
    std::vector<uint8_t> blurImageData(imageData.size());

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;
            double weightSum = 0.0;

            for (int j = -2; j <= 2; j++) {
                for (int i = -2; i <= 2; i++) {
                    int pixelX = x + i;
                    int pixelY = y + j;
                    if (pixelX >= 0 && pixelX < width && pixelY >= 0 && pixelY < height) {
                        int pixelIndex = (pixelY * width + pixelX) * 3;
                        double weight = Gaussian(sigma, i, j);
                        r += static_cast<double>(imageData[pixelIndex]) * weight;
                        g += static_cast<double>(imageData[pixelIndex + 1]) * weight;
                        b += static_cast<double>(imageData[pixelIndex + 2]) * weight;
                        weightSum += weight;
                    }
                }
            }

            int index = (y * width + x) * 3;
            blurImageData[index] = static_cast<uint8_t>(r / weightSum);
            blurImageData[index + 1] = static_cast<uint8_t>(g / weightSum);
            blurImageData[index + 2] = static_cast<uint8_t>(b / weightSum);
        }
    }

    return blurImageData;
}

double Gaussian(double sigma, int x, int y) {
    double exponent = -(x * x + y * y) / (2.0 * sigma * sigma);
    return exp(exponent) / (2.0 * M_PI * sigma * sigma);
}

std::vector<uint8_t> HighContrast(const std::vector<uint8_t> &imageData, const std::vector<uint8_t> &blurImageData) {
    std::vector<uint8_t> highContrastImageData(imageData.size());

    for (size_t i = 0; i < imageData.size(); i++) {
        int between = static_cast<int>(imageData[i]) - static_cast<int>(blurImageData[i]);
        highContrastImageData[i] = static_cast<uint8_t>(between + 128); //0-255
    }

    return highContrastImageData;
}

std::vector<uint8_t> Sharpen(const std::vector<uint8_t> &imageData, const std::vector<uint8_t> &highContrastImageData) {
    std::vector<uint8_t> sharpenImageData(imageData.size());

    for (size_t i = 0; i < imageData.size(); i++) {
        int addValue = static_cast<int>(imageData[i]) + static_cast<int>(highContrastImageData[i]);
        sharpenImageData[i] = static_cast<uint8_t>(std::max(std::min(addValue-170, 255), 0));

    }

    return sharpenImageData;
}

int main() {
    //锐化=原图+高反差
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    std::vector<uint8_t> imageData = myValue.imageData;
    // sigma 模糊程度
    double sigma = 1.5;
    std::vector<uint8_t> blurImageData = Gauss(imageData, width, height,sigma);
    std::vector<uint8_t> highContrast = HighContrast(imageData, blurImageData);
    std::vector<uint8_t> sharpenImageData = Sharpen(imageData, highContrast);
    MYFunction::WriteBMPFile("outputSharpen.bmp", sharpenImageData, myValue.bmp, myValue.bmpInfo);
    return 0;
}
