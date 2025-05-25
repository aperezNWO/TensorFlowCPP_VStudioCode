
//////////////////////////////////////////////////////
// CONFIGURATION
//////////////////////////////////////////////////////
/*

1) TOOL CHAIN : C:\msys64\ucrt64\bin (CAMBIAR PATH=)

// INSTALL

	2) vcpkg x64-mingw-static

	3) vcpkg integrate install


// COMMAND LINE COMPILE (static)

	4) g++ -shared -static -static-libgcc -static-libstdc++ -o tesseract.dll tesseractApp.cpp -I"C:/Users/pablo.perez/dev/cpp/_install/vcpkg_ucrt64/installed/x64-mingw-static/include"  -L"C:/Users/pablo.perez/dev/cpp/_install/vcpkg_ucrt64/installed/x64-mingw-static/lib"    -ltesseract55 -lleptonica -lcurl -larchive -ltiff -lwebp -lsharpyuv -lgif -lopenjp2 -lssl -lcrypto -lpng -ljpeg -lz -lbz2 -llzma -llz4 -lzstd -lws2_32 -lbcrypt -lcrypt32 -Wl,--subsystem,windows -m64 

// VISUAL STUDIO CODE INSTALL

	5) TERMINAL > RUN > BUILD TASK > (2) Build Tesseract DLL

	6) rename file to "tesseract.dll".

	7) Copy "tesseract.dll" file to __dist folder.

*/

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "include/tesseractApp.h"

//
TesseractApp::TesseractApp()
{
     //
     ReadConfigFile();
}
//
TesseractApp::~TesseractApp()
{
    //
}
//
const char* TesseractApp::GetTesseractOcrOutput()
{
   //
   const char* imagePath = "Input.png";
   static std::string output;
   //
   tesseract::TessBaseAPI ocr;

   //
   if (ocr.Init("tessdata", "eng")) {
       output = "Could not initialize tesseract.";
       return output.c_str();
   }

   //
   Pix* image = pixRead(imagePath);
   if (!image) {
       output = "Could not open image.";
       return output.c_str();
   }

   //
   ocr.SetImage(image);
   char* result = ocr.GetUTF8Text();

   //
   output = result ? result : "No output.";
   delete[] result;
   pixDestroy(&image);
   ocr.End();

   //
   return output.c_str();
}
//
const char* TesseractApp::GetTesseractOcrOutputPath(const char* imagePath)
{
   //
   static std::string output;
   //
   tesseract::TessBaseAPI ocr;

   //
   if (ocr.Init("tessdata", "eng")) {
       output = "Could not initialize tesseract.";
       return output.c_str();
   }

   //
   Pix* image = pixRead(imagePath);
   if (!image) {
       output = "Could not open image.";
       return output.c_str();
   }

   //
   ocr.SetImage(image);
   char* result = ocr.GetUTF8Text();

   //
   output = result ? result : "No output.";
   delete[] result;
   pixDestroy(&image);
   ocr.End();

   //
   return output.c_str();
}
//
const char*  TesseractApp::GetTesseractVersion()
{
    // Get the Tesseract version
    return tesseract::TessBaseAPI::Version();
}
//
const char*  TesseractApp::GetTesseractAppVersion()
{
    //
    return this->configMap["DLL_VERSION"].c_str();
} 
//
int          TesseractApp::ReadConfigFile()
{
    // Open the configuration file
    std::ifstream configFile("tesseract.ini");

    // Check if the file is opened successfully
    if (!configFile.is_open()) {
        std::cerr << "Error opening the configuration file." << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line = "";
    while (std::getline(configFile, line)) {
        // Skip empty lines or lines starting with '#' (comments)
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Split the line into key and value
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            // Trim leading and trailing whitespaces from key and value
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            // Insert key-value pair into the map
            this->configMap[key] = value;
        }
    }

    // Close the configuration file
    configFile.close();

    //
    return 0;
}    
////////////////////////////////////////////////////////////////
// DLL ENTRY POINTS
////////////////////////////////////////////////////////////////

DLL_EXPORT const char*  GetTesseractOcrOutput() 
{
    //
    std::unique_ptr<TesseractApp> uniquePtr = std::make_unique<TesseractApp>();
    //
    return uniquePtr->GetTesseractOcrOutput();
}

DLL_EXPORT const char*  GetTesseractOcrOutputPath(char* imagePath) 
{
    //
    std::unique_ptr<TesseractApp> uniquePtr = std::make_unique<TesseractApp>();
    //
    return uniquePtr->GetTesseractOcrOutputPath(imagePath);
}
                                                     
DLL_EXPORT const char* GetTesseractVersion() 
{
    //
    std::unique_ptr<TesseractApp> uniquePtr = std::make_unique<TesseractApp>();
    //
    return uniquePtr->GetTesseractVersion();
}


DLL_EXPORT const char* GetTesseractAppVersion()
{
    //
    std::unique_ptr<TesseractApp> uniquePtr = std::make_unique<TesseractApp>();
    //
    return uniquePtr->GetTesseractAppVersion();
}