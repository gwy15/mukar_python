/* IceKey.i */
%module IceKey
%include "std_string.i"
%{
#define SWIG_PYTHON_STRICT_BYTE_CHAR
#include "IceKey.h"
#include <string>
std::string decrypt(std::string input, std::string key) {
    char *output = new char[input.size() + 1]{0};
    IceKey ice = IceKey(0);
    ice.set((unsigned char*)key.c_str());
    for (int i = 0; i < input.size(); i += 8) {
        ice.decrypt((unsigned char*)&input[i], (unsigned char*)&output[i]);
    }
    std::string result(output, input.size());
    delete[] output;
    return result;
}
%}

std::string decrypt(std::string input, std::string key);
