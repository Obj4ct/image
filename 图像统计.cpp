//
// Created by ZThenG on 2023/9/16/0016.
//

#include "BMPFile.h"
//平方和
uint32_t CalSquareSum(std::vector<uint8_t> imageData) {
    uint32_t sum=0;
    for (unsigned int pixVal : imageData) {
        sum+=pixVal*pixVal;
    }
    return sum;
}
//方差
uint32_t CalVariance(std::vector<uint8_t> imageData) {
    uint32_t aver, tempSum=0,sum=0,variance;
    for (int i = 0; i < imageData.size(); i++) {
        sum += imageData[i];
    }
    aver = sum / imageData.size();
    for (int i = 0; i < imageData.size(); ++i) {
        tempSum += ((imageData[i] - aver)*(imageData[i]-aver));

    }
    variance=tempSum/imageData.size();
    return variance;
}
//标准差
double_t CalStandard(std::vector<uint8_t>imageData)
{
    uint32_t aver, tempSum=0,sum=0,variance;
    for (int i = 0; i < imageData.size(); i++) {
        sum += imageData[i];
    }
    aver = sum / imageData.size();
    for (int i = 0; i < imageData.size(); ++i) {
        tempSum += ((imageData[i] - aver)*(imageData[i]-aver));

    }
    variance=tempSum/imageData.size();


    double_t standard=std::sqrt(variance);
    return standard;
}
//直方图数据
std::vector<int> CalHistogram(const std::vector<uint8_t>& imageData) {
    std::vector<int> histogram(255);

    // 遍历图像数据
    for (size_t i = 0; i < imageData.size(); i++) {
        uint8_t pixel = imageData[i];
        histogram[pixel]++;
    }

    return histogram;
}

void Save(const std::vector<int>& histogram, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cout << "Unable to create histogram file" << std::endl;
        return;
    }

    for (int i = 0; i < histogram.size(); ++i) {
        outputFile << "数据" << i << ": " << histogram[i] << std::endl;
    }

    outputFile.close();
}
int main() {
    BMP bmp;
    BMPInfo bmpInfo;
    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open this file" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char *>(&bmp), sizeof(BMP));

    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char *>(&bmpInfo), sizeof(BMPInfo));

    //offset
    uint32_t imageDataOffset = bmp.dataOffset;

    //size
    uint32_t imageDataSize = bmpInfo.imageSize;
    //ImgInfo();
    //read data of image
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    inputFile.read(reinterpret_cast<char *>(imageData.data()), imageDataSize);

    // get width and height
//    int width = bmpInfo.width;
//    int height = bmpInfo.height;

    // close
    inputFile.close();
    bool isLoop=true;
    while(isLoop)
    {
        int choice=1;
        std::cout<<"请输入你要获取的图像信息::"<<std::endl
                 <<"1.平方和"<<std::endl
                 <<"2.方差"<<std::endl
                 <<"3.标准差"<<std::endl
                 <<"4.直方图数据"<<std::endl
                 <<"5.exit"<<std::endl
                 <<"input:";
        std::cin>>choice;

        switch (choice) {
            case 1:
            {
                //OutputToFile(imageData,"beforeBrightness");
                uint32_t sum=CalSquareSum(imageData);
                //OutputToFile(imageData,"afterBrightness");
                std::cout<<"平方和是: "<<sum<<std::endl;
                isLoop=true;
                break;
            }
            case 2:
            {
                uint32_t variance = CalVariance(imageData);
                std::cout << "方差是: " << variance << std::endl;
                isLoop=true;
                break;
            }
            case 3:
            {
                double_t standard = CalStandard(imageData);
                std::cout << "标准差: " << standard << std::endl;
                isLoop=true;
                break;
            }
            case 4:
            {
                // 计算直方图
                std::vector<int> histogram = CalHistogram(imageData);
                Save(histogram, "data.txt");
                std::cout << "直方图数据成功生成!文件名为data.txt" << std::endl;
                isLoop=true;
                break;

            }
            case 5:
                exit(0);

            default:
            {
                std::cout<<"input error! try again!"<<std::endl;
            }
        }
    }

}

