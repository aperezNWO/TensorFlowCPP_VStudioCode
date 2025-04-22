/*

TOOL CHAIN : C:\msys64\ucrt64\bin


g++ -std=c++11 -Wall -Wextra  ocr_dll_test.cpp -o ocr_dll_test.exe -m64


*/

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>

// Define function pointer types for the DLL functions
typedef        const char* (__cdecl *GetTesseractOcrOutputFunc)();
typedef static const char* (__cdecl *GetTesseractVersionFunc)();


int main() {
    // Load the DLL
    HINSTANCE hDll = LoadLibraryA("tesseract.dll");
    if (!hDll) {
        DWORD errorCode = GetLastError(); // Capture the error immediately
        std::cerr << "Failed to load TensorFlowApp64_CPP.dll. Error code: " << errorCode << std::endl;

        // Optional: Format the error message for more detail
        LPVOID errorMsg;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&errorMsg,
            0,
            NULL
        );
        std::cerr << "Error message: " << (LPSTR)errorMsg << std::endl;
        LocalFree(errorMsg);

        return 1;
    }
 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // GetTesseractOcrOutput
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    GetTesseractOcrOutputFunc getOcrOutput = (GetTesseractOcrOutputFunc)GetProcAddress(hDll, "GetTesseractOcrOutput");

    // Check if the functions were found
    if (!getOcrOutput) {
        std::cerr << "Failed to get function addresses. Error code: " << GetLastError() << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    // Test GetTensorFlowOcrOutput (uses hardcoded "Input.png")
    const char* ocrOutput = getOcrOutput();
    std::cout << "GetTesseractOcrOutputFunc result: " << ocrOutput << std::endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // GetTesseractVersion
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    GetTesseractVersionFunc getTesseractVersion = (GetTesseractVersionFunc)GetProcAddress(hDll, "GetTesseractVersion");

    // Check if the functions were found
    if (!getTesseractVersion) {
        std::cerr << "Failed to get function addresses. Error code: " << GetLastError() << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    // GetTesseractVersion
    const char* tesseractVersion = getTesseractVersion();
    std::cout << "GetTesseractVersion result: " << tesseractVersion << std::endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CLEANUP AND FINISING TASKS
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
 
    // Pause and wait for a keypress
    std::cout << "\nPress any key to exit..." << std::endl;
    _getch();

    
    FreeLibrary(hDll);
    return 0;
}
