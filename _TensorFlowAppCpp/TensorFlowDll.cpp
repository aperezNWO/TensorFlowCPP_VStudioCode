/*

x86_64-w64-mingw32-g++ -shared -static-libgcc -static-libstdc++ -std=c++14 -Wall -Wextra -g -I"include" TensorFlowDll.cpp -o TensorFlowApp64_CPP.dll -L"lib" -l:tensorflow.lib

*/ 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tesseract/capi.h> // Tesseract C API header
#include <tensorflow/c/c_api.h> // TensorFlow C API header


// Function to get the TensorFlow version
extern "C" __declspec(dllexport) const char* __cdecl GetTensorFlowVersion() {
    return TF_Version();
}

// Function to allocate memory and return a concatenated string
extern "C" __declspec(dllexport) const char* __cdecl GetTensorFlowOcrOutput() {
    const char* tf_version = TF_Version();
    const char* suffix = " (Custom Build)";

    size_t total_length = std::strlen(tf_version) + std::strlen(suffix) + 1;
    char* result = static_cast<char*>(std::malloc(total_length));
    if (!result) {
        return nullptr; // Return nullptr if allocation fails
    }

    std::strcpy(result, tf_version);
    std::strcat(result, suffix);

    return result;
}

