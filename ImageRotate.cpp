////
//// Created by ztheng on 2023/9/5.
////
#include "MyLib/BMPFile.h"
//图像旋转
//done

// RotateImage
void RotateImage(std::vector<uint8_t> &imageData, int32_t width, int32_t height, double_t angle)
{
    double_t radians = angle * M_PI / 180.0;
    std::vector<uint8_t> rotatedImageData(imageData.size());

    int32_t centerX = width / 2;
    int32_t centerY = height / 2;

    int32_t rotatedWidth = width;
    int32_t rotatedHeight = height;

    for (int y = 0; y < rotatedHeight; ++y)
    {
        for (int x = 0; x < rotatedWidth; ++x)
        {
            // 计算旋转后的坐标
            double_t rotatedX = std::cos(radians) * (x - centerX) - std::sin(radians) * (y - centerY) + centerX;
            double_t rotatedY = std::sin(radians) * (x - centerX) + std::cos(radians) * (y - centerY) + centerY;

            // 防止插值过程中超出边界
            rotatedX = std::max(0.0, std::min(rotatedX, static_cast<double>(width - 1)));
            rotatedY = std::max(0.0, std::min(rotatedY, static_cast<double>(height - 1)));

            // 双线性插值
            int x0 = std::floor(rotatedX);
            int x1 = std::ceil(rotatedX);
            int y0 = std::floor(rotatedY);
            int y1 = std::ceil(rotatedY);

            double tx = rotatedX - x0;
            double ty = rotatedY - y0;

            for (int c = 0; c < 3; ++c)
            {
                double interpolatedValue = (1 - tx) * (1 - ty) * imageData[y0 * width * 3 + x0 * 3 + c] +
                                           tx * (1 - ty) * imageData[y0 * width * 3 + x1 * 3 + c] +
                                           (1 - tx) * ty * imageData[y1 * width * 3 + x0 * 3 + c] +
                                           tx * ty * imageData[y1 * width * 3 + x1 * 3 + c];

                rotatedImageData[y * rotatedWidth * 3 + x * 3 + c] = static_cast<uint8_t>(interpolatedValue);
            }
        }
    }

    imageData = rotatedImageData;
}
void RotateReverse(std::vector<uint8_t> &imageData, int32_t width, int32_t height, double_t angle) {
    double_t clockwiseAngle = 360.0 - angle;
    RotateImage(imageData, width, height, clockwiseAngle);
}
int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    std::vector<uint8_t> imageData = myValue.imageData;
    // RotateImage Function
    double_t angle;

    bool isLoop = true;
    while (isLoop) {
        int choice = 1;
        std::cout << "选择旋转方向:" << std::endl
                  << "1.顺时针" << std::endl
                  << "2.逆时针" << std::endl
                  << "3.exit" << std::endl
                  << "input:";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "input rotate angle:" << std::endl;
                std::cin >> angle;
                RotateImage(imageData, width, height, angle);

                MYFunction::WriteBMPFile("outputRotate.bmp", imageData, myValue.bmp, myValue.bmpInfo);
                isLoop = true;
                break;
            }
            case 2: {
                std::cout << "input rotate angle:" << std::endl;
                std::cin >> angle;
                //normal
                RotateReverse(imageData, width, height, angle);
                MYFunction::WriteBMPFile("outputRotateReverse.bmp", imageData, myValue.bmp, myValue.bmpInfo);
                isLoop = true;
                break;
                case 3:
                    exit(0);
                default: {
                    std::cout << "input error! try again!" << std::endl;
                }
            }
        }
    }
}
