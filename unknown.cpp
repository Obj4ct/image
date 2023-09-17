
#include "BMPFile.h"


void TailorImg(int32_t newHeight, int32_t newWidth, std::vector<uint8_t>& imageData,BMP& bmp,BMPInfo &bmpInfo) {
    std::cout << "Entering" << std::endl;

    int32_t startX = (bmpInfo.width - newWidth) / 4;
    int32_t startY = (bmpInfo.height - newHeight) / 4;

    // update
    bmpInfo.height = newHeight;
    bmpInfo.width = newWidth;
    bmpInfo.imageSize = newHeight * newWidth * 3;
    bmp.fileSize = bmp.dataOffset + bmpInfo.imageSize;

    // newSize
    std::vector<uint8_t> newImageData(bmpInfo.imageSize);

    // foreach size
    for (int32_t y = 0; y < newHeight; ++y) {
        for (int32_t x = 0; x < newWidth; ++x) {
            int32_t sourceIndex = ((startY + y) * bmpInfo.width + (startX + x)) * 3;
            int32_t destIndex = (y * newWidth + x) * 3;
            if (sourceIndex < imageData.size() && destIndex < imageData.size()) {
                //std::cout << "Copying pixel (" << x << ", " << y << ")" << std::endl;
                newImageData[destIndex] = imageData[sourceIndex];
                newImageData[destIndex + 1] = imageData[sourceIndex + 1];
                newImageData[destIndex + 2] = imageData[sourceIndex + 2];
            } else {
                std::cout << "Invalid indices: sourceIndex=" << sourceIndex << ", destIndex=" << destIndex << std::endl;
            }
        }
    }
    std::cout<<"old image data is :"<<imageData.size()<<std::endl;

    std::cout<<"new image data is :"<<newImageData.size()<<std::endl;
    // copy to imageData
    //std::copy(newImageData.begin(),newImageData.end(),imageData.begin());
    std::cout<<"after equal, image data is :"<<imageData.size()<<std::endl;
    std::cout << "Exiting" << std::endl;
}




int main() {
    BMP bmp;
    BMPInfo bmpInfo;
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

    //move to image data
    std::vector<uint8_t> imageData(imageDataSize);


    inputFile.seekg(imageDataOffset);
    //read
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close

    inputFile.close();





    int32_t height;
    int32_t width;
    std::cout<<"please input height and width"<<std::endl
             <<"height: "<<std::endl;
    std::cin>>height;
    std::cout<<"width: "<<std::endl;
    std::cin>>width;

    std::vector<uint8_t> newImageData(height*width*3,0);
    newImageData=imageData;


    // fuction
    TailorImg(height,width,imageData,bmp,bmpInfo);

















    // create file
    std::ofstream outputFile("outColorTailor1.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "unable to create this file!" << std::endl;
        return 1;
    }

    outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));

    outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));

    //write file
    //计算要写入文件的实际字节数，以确保只有有效的图像数据被写入文件，而不会包括任何未使用的内存。
    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());
    // close file
    outputFile.close();

    std::cout << "success！" << std::endl;

    return 0;

}