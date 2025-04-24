///////////////////////////////////////////////////////////////////////////
// TESSERACT.DLL
///////////////////////////////////////////////////////////////////////////

#ifndef TESSERACTAPP_H // include guard
#define TESSERACTAPP_H
#endif

#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <random>
#include <regex>
#include <cctype>
#include <map>

//
using namespace std;

#pragma hdrstop
#pragma argsused
#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport) __stdcall __cdecl

using namespace std;

class TesseractApp
{
    public :
        //
        TesseractApp();
        ~TesseractApp();
        //
        const char*  GetTesseractOcrOutput(); 
        const char*  GetTesseractVersion();
        const char*  GetTesseractAppVersion(); 
        //
        int          ReadConfigFile();
     public :
        //
        map<string, string> configMap;

};