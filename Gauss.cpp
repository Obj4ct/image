#include "MyLib/BMPFile.h"
//done
//高斯模糊
// 高斯核，用于模糊像素值的权重矩阵
double_t kernel[5][5] = {
        {1, 4, 6, 4, 1},
        {4, 16, 24, 16, 4},
        {6, 24, 36, 24, 6},
        {4, 16, 24, 16, 4},
        {1, 4, 6, 4, 1}

};

double_t KernelSum() {
    double_t sum = 0;
    for (uint32_t i = 0; i < 5; i++) {
        for (uint32_t j = 0; j < 5; ++j) {
            sum += kernel[i][j];
        }
    }
    return sum;
}

std::vector<uint8_t> Gauss(const std::vector<uint8_t> &imageData, int width, int height) {
    std::vector<uint8_t> blurImageData(imageData.size());
    double_t kernelSum = KernelSum();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;

            for (int j = 0; j < 5; j++) {
                for (int i = 0; i < 5; i++) {
                    int pixelX = x + i - 2;
                    int pixelY = y + j - 2;
                    if (pixelX >= 0 && pixelX < width && pixelY >= 0 && pixelY < height) {
                        int pixelIndex = (pixelY * width + pixelX) * 3;
                        r += static_cast<double>(imageData[pixelIndex]) * kernel[j][i];
                        g += static_cast<double>(imageData[pixelIndex + 1]) * kernel[j][i];
                        b += static_cast<double>(imageData[pixelIndex + 2]) * kernel[j][i];
                    }
                }
            }

            int index = (y * width + x) * 3;
            blurImageData[index] = static_cast<uint8_t>(r / kernelSum);
            blurImageData[index + 1] = static_cast<uint8_t>(g / kernelSum);
            blurImageData[index + 2] = static_cast<uint8_t>(b / kernelSum);
        }
    }

    return blurImageData;
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    std::vector<uint8_t> imageData = myValue.imageData;
    std::vector<uint8_t> blurImageData = Gauss(imageData, width, height);
    MYFunction::WriteBMPFile("outputGauss.bmp", blurImageData, myValue.bmp, myValue.bmpInfo);

    return 0;
}
