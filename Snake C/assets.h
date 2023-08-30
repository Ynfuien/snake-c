#ifndef ASSETS_H_
#define ASSETS_H_

#include <Windows.h>

HMODULE GMH();

typedef struct Asset {
    DWORD size;
    char* content;
} Asset;
Asset* getAsset(int file, int type);


#endif