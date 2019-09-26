#include "IceKey.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "md5.h"

std::string getKeyForFilename(std::string fileNameWithoutExt) {
    auto filename = "Zhanjian" + fileNameWithoutExt;
    std::cout << filename << std::endl;
    return MD5(filename).md5();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: mukar <filename.mukar>" << std::endl;
        return 1;
    }
    auto filename = std::string(argv[1]);
    auto fileNameWithoutExt = filename.substr(0, filename.size() - 6); // .mukar
    std::cout << "Decrypting " << filename << std::endl;
    
    // read from bin file
    auto inFile = std::ifstream(filename, std::ios::binary);
    std::vector<unsigned char> inBuffer(std::istreambuf_iterator<char>(inFile), {});
    // init output buffer
    auto length = inBuffer.size();
    std::vector<unsigned char> outBuffer(length);

    
    // init ice
    auto ice = IceKey(0);
    // calc md5 key
    std::string key = getKeyForFilename(fileNameWithoutExt);
    ice.set((unsigned char*)key.c_str());
    // ice.set((const unsigned char*)"ab5efcc5ecd228483770d302284828e9");
    for (int i=0; i<length; i += 8) {
        ice.decrypt(&inBuffer[i], &outBuffer[i]);
    }
    
    // save output
    auto ofile = std::ofstream(fileNameWithoutExt + ".png", std::ios::binary);
    ofile.write((const char*)outBuffer.data(), length);
    std::cout << "Decrypt complete!" << std::endl;
}
