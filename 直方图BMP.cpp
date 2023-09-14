#include "BMPFile.h"

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

    std::ifstream inputFile(FILENAME, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cout << "Unable to open the image file" << std::endl;
        return 1;
    }


    std::vector<uint8_t> imageData;
    uint8_t byte;
    //read to imageData
    while (inputFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        imageData.push_back(byte);
    }

    inputFile.close();

    // 计算直方图
    std::vector<int> histogram = CalHistogram(imageData);


    Save(histogram, "data.txt");

    std::cout << "直方图数据成功生成!" << std::endl;

    return 0;
}
