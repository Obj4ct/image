//
// Created by Obj4ct on 2023/9/23.
//结构张量实现边缘检测
#include "MyLib/BMPFile.h"


// 定义结构体表示像素
//先定义一个结构体来表示图像中的像素，包括红、绿和蓝三个通道的值
struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};
//边缘检测算子 copy
int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
};

int sobelY[3][3] = {
        {-1, -2, -1},
        {0,  0,  0},
        {1,  2,  1}
};

//copy edge.cpp and change something
std::vector<Pixel> SobelEdge(const std::vector<Pixel> &imageData, int width, int height) {
    std::vector<Pixel> edgeImageData(imageData.size());

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            //x 方向  RGB  y方向 RGB
            int sumXRed = 0;
            int sumXGreen = 0;
            int sumXBlue = 0;
            int sumYRed = 0;
            int sumYGreen = 0;
            int sumYBlue = 0;

            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    //x y坐标
                    int pixelX = x + i - 1;
                    int pixelY = y + j - 1;
                    // 计算像素在一维向量中的索引
                    int pixelIndex = pixelY * width + pixelX;
                    //存RGB
                    Pixel pixel = imageData[pixelIndex];


                    sumXRed += pixel.red * sobelX[j][i];
                    sumXGreen += pixel.green * sobelX[j][i];
                    sumXBlue += pixel.blue * sobelX[j][i];

                    sumYRed += pixel.red * sobelY[j][i];
                    sumYGreen += pixel.green * sobelY[j][i];
                    sumYBlue += pixel.blue * sobelY[j][i];
                }
            }

            // 计算梯度强度
            int edgeValueRed = std::min(std::max(std::abs(sumXRed) + std::abs(sumYRed), 0), 255);
            int edgeValueGreen = std::min(std::max(std::abs(sumXGreen) + std::abs(sumYGreen), 0), 255);
            int edgeValueBlue = std::min(std::max(std::abs(sumXBlue) + std::abs(sumYBlue), 0), 255);

            int index = y * width + x;
            edgeImageData[index].red = static_cast<uint8_t>(edgeValueRed);
            edgeImageData[index].green = static_cast<uint8_t>(edgeValueGreen);
            edgeImageData[index].blue = static_cast<uint8_t>(edgeValueBlue);
        }
    }

    return edgeImageData;
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    int32_t height = myValue.bmpInfo.height;
    int32_t width = myValue.bmpInfo.width;
    //指针允许我们在不改变实际数据的情况下，告诉编译器以不同的方式解释这些数据。
    // 指针提供了一种将数据重新解释为不同类型的方法，以便我们可以以不同的方式处理这些数据，而不必修改它们的值
    std::vector<Pixel> imageData(reinterpret_cast<Pixel *>(myValue.imageData.data()),
                                 reinterpret_cast<Pixel *>(myValue.imageData.data() + myValue.imageData.size()));
    //计算边缘先
    std::vector<Pixel> edgeImageData = SobelEdge(imageData, width, height);
    //指定大小 3个通道
    std::vector<uint8_t> edgeImageDataVector(edgeImageData.size() * sizeof(Pixel));
//    edgeImageDataVector=reinterpret_cast<uint8_t >(imageData);
    std::memcpy(edgeImageDataVector.data(), edgeImageData.data(), edgeImageDataVector.size());

    MYFunction::WriteBMPFile("outputTensorEdge.bmp", edgeImageDataVector, myValue.bmp, myValue.bmpInfo);

    return 0;
}