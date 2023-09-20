////
//// Created by ztheng on 2023/9/5.
////
#include "MyLib/BMPFile.h"

//done

// RotateImage
void RotateImage(std::vector<uint8_t> &imageData, int32_t width, int32_t height, double_t angle) {
    double_t radians = angle * M_PI / 180.0;
    std::vector<uint8_t> rotatedImageData(width * height * 3);


    int32_t centerX =  width / 2;
    int32_t centerY =  height / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double_t rotatedX = std::cos(radians) * (x - centerX) -
                              std::sin(radians) * (y - centerY) + centerX;
            double_t rotatedY = std::sin(radians) * (x - centerX) +
                              std::cos(radians) * (y - centerY) + centerY;

            if (rotatedX >= 0 && rotatedX < width && rotatedY >= 0 && rotatedY < height)
            {
                int originalIndex = static_cast<int>(std::round(rotatedY)) * width * 3 +
                                    static_cast<int>(std::round(rotatedX)) * 3;
                int newIndex = y * width * 3 + x * 3;
                rotatedImageData[newIndex] = imageData[originalIndex];
                rotatedImageData[newIndex + 1] = imageData[originalIndex + 1];
                rotatedImageData[newIndex + 2] = imageData[originalIndex + 2];

            }
       }
    }


    imageData = rotatedImageData;
}

int main()
{
    std::vector<uint8_t> imageData =MYFunction::ReadBMPFile(FILENAME);

    // RotateImage Function
    double_t angle;
    std::cout<<"input rotate angle:"<<std::endl;
    std::cin>>angle;
    //normal
    RotateImage(imageData, bmpInfo.width, bmpInfo.height, angle);

    MYFunction::WriteBMPFile("outputRotate.bmp", imageData);


}

