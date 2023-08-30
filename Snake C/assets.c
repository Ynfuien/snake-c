#include "assets.h"

HMODULE GMH() {
    HMODULE hModule = NULL;
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)GMH, &hModule);
    return hModule;
}

Asset* getAsset(int file, int type) {
    Asset* asset = malloc(sizeof(Asset));

    HMODULE hM = GMH();
    HRSRC hRes = FindResource(hM, MAKEINTRESOURCE(file), MAKEINTRESOURCE(type));
    HGLOBAL hData = LoadResource(hM, hRes);
    asset->size = SizeofResource(hM, hRes);
    asset->content = malloc(sizeof(char) * asset->size);
    asset->content = (char*)LockResource(hData);

    return asset;
}