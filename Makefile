# Compiler
CXX = g++

# C++ standard
CXXFLAGS += -std=c++23

# Output DLL name
TARGET = tesseract.dll

# Source file
SRC = tesseractApp.cpp

# Include paths
INCLUDE_PATHS = -I"include"

# Library paths
LIBRARY_PATHS = -L"lib"

# Libraries to link
LIBS = -ltesseract55 -lleptonica -lAlgorithm -lcurl -larchive -ltiff -lwebp -lsharpyuv \
       -lgif -lopenjp2 -lssl -lcrypto -lpng -ljpeg -lz -lbz2 -llzma -llz4 -lzstd \
       -lws2_32 -lbcrypt -lcrypt32

# Compilation and Linking Flags
CXXFLAGS += -m64 -static-libgcc -static-libstdc++ -DALGORITHM_EXPORTS $(INCLUDE_PATHS)
LDFLAGS += -shared -static $(LIBRARY_PATHS) $(LIBS) -Wl,--subsystem,windows

# Build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	del /F /Q $(TARGET)