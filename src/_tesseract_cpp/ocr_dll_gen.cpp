
//////////////////////////////////////////////////////
// CONFIGURATION
//////////////////////////////////////////////////////
/*

1) TOOL CHAIN : C:\msys64\ucrt64\bin
2) vcpkg x64-mingw-static
3) vcpkg integrate install
4) g++ -shared -static -static-libgcc -static-libstdc++ -o tesseract.dll ocr_dll_gen.cpp -I"C:/Users/pablo.perez/dev/cpp/_install/vcpkg/installed/x64-mingw-static/include"  -L"C:/Users/pablo.perez/dev/cpp/_install/vcpkg/installed/x64-mingw-static/lib"    -ltesseract55 -lleptonica -lcurl -larchive -ltiff -lwebp -lsharpyuv -lgif -lopenjp2 -lssl -lcrypto -lpng -ljpeg -lz -lbz2 -llzma -llz4 -lzstd -lws2_32 -lbcrypt -lcrypt32 -Wl,--subsystem,windows -m64 
5) TERMINAL > RUN > BUILD TASK > (2) Build Tesseract DLL
6) Copy *.dll file to __dist folder.

*/

#include <string>
#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#define DLL_EXPORT extern "C" __declspec(dllexport) __stdcall

using namespace std;
                                                     
DLL_EXPORT const char* __cdecl GetTesseractOcrOutput() 
{

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

                                                     
DLL_EXPORT const char* __cdecl GetTesseractVersion() 
{
    // Get the Tesseract version
    return tesseract::TessBaseAPI::Version();
}

