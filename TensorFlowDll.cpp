/*


g++ -Iinclude -Llib TensorFlowDll.c -ltensorflow -shared -o TensorFlowApp64



*/

#include <stdio.h>
#include <tensorflow/c/c_api.h>

extern "C" __declspec(dllexport) const char* GetTensorFlowVersion() {
    return TF_Version();
}
