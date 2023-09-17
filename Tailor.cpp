#include "BMPFile.h"
#include "Debug.h"

//not yet
//图像信息
void WriteToBMPInfo(std::vector<uint8_t> &newImageData, int32_t cropHeight, int32_t cropWidth, BMPInfo &newBmpInfo,
                    BMP &newBmp) {
    newBmpInfo.height = cropHeight;//200
    newBmpInfo.width = cropWidth;//200
    newBmpInfo.imageSize = newBmpInfo.width * newBmpInfo.height * 3;//120000
    uint32_t newBmpSize = sizeof(newBmp);
    uint32_t newBmpInfoSize = sizeof(newBmpInfo);
    newBmp.dataOffset = newBmpSize + newBmpInfoSize;
    newBmp.fileSize = newBmp.dataOffset + newBmpInfo.imageSize;
    newImageData.resize(newBmpInfo.imageSize);
}


//内容处理
uint32_t TailorImg(int32_t cropX, int32_t cropY, int32_t cropHeight, int32_t cropWidth, std::vector<uint8_t> &imageData,
                   std::vector<uint8_t> &newImageData, BMPInfo &newBmpInfo, BMP &newBmp, uint32_t originWidth) {

    WriteToBMPInfo(newImageData, cropHeight, cropWidth, newBmpInfo, newBmp);
    for (int y = cropY; y < cropY + cropHeight; y++) {
        for (int x = cropX; x < cropX + cropWidth; x++) {
            uint32_t originIndex = (y * originWidth + x) * 3;
            int index = ((y - cropY) * cropWidth + (x - cropX)) * 3;
            newImageData[index] = imageData[originIndex];     // Red
            newImageData[index + 1] = imageData[originIndex + 1]; // Green
            newImageData[index + 2] = imageData[originIndex + 2]; // Blue
        }
    }
    return newBmpInfo.imageSize;

}

int main() {
    BMP bmp;
    BMPInfo bmpInfo;

    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "Unable to open input file!" << std::endl;
        return 1;
    }
    inputFile.read(reinterpret_cast<char *>(&bmp), sizeof(BMP));
    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "File is not a valid BMP!" << std::endl;
        inputFile.close();
        return 1;
    }

    // Read header
    inputFile.read(reinterpret_cast<char *>(&bmpInfo), sizeof(BMPInfo));

    // Offset
    uint32_t imageDataOffset = bmp.dataOffset;
    uint32_t imageDataSize = bmpInfo.imageSize;
    std::vector<uint8_t> imageData(imageDataSize);
    // No need to change position
    inputFile.seekg(imageDataOffset);

    // Read image data
    inputFile.read(reinterpret_cast<char *>(imageData.data()), imageDataSize);
    // Close input file
    inputFile.close();
    WriteBMPHexToFile(FILENAME,"iNhex.txt");


    TempImage(imageData, "mid.bmp", bmp, bmpInfo);
    int32_t cropX = 0;  // Begin X
    int32_t cropY = 0; // Begin Y
    int32_t cropWidth = 200;  // Width
    int32_t cropHeight = 200; // Height

    std::vector<uint8_t> newImageData;
    //copy first and change newBmp、newBmpInfo later
    //newImageData = imageData;
    BMP newBmp;
    BMPInfo newBmpInfo;
    newBmp = bmp;
    newBmpInfo = bmpInfo;
    newImageData = imageData;
    uint32_t newImageSize = TailorImg(cropX, cropY, cropHeight, cropWidth, imageData, newImageData, newBmpInfo, newBmp,
                                      bmpInfo.width);
    // Create output file
    std::ofstream outputFile("outColorTailor.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "Unable to create output file!" << std::endl;
        return 1;
    }
    // Write BMP header and info
    outputFile.write(reinterpret_cast<const char *>(&newBmp), sizeof(BMP));
    outputFile.write(reinterpret_cast<const char *>(&newBmpInfo), sizeof(BMPInfo));
    outputFile.seekp(newBmp.dataOffset);
    // Write the actual image data
    outputFile.write(reinterpret_cast<const char *>(newImageData.data()), newImageSize);

    // Close output file
    outputFile.close();
    std::cout << "Success!" << std::endl;
    WriteBMPHexToFile("outColorTailor.bmp","outhex.txt");


    return 0;
}
