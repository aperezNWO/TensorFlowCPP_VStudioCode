/*

g++ -std=c++11 -Wall -Wextra -I"include" TensorFlowApp.cpp -o TensorFlowApp.exe -L"lib" -l:tensorflow.lib

*/

/*
#include <iostream>
#include <tensorflow/c/c_api.h>

int main() {

  return 0;
}
*/

#include <iostream>
#include <windows.h>

// Define a function pointer type that matches the exported function signature
//typedef void (*CallTFVersionFunc)();
// Define a function pointer type that matches the exported function signature
typedef const char* (__cdecl *CallTFVersionFunc)();

int main() {
    // Load the DLL
    HINSTANCE hDLL = LoadLibraryA("TensorFlowApp64.dll"); // Replace "your_tensorflow_dll.dll" with the actual name of your DLL

    if (hDLL == nullptr) {
        std::cerr << "Error loading DLL: " << GetLastError() << std::endl;
        return 1;
    }

    // Get the address of the exported function
    //CallTFVersionFunc callTFVersion = (CallTFVersionFunc)GetProcAddress(hDLL, "GetTensorFlowVersion");
     // Get the address of the exported function
     CallTFVersionFunc callTFVersion = (CallTFVersionFunc)GetProcAddress(hDLL, "GetTensorFlowVersion");


    if (callTFVersion == nullptr) {
        std::cerr << "Error getting function address: " << GetLastError() << std::endl;
        FreeLibrary(hDLL);
        return 1;
    }

    // Call the exported function
    std::cout << "Calling function from DLL..." << std::endl;

    //callTFVersion();

    const char* version = callTFVersion();

    if (version != nullptr) {
        std::cout << "TensorFlow version from DLL: " << version << std::endl;
    } else {
        std::cerr << "Error: GetTensorFlowVersion returned a null pointer." << std::endl;
    }

    // Free the DLL
    FreeLibrary(hDLL);

    return 0;
}