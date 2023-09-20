////
//// Created by ZThenG on 2023/9/20/0020.
////
#include "MyLib/BMPFile.h"

//高斯核 计算模糊像素值的权重矩阵
double_t kernel[5][5] = {
        {10, 4,  7,  4,  1},
        {4, 16, 26, 16, 4},
        {7, 26, 41, 26, 7},
        {4, 16, 26, 16, 4},
        {1, 4,  7,  4,  1}
};
double_t KernelSum()
{
    double_t sum=0;
    for(uint32_t i=0;i<5;i++)
    {
        for (uint32_t j = 0; j < 5; ++j) {
            sum+=kernel[i][j];
        }
    }
    return sum;
}
std::vector<uint8_t> GaussianBlur(const std::vector<uint8_t> &imageData, int width, int height) {
    std::vector<uint8_t> blurredImage(imageData.size());
    double_t kernelSum=KernelSum();
    std::cout<<kernelSum;
    for (int y = 2; y < height-2; y++) {
        for (int x = 2; x < width-2; x++) {
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;
            int kernelIndex = 0;
            for (int j = 0; j < 5; j++) {
                for (int i = 0; i < 5; i++) {
                    int pixelIndex = ((y + j) * width + (x + i)) * 3;
                    r += static_cast<double>(imageData[pixelIndex]) * kernel[j][i];
                    g += static_cast<double>(imageData[pixelIndex + 1]) * kernel[j][i];
                    b += static_cast<double>(imageData[pixelIndex + 2]) * kernel[j][i];
                    kernelIndex++;
                }
            }
            int index = (y * width + x) * 3;
            blurredImage[index] = static_cast<uint8_t>(r / kernelSum);
            blurredImage[index + 1] = static_cast<uint8_t>(g / kernelSum);
            blurredImage[index + 2] = static_cast<uint8_t>(b / kernelSum);
        }
    }

    return blurredImage;
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    std::vector<uint8_t> imageData = myValue.imageData;
    std::vector<uint8_t> blurredImage = GaussianBlur(imageData, width, height);
    MYFunction::WriteBMPFile("outputGauss.bmp", blurredImage, myValue.bmp, myValue.bmpInfo);

    return 0;
}
