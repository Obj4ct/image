//
// Created by ztheng on 2023/9/5.
// done

#include "BMPFile.h"
#include "Debug.h"

void AverageBlur(std::vector<uint8_t> &imageData, uint32_t width, uint32_t height) {
    std::vector<uint8_t> blurImage(imageData);
    for (uint32_t y = 0; y < height; y++) {
        for (int x = 0; x < width; ++x) {
            uint32_t index = (y * width + x) * 3;
            uint32_t left = imageData[index + 1];
            uint32_t right = imageData[index - 1];
            uint32_t up = imageData[index - width];
            uint32_t down = imageData[index + width];
            uint32_t mid = imageData[index];
            uint32_t leftUp = imageData[index - width + 1];
            uint32_t rightUp = imageData[index - width - 1];
            uint32_t leftDown = imageData[index + width - 1];
            uint32_t rightDown = imageData[index + width + 1];
            auto averPix = (left + right + up + down + mid + leftUp + rightUp + leftDown + rightDown)/9;
            imageData[index] =imageData[index]/averPix;
        }
    }

}
//用一个奇数点的移动窗口，并将模板中心与图中某个像素位置重合；
//读取模板下各对应的像素灰度值/从小到大，从大到小均可；
//选取灰度序列中，中间的一个像素的灰度值；
//将中间值赋给模板中心位置的像素。


int main() {
    std::vector<uint8_t>imageData=ReadBMPFile(FILENAME);
    // function
//    int32_t radius = 1;

    AverageBlur(imageData, bmpInfo.width, bmpInfo.height);
    WriteBMPFile("outputAverBlur.bmp", imageData, bmp, bmpInfo);

    return 0;
}
