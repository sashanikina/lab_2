#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

HANDLE fOpenHandle = nullptr;

int main() {
    setlocale(LC_ALL, "RU");
    void* mapAddr;
    string fileName, viewName, input;
    LPCSTR lpViewName;
    printf("Введите имя отображения файла: ");
    cin >> viewName;
    lpViewName = viewName.c_str();
    fOpenHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, lpViewName);

    if (fOpenHandle) {
        mapAddr = MapViewOfFile(fOpenHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);

        if (mapAddr) {
            printf("Записанная строка: %s\n", (char*)mapAddr);
            UnmapViewOfFile(mapAddr);
        }
        else printf("Ошибка открытия проецирования: %lu\n", GetLastError());
        CloseHandle(fOpenHandle);
    }
    else printf("Ошибка открытия проецирования: %lu\n", GetLastError());
    system("pause");
    return 0;
}
