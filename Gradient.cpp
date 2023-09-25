#include "MyLib/BMPFile.h"
//done
//梯度图  后一个像素与前一个相减
void Save(const std::vector<int> &data, const std::string &filename);

void Gradient(std::vector<uint8_t> &imageData) {
    std::vector<int> diffData;
    for (int i = 0; i < imageData.size() - 1; ++i) {
        int diff = imageData[i + 1] - imageData[i];
        diffData.push_back(diff);
    }
    Save(diffData, "Gradient.txt");
}

void Save(const std::vector<int> &data, const std::string &filename) {
    std::ofstream outputFile("../outImage/"+filename);
    if (!outputFile.is_open()) {
        std::cout << "Unable to create file" << std::endl;
        return;
    }

    for (int i = 0; i < data.size(); ++i) {
        outputFile << "梯度数据" << i << ": " << data[i] << std::endl;
    }
    std::cout << "Success" << std::endl;
    outputFile.close();
}

int main() {
    MyValue myValue = MYFunction::ReadBMPFile(FILENAME);
    std::vector<uint8_t> imageData = myValue.imageData;
    Gradient(imageData);
    return 0;
}
