//
// Created by ztheng on 2023/9/5.
//done
// 色阶调整分输入色阶调整和输出色阶调整，其中输入色阶调整有3个调整点，即通常所说的黑场、白场及灰场调整
#include "BMPFile.h"

int ColorLevelChanel_R(std::vector<uint8_t>& newImageData,int32_t width,int32_t height,double_t brightness, double_t contrast) {

        for (int i = 0; i < newImageData.size(); i+=3)
        {
            uint8_t r = newImageData[i];

            // brightness
            r = std::min(255, std::max(0, static_cast<int>(r + brightness)));
            // contrast
            //128：midGray
            r = std::min(255, std::max(0, static_cast<int>((r - 128) * contrast + 128)));
            newImageData[i] = r;
        }
        return 0;

}
int ColorLevelChanel_G(std::vector<uint8_t>& newImageData,int32_t width,int32_t height,double_t brightness, double_t contrast) {

    for (int i = 0; i < newImageData.size(); i+=3)
    {
        uint8_t G = newImageData[i+1];

        // brightness
        G = std::min(255, std::max(0, static_cast<int>(G + brightness)));
        // contrast
        //128：midGray
        G = std::min(255, std::max(0, static_cast<int>((G - 128) * contrast + 128)));
        newImageData[i+1] = G;
    }
    return 0;

}

int ColorLevelChanel_B(std::vector<uint8_t>& newImageData,int32_t width,int32_t height,double_t brightness, double_t contrast) {

    for (int i = 0; i < newImageData.size(); i+=3)
    {
        uint8_t B = newImageData[i+2];

        // brightness
        B = std::min(255, std::max(0, static_cast<int>(B+ brightness)));
        // contrast
        //128：midGray
        B = std::min(255, std::max(0, static_cast<int>((B - 128) * contrast + 128)));
        newImageData[i+2] = B;
    }
    return 0;

}

int ColorLevelChanel_RGB(std::vector<uint8_t> &newImageData, int32_t width, int32_t height, double_t brightness, double_t contrast)
{
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3;
            uint8_t r = newImageData[index];
            uint8_t g = newImageData[index + 1];
            uint8_t b = newImageData[index + 2];
            //brightness
            r = std::min(255, std::max(0, static_cast<int>(r + brightness)));
            g = std::min(255, std::max(0, static_cast<int>(g + brightness)));
            b = std::min(255, std::max(0, static_cast<int>(b + brightness)));
            //contrast
            r = std::min(255, std::max(0, static_cast<int>((r - 128) * contrast + 128)));
            g = std::min(255, std::max(0, static_cast<int>((g - 128) * contrast + 128)));
            b = std::min(255, std::max(0, static_cast<int>((b - 128) * contrast + 128)));

            // update
            newImageData[index] = r;
            newImageData[index + 1] = g;
            newImageData[index + 2] = b;
        }
    }
    return 0;
}
int main() {
    BMP bmp;
    BMPInfo bmpInfo;
    std::ifstream inputFile(FILENAME, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "unable to open this file" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));

    if (bmp.fileType != 0x4D42) { // BM ASCII
        std::cout << "file is not invalid!" << std::endl;
        return 1;
    }


    inputFile.read(reinterpret_cast<char*>(&bmpInfo), sizeof(BMPInfo));

    //offset
    uint32_t imageDataOffset = bmp.dataOffset;

    //size
    uint32_t imageDataSize = bmpInfo.imageSize;
    //ImgInfo();
    //read data of image
    std::vector<uint8_t> imageData(imageDataSize);
    inputFile.seekg(imageDataOffset);
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageDataSize);

    // close
    inputFile.close();
    //CreateNewBmp();
    std::vector<uint8_t> newImageData;
    newImageData=imageData;
    double_t brightness,contrast;
    bool isLoop=true;
    while(isLoop)
    {
        int choice=1;
        std::cout<<"which chanel do you like to change:"<<std::endl
                 <<"1.r"<<std::endl
                 <<"2.g"<<std::endl
                 <<"3.b"<<std::endl
                 <<"4.RGB(All chanel)"<<std::endl
                 <<"5.exit"<<std::endl
                 <<"input:";
        std::cin>>choice;

        switch (choice) {
            case 1:
            {
                std::cout<<"How much r chanel do you want to increase or decrease?"<<std::endl
                << "please input brightness:"<<std::endl;
                std::cin >> brightness;
                std::cout<< "please input contrast:"<<std::endl;
                std::cin>>contrast;
                ColorLevelChanel_R(newImageData,bmpInfo.width,bmpInfo.height,brightness,contrast);
                std::ofstream outputFile("changeColorLever_R.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout<<std::endl;
                isLoop=true;
                break;
            }
            case 2:
            {
                std::cout<<"How much g chanel do you want to increase or decrease?"<<std::endl
                         << "please input brightness:"<<std::endl;
                std::cin >> brightness;
                std::cout<< "please input contrast:"<<std::endl;
                std::cin>>contrast;
                ColorLevelChanel_G(newImageData,bmpInfo.width,bmpInfo.height,brightness,contrast);
                std::ofstream outputFile("changeColorLever_G.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout<<std::endl;
                isLoop=true;
                break;
            }
            case 3:
            {
                std::cout<<"How much b chanel do you want to increase or decrease?"<<std::endl
                         << "please input brightness:"<<std::endl;
                std::cin >> brightness;
                std::cout<< "please input contrast:"<<std::endl;
                std::cin>>contrast;
                ColorLevelChanel_B(newImageData,bmpInfo.width,bmpInfo.height,brightness,contrast);
                std::ofstream outputFile("changeColorLever_B.bmp", std::ios::binary);
                if (!outputFile.is_open()) {
                    std::cout << "unable to create this file" << std::endl;
                    return 1;
                }
                outputFile.write(reinterpret_cast<const char*>(&bmp), sizeof(BMP));
                outputFile.write(reinterpret_cast<const char*>(&bmpInfo), sizeof(BMPInfo));
                outputFile.seekp(bmp.dataOffset);
                // write
                outputFile.write(reinterpret_cast<const char*>(newImageData.data()), newImageData.size());
                // close file
                outputFile.close();
                std::cout << "success" << std::endl;
                std::cout<<std::endl;
                isLoop=true;
                break;
            }
            case 4:
            {

                inputRGB:
                std::cout << "How much RGB chanel do you want to increase or decrease?" << std::endl
                          << "please input brightness:"<<std::endl;

                std::cin >> brightness;
                std::cout<< "please input contrast:"<<std::endl;
                std::cin>>contrast;
                // RGB function
                int result = ColorLevelChanel_RGB(newImageData, bmpInfo.width, bmpInfo.height,brightness,contrast);
                if (result == 1)
                {
                    goto inputRGB;
                }
                else
                {
                    std::ofstream outputFile("changeColorLever_RGB.bmp", std::ios::binary);
                    if (!outputFile.is_open())
                    {
                        std::cout << "unable to create this file" << std::endl;
                        return 1;
                    }
                    outputFile.write(reinterpret_cast<const char *>(&bmp), sizeof(BMP));

                    outputFile.write(reinterpret_cast<const char *>(&bmpInfo), sizeof(BMPInfo));
                    outputFile.seekp(bmp.dataOffset);

                    // write
                    outputFile.write(reinterpret_cast<const char *>(newImageData.data()), newImageData.size());

                    // close file
                    outputFile.close();

                    std::cout << "success" << std::endl;
                }
                isLoop = true;
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
