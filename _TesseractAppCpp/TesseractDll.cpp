/*



// worked copying files "libwinpthread-1.dll"

g++ -shared -o TensorFlowApp64_CPP.dll TesseractDll.cpp -static-libgcc -static-libstdc++ -Wl,--out-implib=TensorFlowApp64_CPP.a

// worked

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


