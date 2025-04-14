/**

hi. ¿Can you please tell me how to Wrap Tesseract directly in C++ under windows x64 operating systen?

cd C:\Users\pablo.perez\dev\cpp\Tesseract
git clone https://github.com/madler/zlib.git
cd zlib
mkdir build && cd build
cmake -A x64 .. -G "Visual Studio 17 2022" -DZLIB_BUILD_EXAMPLES=OFF
cmake --build . --config Release --target install

set CMAKE_PREFIX_PATH=C:\Program Files\zlib
cd C:\Users\pablo.perez\dev\cpp\Tesseract\_src\vcpkg
.\vcpkg install tesseract:x64-windows



g++ -shared -static -static-libgcc -static-libstdc++ -o TesseractWrapper.dll TesseractWrapper.cpp -lpthread

// dynamic
vcpkg install tesseract:x64-mingw-dynamic

g++ -shared -o TesseractWrapper.dll TesseractWrapper.cpp   -I"C:\Users\pablo.perez\dev\cpp\Tesseract\_src\vcpkg\installed\x64-windows\include"  -L"C:\Users\pablo.perez\dev\cpp\Tesseract\_src\vcpkg\installed\x64-windows\lib"   -ltesseract -lleptonica  -Wl,--subsystem,windows  -m64

g++ -shared -o TensorFlowApp64_CPP.dll TesseractWrapper.cpp   -I"C:/Users/pablo.perez/dev/cpp/Tesseract/_src/vcpkg/installed/x64-mingw-dynamic/include"   -L"C:/Users/pablo.perez/dev/cpp/Tesseract/_src/vcpkg/installed/x64-mingw-dynamic/lib"    -ltesseract55 -lleptonica -lpng -ljpeg -lz    -Wl,--subsystem,windows -m64


// static
vcpkg install tesseract:x64-mingw-static

setx PATH "%PATH%;C:\Users\pablo.perez\dev\cpp\Tesseract\_src\vcpkg\installed\x64-mingw-static\lib" /M

g++ -shared -o TensorFlowApp64_CPP.dll TesseractWrapper.cpp   -I"C:/Users/pablo.perez/dev/cpp/Tesseract/_src/vcpkg/installed/x64-mingw-static/include"   -L"C:/Users/pablo.perez/dev/cpp/Tesseract/_src/vcpkg/installed/x64-mingw-static/lib"   -static -ltesseract55 -lleptonica -lpng -ljpeg -lz  -static-libgcc -static-libstdc++   -Wl,--subsystem,windows -m64


// dynamic app

g++ -o TensorFlowApp64_CPP.exe TesseractWrapperEXE.cpp   -I"C:/Users/pablo.perez/dev/cpp/Tesseract/_src/vcpkg/installed/x64-mingw-dynamic/include"  -L"C:/Users/pablo.perez/dev/cpp/Tesseract/_src/vcpkg/installed/x64-mingw-dynamic/lib" -ltesseract55 -lleptonica 

-Wl,--subsystem,windows -m64  

 
 

-lpng -ljpeg -lz    



*/



#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>
#include <iostream>


//extern "C" __declspec(dllexport) const char* __cdecl 

const char* GetTensorFlowOcrOutput() {
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

    printf("Program init...");
    
    printf("%s",GetTensorFlowOcrOutput());

    return 0;
}