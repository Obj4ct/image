//
// Created by ZThenG on 2023/9/25/0025.
//
#include "MyLib/BMPFile.h"
#include "MyLib/BMPFile.cpp"

enum BlendMode {
    BLEND_NORMAL,     // 正常模式
    BLEND_MULTIPLY,   // 正片叠底
    BLEND_SCREEN,     // 滤色
    BLEND_OVERLAY,    // 叠加

};

void blendPixels(uint8_t &destR, uint8_t &destG, uint8_t &destB, uint8_t srcR, uint8_t srcG, uint8_t srcB, BlendMode blendMode) {
    double alpha = 1.0; // ]控制混合程度

    switch (blendMode) {
        case BLEND_NORMAL:
            destR = srcR;
            destG = srcG;
            destB = srcB;
            break;

        case BLEND_MULTIPLY:

            destR = static_cast<uint8_t>((destR * srcR) / 255);
            destG = static_cast<uint8_t>((destG * srcG) / 255);
            destB = static_cast<uint8_t>((destB * srcB) / 255);
            break;

        case BLEND_SCREEN:
            destR = static_cast<uint8_t>(255 - (255 - destR) * (255 - srcR) / 255);
            destG = static_cast<uint8_t>(255 - (255 - destG) * (255 - srcG) / 255);
            destB = static_cast<uint8_t>(255 - (255 - destB) * (255 - srcB) / 255);
            break;

        case BLEND_OVERLAY:
            if (destR < 128) {
                destR = static_cast<uint8_t>((2 * destR * srcR) / 255);
            } else {
                destR = static_cast<uint8_t>(255 - (2 * (255 - destR) * (255 - srcR)) / 255);
            }

            if (destG < 128) {
                destG = static_cast<uint8_t>((2 * destG * srcG) / 255);
            } else {
                destG = static_cast<uint8_t>(255 - (2 * (255 - destG) * (255 - srcG)) / 255);
            }

            if (destB < 128) {
                destB = static_cast<uint8_t>((2 * destB * srcB) / 255);
            } else {
                destB = static_cast<uint8_t>(255 - (2 * (255 - destB) * (255 - srcB)) / 255);
            }
            break;
        default:
            break;
    }
}

void applyEffect(std::vector<uint8_t> &imageData, const std::vector<uint8_t> &effectData, int width, int height, BlendMode blendMode) {

    if (imageData.size() != effectData.size()) {
        return;
    }

    for (size_t i = 0; i < imageData.size(); i += 3) {
        uint8_t &destR = imageData[i];
        uint8_t &destG = imageData[i + 1];
        uint8_t &destB = imageData[i + 2];

        uint8_t srcR = effectData[i];
        uint8_t srcG = effectData[i + 1];
        uint8_t srcB = effectData[i + 2];
        blendPixels(destR, destG, destB, srcR, srcG, srcB, blendMode);
    }
}

int main() {
    MyValue originalImage = MYFunction::ReadBMPFile(FILENAME);
    MyValue effectImage = MYFunction::ReadBMPFile("back.bmp");

    int32_t width = originalImage.bmpInfo.width;
    int32_t height = originalImage.bmpInfo.height;
    std::vector<uint8_t> originalImageData = originalImage.imageData;
    std::vector<uint8_t> effectImageData = effectImage.imageData;

    BlendMode blendMode = BLEND_OVERLAY;
    applyEffect(originalImageData, effectImageData, width, height, blendMode);
    MYFunction::WriteBMPFile("outputBlendedImage.bmp", originalImageData, originalImage.bmp, originalImage.bmpInfo);

    return 0;
}
