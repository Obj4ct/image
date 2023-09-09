//
// Created by ztheng on 2023/9/5.
//
#include "BMPFile.h"
void TailorImg(int32_t cropX,int32_t cropY,int32_t cropHeight,int32_t cropWidth,std::vector<uint8_t> &imageData,std::vector<uint8_t> &newImageData)
{
    newBmpInfo.height = cropHeight;
    newBmpInfo.width = cropWidth;
    newBmpInfo.imageSize = newBmpInfo.width * newBmpInfo.height * (newBmpInfo.bitsPerPixel / 8);
    newBmp.fileSize = bmp.dataOffset + newBmpInfo.imageSize;
    //把数据移入newImageData  指针到新图像数据的地方
    std::vector<BMP> bmpData;
    std::vector<BMPInfo> bmpInfoData;
    newImageData.insert(newImageData.end(), reinterpret_cast<uint8_t*>(&newBmpInfo), reinterpret_cast<uint8_t*>(&newBmpInfo) + sizeof(newBmpInfo));
//    bmpData.push_back(newBmp);
    bmpInfoData.push_back(newBmpInfo);
    newImageData.insert(newImageData.begin(), reinterpret_cast<uint8_t*>(&bmpData[0]), reinterpret_cast<uint8_t*>(&bmpData[0]) + sizeof(BMP));
    newImageData.insert(newImageData.end(), reinterpret_cast<uint8_t*>(&bmpInfoData[0]), reinterpret_cast<uint8_t*>(&bmpInfoData[0]) + sizeof(BMPInfo));
    newImageData.insert(newImageData.begin()+newBmp.dataOffset, imageData.begin()+bmp.dataOffset,imageData.end());
    for (int y = cropY; y < cropY + cropHeight; y++) {
        for (int x = cropX; x < cropX + cropWidth; x++) {
            int index = y * newBmpInfo.width + x;
            newImageData.push_back(imageData[index + 2]);
            newImageData.push_back(imageData[index + 1]);
            newImageData.push_back(imageData[index]);
        }
    }
}
int main() {

    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open it!" << std::endl;
        return 1;
    }
    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));
    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }


    // read header
    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));

    // offset
    uint32_t imageDataOffset = bmp.dataOffset;
    //set imageSize imageSize=width*height*字节
    uint32_t imageDataSize = bmpInfo.imageSize;

    std::vector<uint8_t> imageData(imageDataSize);
    //no need to change position
    inputFile.seekg(imageDataOffset);
    //read
    //problem here
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close
    inputFile.close();
    //CreateNewBmp();
    ReadBinTxt(FILENAME,"OriginBin");
    OutputToFile(imageData,"OriginPix");
   // std::vector<uint8_t> newImageData;
    int32_t cropX = bmpInfo.width/2; // begin x
    int32_t cropY = bmpInfo.height/2; // begin y
    int32_t cropWidth=0; // width
    int32_t cropHeight=0; // height
    std::cout << "please input height and width" << std::endl
              << "height: " << std::endl;
    std::cin >> cropHeight;
    std::cout << "width: " << std::endl;
    std::cin >> cropWidth;
    newBmpInfo.width=cropWidth;
    newBmpInfo.height=cropHeight;
    // fuction
    newBmpInfo.imageSize = newBmpInfo.width * newBmpInfo.height * (newBmpInfo.bitsPerPixel / 8);
    newBmp.fileSize = bmp.dataOffset + newBmpInfo.imageSize;
   // newImageData.resize(imageDataSize);
    std::vector<uint8_t> newImageData(newBmpInfo.imageSize);
    newImageData=imageData;
    imageData=newImageData;
    TailorImg(cropX,cropY,cropHeight,cropWidth,imageData,newImageData);
    // create file
    std::ofstream outputFile("outColorTailor.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }
    std::cout<<"error 1"<<std::endl;
    outputFile.write(reinterpret_cast<const char*>(&newBmp), sizeof(newBmp));
    std::cout<<"error 2"<<std::endl;
    outputFile.write(reinterpret_cast<const char*>(&newBmpInfo), sizeof(newBmpInfo));
    std::cout<<"error 1"<<std::endl;
    //write file
    //计算要写入文件的实际字节数，以确保只有有效的图像数据被写入文件，而不会包括任何未使用的内存。
    outputFile.seekp(bmp.dataOffset);


    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), imageDataSize);
    // close file
    std::cout<<"error 3"<<std::endl;
    ReadBinTxt("outColorTailor.bmp","AfterBin");
    OutputToFile(newImageData,"AfterPix");
    outputFile.close();
    std::cout << "success" << std::endl;

    return 0;

}

