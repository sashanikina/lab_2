#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

HANDLE fMapH = nullptr, fHandle = nullptr;

int main() {
    setlocale(LC_ALL, "RU");
    void* mapAddr;
    string fileName, viewName, input;
    LPCSTR lpFileName, lpViewName, lpInput;
    if (fHandle == nullptr) {
        printf("Введите полное имя файла (например c:\\folder\\file.txt): ");
        cin >> fileName;
        lpFileName = fileName.c_str();
        fHandle = CreateFile(lpFileName, GENERIC_ALL, NULL, nullptr, CREATE_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, nullptr);
    }
    else printf("Файл для проецирования открыт\n");

    if (fHandle) {
        printf("Введите имя отображения файла: ");
        cin >> viewName;
        lpViewName = viewName.c_str();
        fMapH = CreateFileMapping(fHandle, nullptr, PAGE_READWRITE, 0, 256, lpViewName);

        if (fMapH) {
            mapAddr = MapViewOfFile(fMapH, FILE_MAP_ALL_ACCESS, 0, 0, 0);

            if (mapAddr) {
                printf("Файл спроецирован\n");
                printf("Введите строку для записи: ");
                cin >> input;
                lpInput = input.c_str();
                CopyMemory(mapAddr, lpInput, sizeof(char) * input.length());
                printf("\nСтрока записана\n");
                UnmapViewOfFile(mapAddr);
            }
            else printf("Ошибка проецирования файла: %lu\n", GetLastError());
        }
        else printf("Ошибка проецирования файла: %lu\n", GetLastError());
    }
    else printf("Ошибка создания файла: %lu\n", GetLastError());
    system("pause");
    return 0;
}
