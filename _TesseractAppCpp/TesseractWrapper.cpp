/**

// dynamic app

g++ -o TensorFlowApp64_CPP.exe TesseractWrapper.cpp   -I"C:/Users/pablo.perez/dev/cpp/Tesseract/_src/vcpkg/installed/x64-mingw-dynamic/include"   -L"C:/Users/pablo.perez/dev/cpp/Tesseract/_src/vcpkg/installed/x64-mingw-dynamic/lib"    -ltesseract55 -lleptonica -lpng -ljpeg -lz    -Wl,--subsystem,windows -m64



*/



#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>
#include <iostream>


extern "C" __declspec(dllexport) const char* __cdecl GetTensorFlowOcrOutput() {
    const char* imagePath = "Input.png";
    static std::string output;

    tesseract::TessBaseAPI ocr;

    if (ocr.Init("tessdata", "eng")) {
        output = "Could not initialize tesseract.";
        return output.c_str();
    }

    Pix* image = pixRead(imagePath);
    if (!image) {
        output = "Could not open image.";
        return output.c_str();
    }

    ocr.SetImage(image);
    char* result = ocr.GetUTF8Text();

    output = result ? result : "No output.";
    delete[] result;
    pixDestroy(&image);
    ocr.End();

    return output.c_str();
}

int main(){
    GetTensorFlowOcrOutput();
}