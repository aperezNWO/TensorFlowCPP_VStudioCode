/*
// static link sample

TOOL CHAIN : C:\msys64\ucrt64\bin

g++ -shared -static -static-libgcc -static-libstdc++ -o TensorFlowApp64_CPP.dll TesseractDll.cpp -lpthread



*/ 

#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

extern "C" __declspec(dllexport) const char* __cdecl GetTensorFlowOcrOutput() {
    static std::string result = "OCR OUTPUT";
    return result.c_str();
}


