//
// Created by ZThenG on 2023/9/25/0025.
//
#include "MyLib/BMPFile.h"

enum BlendMode {
    BLEND_NORMAL,     // 正常模式 在“正常”模式下，“混合色”的显示与不透明度的设置有关。
    BLEND_MULTIPLY,   // 正片叠底 其主要特点是以正片作为底图，再将其他图像叠加于其上，并根据叠加图像的颜色来调整底图的亮度和饱和度，产生丰富的合成效果。
    BLEND_SCREEN,     // 滤色 ps中滤色的作用结果和正片叠底刚好相反，它是将两个颜色的互补色的像素值相乘，然后除以255得到的最终色的像素值。通常执行滤色模式后的颜色都较浅。
    BLEND_OVERLAY,    // 叠加 　“叠加”模式把图像的“基色”颜色与“混合色”颜色相混合产生一种中间色。
                      // “基色”内颜色比“混合色”颜色暗的颜色使“混合色”颜色倍增，比“混合色”颜色亮的颜色将使“混合色”颜色被遮盖，
                      // 而图像内的高亮部分和阴影部分保持不变，因此对黑色或白色像素着色时“叠加”模式不起作用。
};

void SwitchBlendMode(uint8_t &destR, uint8_t &destG, uint8_t &destB, uint8_t srcR, uint8_t srcG, uint8_t srcB,
                     BlendMode blendMode, double alpha) {


    switch (blendMode) {
        // 正常模式 在“正常”模式下，“混合色”的显示与不透明度的设置有关。
        //线性插值
        case BLEND_NORMAL: {
            destR = static_cast<uint8_t>((1.0 - alpha) * destR + alpha * srcR);
            destG = static_cast<uint8_t>((1.0 - alpha) * destG + alpha * srcG);
            destB = static_cast<uint8_t>((1.0 - alpha) * destB + alpha * srcB);
            break;
        }
            // 正片叠底 其主要特点是以正片作为底图，再将其他图像叠加于其上，并根据叠加图像的颜色来调整底图的 亮度 和 饱和度，产生丰富的合成效果。
            // 这种混合模式的效果是将源像素的颜色应用于目标像素，具有"遮罩"效果，通常用于创建阴影或混合颜色的效果。
            //   相乘:这种混合模式的核心概念是模拟颜色的遮罩效应或阴影效果。这种效果是通过将源像素的颜色与目标像素的颜色相乘来实现的。
            //  /255 需要保证像素的范围
        case BLEND_MULTIPLY: {
            destR = static_cast<uint8_t>((destR * srcR) / 255);
            destG = static_cast<uint8_t>((destG * srcG) / 255);
            destB = static_cast<uint8_t>((destB * srcB) / 255);
            break;
        }
            // 滤色 ps中滤色的作用结果和正片叠底刚好相反，它是将 两个颜色的互补色 的像素值相乘，然后除以255得到的最终色的像素值。通常执行滤色模式后的颜色都较浅。
        case BLEND_SCREEN: {
            destR = static_cast<uint8_t>((255 - destR) * (255 - srcR) / 255);
            destG = static_cast<uint8_t>((255 - destG) * (255 - srcG) / 255);
            destB = static_cast<uint8_t>((255 - destB) * (255 - srcB) / 255);
            break;
        }
        //“叠加”模式把图像的“基色”颜色与“混合色”颜色相混合产生一种中间色。
        //根据目标像素的亮度选择源像素的亮度值。如果目标像素较暗（R、G、B < 128）,则使用 2 * dest * src / 255 计算；
        // 如果目标像素较亮（R、G、B >= 128），则使用 255 - (2 * (255 - dest) * (255 - src)) / 255 计算
        case BLEND_OVERLAY: {
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
        }

        default:
            break;
    }

}

void Effect(std::vector<uint8_t> &imageData, const std::vector<uint8_t> &effectData, int width, int height,
            BlendMode blendMode) {
    double alpha = 0.0;
    if (imageData.size() != effectData.size()) {
        std::cout << "两张图片的大小不一样！" << std::endl;
    }
    if (blendMode == BLEND_NORMAL) {
        std::cout << "输入你要混合背景的程度(0-1):" << std::endl;
        std::cin >> alpha;
    }


    for (size_t i = 0; i < imageData.size(); i += 3) {

        //获取原图RGB
        uint8_t &destR = imageData[i];
        uint8_t &destG = imageData[i + 1];
        uint8_t &destB = imageData[i + 2];
        //获取背景RGB
        uint8_t srcR = effectData[i];
        uint8_t srcG = effectData[i + 1];
        uint8_t srcB = effectData[i + 2];
        SwitchBlendMode(destR, destG, destB, srcR, srcG, srcB, blendMode, alpha);
    }
}

int main() {
    MyValue originalImage = MYFunction::ReadBMPFile(FILENAME);
    MyValue effectImage = MYFunction::ReadBMPFile(BACKFILE);

    int32_t width = originalImage.bmpInfo.width;
    int32_t height = originalImage.bmpInfo.height;
    std::vector<uint8_t> originalImageData = originalImage.imageData;
    std::vector<uint8_t> effectImageData = effectImage.imageData;
    //选择混合模式
    bool isLoop = true;
    while (isLoop) {
        int choice = 0;
        std::cout << "select a function:" << std::endl
                  << "1.正常模式" << std::endl
                  << "2.正片叠低" << std::endl
                  << "3.滤色" << std::endl
                  << "4.叠加" << std::endl
                  << "5.exit" << std::endl
                  << "input:";
        std::cin >> choice;
        switch (choice) {
            case 1: {
                BlendMode blendMode = BLEND_NORMAL;
                Effect(originalImageData, effectImageData, width, height, blendMode);
                MYFunction::WriteBMPFile("outputBlendedImage.bmp", originalImageData, originalImage.bmp,
                                         originalImage.bmpInfo);
                break;
            }
            case 2: {
                BlendMode blendMode = BLEND_MULTIPLY;
                Effect(originalImageData, effectImageData, width, height, blendMode);
                MYFunction::WriteBMPFile("outputBlendedImage.bmp", originalImageData, originalImage.bmp,
                                         originalImage.bmpInfo);
                break;
            }
            case 3: {
                BlendMode blendMode = BLEND_SCREEN;
                Effect(originalImageData, effectImageData, width, height, blendMode);
                MYFunction::WriteBMPFile("outputBlendedImage.bmp", originalImageData, originalImage.bmp,
                                         originalImage.bmpInfo);
                break;
            }
            case 4: {
                {
                    BlendMode blendMode = BLEND_OVERLAY;
                    Effect(originalImageData, effectImageData, width, height, blendMode);
                    MYFunction::WriteBMPFile("outputBlendedImage.bmp", originalImageData, originalImage.bmp,
                                             originalImage.bmpInfo);
                    break;
                }
            }
            case 5: {
                exit(0);
            }
        }
    }

}
