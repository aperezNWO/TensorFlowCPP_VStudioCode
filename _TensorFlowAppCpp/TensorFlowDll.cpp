/*

g++ -shared -std=c++11 -Wall -Wextra -I"include" TensorFlowDll.cpp -o TensorFlowApp64_CPP.dll -L"lib" -l:tensorflow.lib

*/ 

#include <string>
#include <cstring> // For strlen, strcpy, etc.
#include <cstdlib> // For malloc, free
#include <tensorflow/c/c_api.h>
#include <stdio.h>

// Function to get the TensorFlow version with an additional string appended
extern "C" __declspec(dllexport) const char* __cdecl GetTensorFlowVersion() {
    // Get the TensorFlow version
    const char* tf_version = TF_Version();
    
    // Define the additional string to append
    const char* suffix = "";
    
    // Calculate the total length of the concatenated string (+1 for null terminator)
    size_t total_length = std::strlen(tf_version) + std::strlen(suffix) + 1;
    
    // Allocate memory for the concatenated string
    char* result = static_cast<char*>(std::malloc(total_length));
    if (!result) {
        return nullptr; // Return nullptr if allocation fails
    }
    
    // Copy the TensorFlow version into the result buffer
    std::strcpy(result, tf_version);
    
    // Append the suffix to the result buffer
    std::strcat(result, suffix);
    
    // Return the concatenated string
    return result;
}


