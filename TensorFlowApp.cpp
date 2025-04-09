/*

g++ -o TensorFlowAppCpp TensorFlowApp.cpp


*/

#include <iostream>
#include <windows.h>

typedef const char* (*GetTensorFlowVersionFunc)();

int main() {
    // Load the DLL
    HMODULE hModule = LoadLibrary("TensorFlowApp64.dll");

    if (hModule == NULL) {
        std::cerr << "Failed to load the DLL" << std::endl;
        return 1;
    }

    // Get the address of the GetTensorFlowVersion function
    GetTensorFlowVersionFunc GetTensorFlowVersion = (GetTensorFlowVersionFunc)GetProcAddress(hModule, "GetTensorFlowVersion");

    if (GetTensorFlowVersion == NULL) {
        std::cerr << "Failed to find GetTensorFlowVersion function" << std::endl;
        FreeLibrary(hModule);
        return 1;
    }

    // Call the function and print the TensorFlow version
    const char* version = GetTensorFlowVersion();
    std::cout << "TensorFlow Version: " << version << std::endl;

    // Free the DLL
    FreeLibrary(hModule);

    return 0;
}

