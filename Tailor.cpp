////
//// Created by ztheng on 2023/9/5.
////
//#include "BMPFile.h"
//
//
//void TailorImg(uint32_t height,uint32_t width) {
//    bmpInfo.height=height;
//    bmpInfo.width=width;
//    bmpInfo.imageSize=height*width*3;
//
//    bmp.fileSize = sizeof(BMP) + sizeof(BMPInfo) + bmpInfo.imageSize;
//
//}
//
//
//int main() {
//
//    std::ifstream inputFile(FILENAME, std::ios::binary);
//    if (!inputFile.is_open()) {
//        std::cout << "unable to open it!" << std::endl;
//        return 1;
//    }
//
//    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));
//
//    if (bmp.fileType != 0x4D42) { // BM ASCII
//        std::cout << "file is not invalid!" << std::endl;
//        return 1;
//    }
//
//
//    // read header
//    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));
//
//    // offset
//    int imageDataOffset = bmp.dataOffset;
//    //set imageSize imageSize=width*height*字节
//    int imageDataSize = bmpInfo.imageSize;
//
//    ImgInfo();
//
//    //move to image data
//    std::vector<uint8_t> imageData(imageDataSize);
//    inputFile.seekg(imageDataOffset);
//    //read
//    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);
//
//    // close
//    int height;
//    int width;
//    inputFile.close();
//    std::cout<<"please input height and width"<<std::endl
//    <<"height: "<<std::endl;
//    std::cin>>height;
//    std::cout<<"width: "<<std::endl;
//    std::cin>>width;
//
//    // fuction
//    TailorImg(height,width);
//    ImgInfo();
//    // create file
//    std::ofstream outputFile("outColorTailor.bmp", std::ios::binary);
//    if (!outputFile.is_open()) {
//        std::cout << "unable to create this file!" << std::endl;
//        return 1;
//    }
//
//    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
//    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
//    //write file
//    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageDataSize);
//
//    // close file
//    outputFile.close();
//
//    std::cout << "success！" << std::endl;
//
//    return 0;
//
//}
//
//
//
