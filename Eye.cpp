#include "MyLib/BMPFile.h"
#include "MyLib/BMPFile.cpp"


// 应用鱼眼效果以放大指定区域
void Eyes(std::vector<uint8_t> &imageData, int32_t beginX, int32_t beginY, int32_t endX, int32_t endY,uint32_t maxRadius) {
    int32_t newHeight=endY-beginY;
    int32_t newWidth=endX-beginX;
    int32_t centerX=265;
    int32_t centerY=267;
    //遍历每个像素，计算像素到图像中心的距离，并检查是否小于最大半径，以确保像素位于鱼眼效果的范围内。
    for (int y = beginY; y < newHeight; ++y) {
        for (int x = beginX; x < newWidth; ++x) {
            int32_t offsetX = centerX - x;
            int32_t offsetY = centerY - y;
            float distance = std::sqrt(static_cast<float>(offsetX * offsetX + offsetY * offsetY));
            //小于=应用鱼眼
            if (distance < maxRadius) {

                //当前像素相对于图像中心点的极坐标角度
                float angle = std::atan2(static_cast<float>(offsetY), static_cast<float>(offsetX));
                //用于计算每个像素的新半径
                float normalizedRadius = distance / maxRadius;
                //进行非线性变换
                float mappedRadius = normalizedRadius * normalizedRadius;

                //极坐标变换
                int32_t newX = static_cast<int32_t>(centerX + maxRadius * mappedRadius * std::cos(angle));
                int32_t newY = static_cast<int32_t>(centerY + maxRadius * mappedRadius * std::sin(angle));

                for (int channel = 0; channel < 3; ++channel) {
                    imageData[(y * newWidth + x) * 3 + channel] = imageData[(newY * newWidth + newX) * 3 + channel];
                }
            } else {
                // 超出范围保持原始颜色
                for (int channel = 0; channel < 3; ++channel) {
                    imageData[(y * newWidth + x) * 3 + channel] = 0;
                }
            }
        }
    }

}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t width = myValue.bmpInfo.width;
    int32_t height = myValue.bmpInfo.height;
    std::vector<uint8_t> imageData = myValue.imageData;

    // 定义左眼和右眼区域的坐标

    int leftEyeX1 = 248;  // 左眼区域的左上角 x 坐标
    int leftEyeY1 = 244;  // 左眼区域的左上角 y 坐标
    int leftEyeX2 = 284;  // 左眼区域的右下角 x 坐标
    int leftEyeY2 = 272;  // 左眼区域的右下角 y 坐标

    int rightEyeX1 = 318; // 右眼区域的左上角 x 坐标
    int rightEyeY1 = 252; // 右眼区域的左上角 y 坐标
    int rightEyeX2 = 344; // 右眼区域的右下角 x 坐标
    int rightEyeY2 = 274; // 右眼区域的右下角 y 坐标
    uint32_t maxRadius=20;

    Eyes(imageData, leftEyeX1, leftEyeY1, leftEyeX2, leftEyeY2,maxRadius);

    MYFunction::WriteBMPFile("outputFisheyeEyes.bmp", imageData, myValue.bmp, myValue.bmpInfo);

    return 0;
}

