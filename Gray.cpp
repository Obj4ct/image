////
//// Created by ztheng on 2023/9/5.
////
//#include "BMPFile.h"
//
//// 灰度转换函数
//void ConvertToGray(std::vector<uint8_t>& imageData, int width, int height) {
//    for (int i = 0; i < width * height; ++i) {
//        // 获取每个像素的颜色分量
//        uint8_t R = imageData[i * 4];
//        uint8_t G = imageData[i * 4 + 1];
//        uint8_t B = imageData[i * 4 + 2];
//        uint8_t A = imageData[i * 4 + 3];
//
//        // 计算灰度值
//        uint8_t grayValue = static_cast<uint8_t>((R + G + B + A) / 4);
//
//        // 将灰度值写回到图像数据中的每个通道
//        imageData[i * 4] = grayValue;
//        imageData[i * 4 + 1] = grayValue;
//        imageData[i * 4 + 2] = grayValue;
//        imageData[i * 4 + 3] = grayValue;
//    }
//}
//
//int main() {
//
//    std::ifstream inputFile(FILENAME, std::ios::binary);
//    if (!inputFile.is_open()) {
//        std::cout << "unable to open this file" << std::endl;
//        return 1;
//    }
//
//
//    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));
//
//    if (bmp.fileType != 0x4D42) { // BM ASCII
//        std::cout << "file is not invalid!" << std::endl;
//        return 1;
//    }
//
//
//    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));
//
//    //offset
//    int imageDataOffset = bmp.dataOffset;
//
//    //size
//    int imageDataSize = bmpInfo.imageSize;
//    ImgInfo();
//    //read data of image
//    std::vector<uint8_t> imageData(imageDataSize);
//    inputFile.seekg(imageDataOffset);
//    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);
//
//    // get width and height
//    int width = bmpInfo.width;
//    int height = bmpInfo.height;
//
//    // close
//    inputFile.close();
//
//    // function
//    ConvertToGray(imageData, width, height);
//
//    //create file
//    std::ofstream outputFile("outputGray.bmp", std::ios::binary);
//    if (!outputFile.is_open()) {
//        std::cout << "unable to create this file" << std::endl;
//        return 1;
//    }
//
//    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
//    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
//
//    // write
//    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);
//
//    // close file
//    outputFile.close();
//
//    std::cout << "success" << std::endl;
//
//    return 0;
//}
