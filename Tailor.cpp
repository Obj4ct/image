#include "BMPFile.h"
#include "Debug.h"

//something have done.
//图像信息
void WriteToBMPInfo(std::vector<uint8_t> &imageData, int32_t cropHeight, int32_t cropWidth, BMPInfo &newBmpInfo){
    newBmpInfo.height = cropHeight;
    newBmpInfo.width = cropWidth;
    newBmpInfo.imageSize = newBmpInfo.width * newBmpInfo.height * 3;//120000
    bmp.fileSize = bmp.dataOffset + newBmpInfo.imageSize;
    imageData.resize(newBmpInfo.imageSize);
}
//内容处理
void TailorImg(int32_t cropX, int32_t cropY, int32_t cropHeight, int32_t cropWidth, std::vector<uint8_t> &imageData,
               BMPInfo &newBmpInfo, uint32_t originWidth) {

    WriteToBMPInfo(imageData, cropHeight, cropWidth, newBmpInfo);
    for (int y = cropY; y < cropY + cropHeight; y++) {
        for (int x = cropX; x < cropX + cropWidth; x++) {
            uint32_t originIndex = (y * originWidth + x) * 3;
            int index = ((y - cropY) * cropWidth + (x - cropX)) * 3;
            imageData[index] = imageData[originIndex];     // Red
            imageData[index + 1] = imageData[originIndex + 1]; // Green
            imageData[index + 2] = imageData[originIndex + 2]; // Blue
        }
    }
}

int main() {
    std::vector<uint8_t> imageData =myFunction.ReadBMPFile(FILENAME);


    int32_t cropX = 0;  // Begin X
    int32_t cropY = 0; // Begin Y
    int32_t cropWidth = 0;  // Width
    int32_t cropHeight = 0; // Height
    std::cout << "输入你要裁剪的起始x坐标：" << std::endl;
    std::cin >> cropX;
    std::cout << "输入你要裁剪的起始y坐标：" << std::endl;
    std::cin >> cropY;
    std::cout << "输入你希望裁剪的高度：" << std::endl;
    std::cin >> cropHeight;
    std::cout << "输入你希望裁剪的宽度：" << std::endl;
    std::cin >> cropWidth;
    TailorImg(cropX, cropY, cropHeight, cropWidth, imageData,bmpInfo, bmpInfo.width);
    // Create output file
    //success write
    myFunction.WriteBMPFile("outColorTailor.bmp", imageData, bmp, bmpInfo);


    return 0;
}
