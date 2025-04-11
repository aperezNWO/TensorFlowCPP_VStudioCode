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
extern "C" __declspec(dllexport) const char* __cdecl GetTensorFlowVersion_CPP() {
    return TF_Version();
}

extern "C" __declspec(dllexport) const char* __cdecl GetTensorFlowOcrOutput() {
    //
    //std::string result = "OCR OUTPUT";
    const char * result        = "OCR OUTPUT";
    //
    return result;
}



