#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "IceKey.h"
#include "md5.h"

using uchar = unsigned char;

std::string getKeyForFilename(std::string fileNameWithoutExt) {
    auto filename = "Zhanjian" + fileNameWithoutExt;
    std::cout << filename << std::endl;
    return MD5(filename).md5();
}

std::vector<uchar> decrypt(std::vector<uchar> input, std::string key) {
    std::vector<uchar> output(input.size());
    auto ice = IceKey(0);
    ice.set((uchar*)key.c_str());
    for (int i = 0; i < input.size(); i += 8) {
        ice.decrypt(&input[i], &output[i]);
    }
    return output;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: mukar <filename.mukar>" << std::endl;
        return 1;
    }
    auto filename = std::string(argv[1]);
    auto fileNameWithoutExt =
        filename.substr(0, filename.size() - 6);  // .mukar
    std::cout << "Decrypting " << filename << std::endl;

    // read from bin file
    auto inFile = std::ifstream(filename, std::ios::binary);
    std::vector<uchar> inBuffer(std::istreambuf_iterator<char>(inFile), {});

    std::string key = getKeyForFilename(fileNameWithoutExt);
    auto output = decrypt(inBuffer, key);

    // save output
    auto ofile = std::ofstream(fileNameWithoutExt + ".png", std::ios::binary);
    ofile.write((const char*)output.data(), output.size());
    std::cout << "Decrypt complete!" << std::endl;
}
