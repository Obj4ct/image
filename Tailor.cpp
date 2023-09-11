#include "BMPFile.h"
//not yet
void TailorImg(int32_t cropX, int32_t cropY, int32_t cropHeight, int32_t cropWidth, std::vector<uint8_t> &imageData, std::vector<uint8_t> &newImageData, BMPInfo &newBmpInfo,BMP &newBmp) {
    newBmpInfo.height = cropHeight;
    newBmpInfo.width = cropWidth;
    newBmpInfo.imageSize = newBmpInfo.width * newBmpInfo.height * (newBmpInfo.bitsPerPixel / 8);
    uint32_t newBmpSize=sizeof(newBmp);
    uint32_t newBmpInfoSize=sizeof(newBmpInfo);
    newBmp.dataOffset=newBmpSize+newBmpInfoSize;
    newBmp.fileSize=newBmp.dataOffset+newBmpInfo.imageSize;
    for (int y = cropY; y < cropY + cropHeight; y++) {
        for (int x = cropX; x < cropX + cropWidth; x++) {
            int index = y * newBmpInfo.width + x;
            newImageData.push_back(imageData[index+3]);     // Red
            newImageData.push_back(imageData[index +3 + 1]); // Green
            newImageData.push_back(imageData[index + 3 + 2]); // Blue
        }
    }
}

int main() {
    BMP bmp;
    BMPInfo bmpInfo;
    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "Unable to open input file!" << std::endl;
        return 1;
    }

    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));
    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "File is not a valid BMP!" << std::endl;
        inputFile.close();
        return 1;
    }

    // Read header
    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));

    // Offset
    uint32_t imageDataOffset = bmp.dataOffset;
    uint32_t imageDataSize = bmpInfo.imageSize;
    std::vector<uint8_t> imageData(imageDataSize);
    // No need to change position
    inputFile.seekg(imageDataOffset);

    // Read image data
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);
    ReadBinTxt(FILENAME,"before");
    // Close input file
    inputFile.close();

    int32_t cropX = bmpInfo.width / 2;  // Begin X
    int32_t cropY = bmpInfo.height / 2; // Begin Y
    int32_t cropWidth = 300;  // Width
    int32_t cropHeight = 300; // Height


    std::vector<uint8_t> newImageData;
    //copy first and change newBmp、newBmpInfo later
    BMP newBmp;
    BMPInfo newBmpInfo;
    newBmp=bmp;
    newBmpInfo=bmpInfo;
    TailorImg(cropX, cropY, cropHeight, cropWidth, imageData, newImageData, newBmpInfo,newBmp);
    //newImageData=imageData;
    // Create output file
    std::ofstream outputFile("outColorTailor.bmp", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cout << "Unable to create output file!" << std::endl;
        return 1;
    }

    // Write BMP header and info
    outputFile.write(reinterpret_cast<const char*>(&newBmp), sizeof(newBmp));
    outputFile.write(reinterpret_cast<const char*>(&newBmpInfo), sizeof(newBmpInfo));
    outputFile.seekp(newBmp.dataOffset);
    // Write the actual image data
    outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());
    ReadBinTxt("outColorTailor.bmp","after");
    // Close output file
    outputFile.close();

    std::cout << "Success!" << std::endl;
    return 0;
}
