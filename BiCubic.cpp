#include "MyLib/BMPFile.h"
//权重函数
float cubicWeight(float t) {
    // Cubic interpolation kernel
    if (std::abs(t) <= 1.0f) {
        return 1.5f * std::abs(t) * std::abs(t) * std::abs(t) - 2.5f * t * t + 1.0f;
    } else if (std::abs(t) <= 2.0f) {
        return -0.5f * std::abs(t) * std::abs(t) * std::abs(t) + 2.5f * t * t - 4.0f * std::abs(t) + 2.0f;
    } else {
        return 0.0f;
    }
}


std::vector<uint8_t>
LargeImage(const std::vector<uint8_t> &imageData, int32_t width, int32_t height, int32_t newWidth, int32_t newHeight) {
    std::vector<uint8_t> resizedImage(newWidth * newHeight * 3);

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            auto srcX = static_cast<float>(x) * width / newWidth;
            auto srcY = static_cast<float>(y) * height / newHeight;

            srcX = std::max(0.0f, std::min(srcX, static_cast<float>(width - 1)));
            srcY = std::max(0.0f, std::min(srcY, static_cast<float>(height - 1)));


            float weights[4][4];

            // 权重
            for (int j = -1; j <= 2; ++j) {
                for (int i = -1; i <= 2; ++i) {
                    int xi = static_cast<int>(std::floor(srcX)) + i;
                    int yj = static_cast<int>(std::floor(srcY)) + j;
                    xi = std::max(0, std::min(xi, width - 1));
                    yj = std::max(0, std::min(yj, height - 1));
                    float wx = cubicWeight(srcX - (xi + 0.5f));
                    float wy = cubicWeight(srcY - (yj + 0.5f));
                    weights[j + 1][i + 1] = wx * wy;
                }
            }

            // 插值
            for (int channel = 0; channel < 3; ++channel) {
                float interpolatedValue = 0.0f;
                for (int j = 0; j < 4; ++j) {
                    for (int i = 0; i < 4; ++i) {
                        int xi = static_cast<int>(std::floor(srcX)) + i - 1;
                        int yj = static_cast<int>(std::floor(srcY)) + j - 1;
                        xi = std::max(0, std::min(xi, width - 1));
                        yj = std::max(0, std::min(yj, height - 1));
                        interpolatedValue += weights[j][i] * imageData[(yj * width + xi) * 3 + channel];
                    }
                }

                interpolatedValue = std::max(0.0f, std::min(255.0f, interpolatedValue));
                resizedImage[(y * newWidth + x) * 3 + channel] = static_cast<uint8_t>(interpolatedValue);
            }
        }
    }
    return resizedImage;
}

std::vector<uint8_t>
SmallImage(const std::vector<uint8_t> &imageData, int32_t width, int32_t height, int32_t newWidth, int32_t newHeight) {
    std::vector<uint8_t> resizedImage(newWidth * newHeight * 3);

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            auto srcX = static_cast<float>(x) * width / newWidth;
            auto srcY = static_cast<float>(y) * height / newHeight;

            srcX = std::max(0.0f, std::min(srcX, static_cast<float>(width - 1)));
            srcY = std::max(0.0f, std::min(srcY, static_cast<float>(height - 1)));

            float weights[4][4];
            //权重
            for (int j = -1; j <= 2; ++j) {
                for (int i = -1; i <= 2; ++i) {
                    int xi = static_cast<int>(std::floor(srcX)) + i;
                    int yj = static_cast<int>(std::floor(srcY)) + j;

                    xi = std::max(0, std::min(xi, width - 1));
                    yj = std::max(0, std::min(yj, height - 1));

                    float wx = cubicWeight(srcX - (xi + 0.5f));
                    float wy = cubicWeight(srcY - (yj + 0.5f));
                    weights[j + 1][i + 1] = wx * wy;
                }
            }

            // 插值
            for (int channel = 0; channel < 3; ++channel) {
                float interpolatedValue = 0.0f;
                for (int j = 0; j < 4; ++j) {
                    for (int i = 0; i < 4; ++i) {
                        int xi = static_cast<int>(std::floor(srcX)) + i - 1;
                        int yj = static_cast<int>(std::floor(srcY)) + j - 1;
                        xi = std::max(0, std::min(xi, width - 1));
                        yj = std::max(0, std::min(yj, height - 1));

                        interpolatedValue += weights[j][i] * imageData[(yj * width + xi) * 3 + channel];
                    }
                }

                interpolatedValue = std::max(0.0f, std::min(255.0f, interpolatedValue));
                resizedImage[(y * newWidth + x) * 3 + channel] = static_cast<uint8_t>(interpolatedValue);
            }
        }
    }
    return resizedImage;
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    std::vector<uint8_t> imageData = myValue.imageData;

    // 图像放大
    int32_t newWidth = width * 2;
    int32_t newHeight = height * 2;
    std::vector<uint8_t> largeImageData = LargeImage(imageData, width, height, newWidth, newHeight);
    MYFunction::SetBMPHeaderValues(myValue.bmp, myValue.bmpInfo, newWidth, newHeight, 24);
    MYFunction::WriteBMPFile("outputBiCubicLarge.bmp", largeImageData, myValue.bmp, myValue.bmpInfo);

    // 图像缩小
    newWidth = width / 2;
    newHeight = height / 2;
    std::vector<uint8_t> smallImageData = SmallImage(imageData, width, height, newWidth, newHeight);
    MYFunction::SetBMPHeaderValues(myValue.bmp, myValue.bmpInfo, newWidth, newHeight, 24);
    MYFunction::WriteBMPFile("outputBiCubicSmall.bmp", smallImageData, myValue.bmp, myValue.bmpInfo);

    return 0;
}
