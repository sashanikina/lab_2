#include <iostream>
#include <string>
#include <windows.h>
#include <bitset>

using namespace std;

void SysInfo();

void MemStat();

void VirtQ();

void VirtAll();

void VirtAll2();

void WriteInfo();

void VirtP();

void VirtF();

int main() {
    string tmp;
    setlocale(LC_ALL, "RU");
    int answer;
    do {
        system("cls");
        printf("Введите 1 для получения информации о вычислительной системе\n");
        printf("Введите 2 для определения статуса виртуальной памяти\n");
        printf("Введите 3 для определения состояния конкретного участка памяти\n");
        printf("Введите 4 для резервирования региона\n");
        printf("Введите 5 для резервирования региона и передачи ему физической памяти\n");
        printf("Введите 6 для записи данных в ячейки памяти\n");
        printf("Введите 7 для установки защиты доступа для заданного региона памяти и ее проверки\n");
        printf("Введите 8 для возврата физической памяти и освобождения региона адресного пространства заданного региона памяти\n");
        printf("Введите 0 для выхода\n");
        cin >> tmp;
        answer = stoi(tmp);
        switch (answer) {
            case 1:
                SysInfo();
                break;
            case 2:
                MemStat();
                break;
            case 3:
                VirtQ();
                break;
            case 4:
                VirtAll();
                break;
            case 5:
                VirtAll2();
                break;
            case 6:
                WriteInfo();
                break;
            case 7:
                VirtP();
                break;
            case 8:
                VirtF();
                break;
            default:
                break;
        }
    } while (answer != 0);
    return 0;
}

void SysInfo() {
    SYSTEM_INFO siSysInfo;

    GetSystemInfo(&siSysInfo);
    printf("Архитектура процессора:  ");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) printf("x64 (AMD или Intel)\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) printf("ARM\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) printf("ARM64\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) printf("Intel Itanium-based\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) printf("x86\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_UNKNOWN) printf("Неизвестная архитектура\n");

    printf("Размер страницы %i\n", (int) siSysInfo.dwPageSize);
    printf("Указатель на наименьший адрес памяти: 0x%p\n", (void *) siSysInfo.lpMinimumApplicationAddress);
    printf("Указатель на наибольший адрес памяти: 0x%p\n", (void *) siSysInfo.lpMaximumApplicationAddress);
    printf("Маска, представляющая набор процессоров, настроенных в системе: %s\n",
           bitset<sizeof(siSysInfo.dwActiveProcessorMask) * CHAR_BIT>(
                   siSysInfo.dwActiveProcessorMask).to_string().c_str());
    printf("Количество логических процессоров в текущей группе: %i\n", (int) siSysInfo.dwNumberOfProcessors);
    printf("Гранулярность блоков адресов: %i\n", (int) siSysInfo.dwAllocationGranularity);
    printf("Уровень процессора: %i\n", (int) siSysInfo.wProcessorLevel);
    printf("Версия процессора: %i\n", (int) siSysInfo.wProcessorRevision);

    system("pause");
}

void MemStat() {
    MEMORYSTATUS stat;

    GlobalMemoryStatus(&stat);

    printf("Размер структуры данных в байтах: %ld\n", stat.dwLength);
    printf("процент используемой физической памяти: %ld\n", stat.dwMemoryLoad);
    printf("Объем фактической физической памяти в %sбайтах: %ld \n", "K", stat.dwTotalPhys / 1024);
    printf("Объем доступной физической памяти в %sбайтах: %ld\n", "K", stat.dwAvailPhys / 1024);
    printf("Текущий размер зафиксированного ограничения памяти в %sбайтах: %ld\n", "K", stat.dwTotalPageFile / 1024);
    printf("Максимальный объем памяти, который может зафиксировать текущий процесс в %sбайтах: %ld\n", "K",
           stat.dwAvailPageFile / 1024);
    printf("Размер части виртуального адресного пространства вызывающего процесса в %sбайтах: %ld\n", "K",
           stat.dwTotalVirtual / 1024);
    printf("Объем доступного объема памяти виртуального адресного пространства вызывающего процесса в %sбайтах: %ld\n",
           "K", stat.dwAvailVirtual / 1024);

    system("pause");
}

void protectCheck(DWORD level) {

    if (level == 0)
        printf("Отсутствие доступа");
    if (level == PAGE_EXECUTE)
        printf("Включено выполнение доступа к зафиксированной области страниц \n\t(PAGE_EXECUTE)\n");
    if (level == PAGE_EXECUTE_READ)
        printf("Включен доступ только для выполнения или чтения к зафиксированной области страниц. "
               "Попытка записи в зафиксированную область приводит к нарушению доступа \n\t(PAGE_EXECUTE_READ)\n");
    if (level == PAGE_EXECUTE_READWRITE)
        printf("Включен доступ только для выполнения, чтения или чтения/записи к зафиксированной области страниц \n\t(PAGE_EXECUTE_READWRITE)\n");
    if (level == PAGE_EXECUTE_WRITECOPY)
        printf("Включает доступ только для выполнения, чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов \n\t(PAGE_EXECUTE_WRITECOPY)\n");
    if (level == PAGE_NOACCESS)
        printf("Отключен весь доступ к зафиксированной области страниц \n\t(PAGE_NOACCESS)\n");
    if (level == PAGE_READONLY)
        printf("Включен доступ только для чтения к зафиксированной области страниц \n\t(PAGE_READONLY)\n");
    if (level == PAGE_READWRITE)
        printf("Включает доступ только для чтения или чтения/записи к зафиксированной области страниц \n\t(PAGE_READWRITE)\n");
    if (level == PAGE_WRITECOPY)
        printf("Включает доступ только для чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов \n\t(PAGE_WRITECOPY)\n");
    if (level == PAGE_TARGETS_INVALID)
        printf("Все местоположения на страницах установлены в качестве недопустимых целевых объектов для CFG \n\t(PAGE_TARGETS_INVALID)\n");
    if (level == PAGE_TARGETS_NO_UPDATE)
        printf("Для страниц в регионе не будет обновляться информация о CFG \n\t(PAGE_TARGETS_NO_UPDATE)\n");


    if ((level & PAGE_GUARD) != 0) {
        printf("Страницы в области защищены \n(PAGE_GUARD)\n");
    }
    if ((level & PAGE_NOCACHE) != 0)
        printf("Страницы не кэшируются \n(PAGE_NOCACHE)\n");
    if ((level & PAGE_WRITECOMBINE) != 0) {
        printf("Страницы в установлены в режим комбинированной записи \n(PAGE_WRITECOMBINE)\n");
    }

}

void VirtQ() {
    LPCVOID lpAddress;
    MEMORY_BASIC_INFORMATION lpBuffer;
    int address;

    printf("Введите необходимый адрес: 0x");
    cin >> hex >> address;
    lpAddress = (LPCVOID) address;
    VirtualQuery(lpAddress, &lpBuffer, sizeof(lpBuffer));

    printf("Указатель на базовый адрес области страниц: %p\n", (void *) lpBuffer.BaseAddress);
    printf("Указатель на базовый адрес диапазона страниц, выделенных пользователем: %p\n",
           (void *) lpBuffer.AllocationBase);

    printf("Параметр защиты памяти при первоначальном выделении области: ");
    protectCheck(lpBuffer.AllocationProtect);


    if ((lpBuffer.AllocationProtect & PAGE_GUARD) != 0) {
        printf("Страницы в области защищены \n(PAGE_GUARD)");
    }
    if ((lpBuffer.AllocationProtect & PAGE_NOCACHE) != 0)
        printf("Страницы не кэшируются \n(PAGE_NOCACHE)");
    if ((lpBuffer.AllocationProtect & PAGE_WRITECOMBINE) != 0) {
        printf("Страницы в установлены в режим комбинированной записи \n(PAGE_WRITECOMBINE)");
    }


    printf("\nРазмер области, начинающийся с базового адреса, в которой все страницы имеют одинаковые атрибуты:  %u байт\n",
           lpBuffer.RegionSize);
    printf("Защита доступа к страницам в области: %lx\n", lpBuffer.Protect);

    printf("Состояние страниц в области: ");
    if (lpBuffer.State == MEM_COMMIT)
        printf("зафиксированная страница\n");
    if (lpBuffer.State == MEM_FREE)
        printf("свободные страницы, недоступные для вызывающего процесса и доступные для выделения\n");
    if (lpBuffer.State == MEM_RESERVE) {
        printf("зарезервированные страницы, на которых зарезервирован диапазон виртуального адресного "
               "пространства процесса без выделения какого - либо физического хранилища\n");
    }

    printf("Тип страниц в области: ");
    if (lpBuffer.Type == MEM_IMAGE)
        printf("страницы памяти в пределах области отображаются в виде раздела изображения\n");
    if (lpBuffer.Type == MEM_MAPPED)
        printf("страницы памяти в пределах области сопоставляются с представлением раздела\n");
    if (lpBuffer.Type == MEM_PRIVATE)
        printf("страницы памяти в пределах области являются частными\n");
    system("pause");

}

void VirtAll() {
    LPVOID Addr;
    LPVOID Addr2 = nullptr;
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);

    Addr = VirtualAlloc(nullptr, siSysInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (Addr != nullptr) {
        printf("Автоматическое резервирование успешно! Базовый адрес области: 0х%p \n", Addr);
        printf("Резервирование в режиме ввода адреса начала области...\n");
        printf("Введите адрес: 0x");
        cin >> hex >> Addr2;

        Addr = VirtualAlloc(Addr2, siSysInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);

        if (Addr != nullptr)
            printf("Резервирование успешно! Базовый адрес области: 0x%p \n", Addr);
        else printf("Ошибка резервирования.");
    } else printf("Ошибка резервирования.");

    system("pause");
}

void VirtAll2() {
    LPVOID Addr;
    LPVOID Addr2 = nullptr;
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    Addr = VirtualAlloc(nullptr, siSysInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (Addr != nullptr) {
        printf("Автоматическое резервирование успешно! Базовый адрес области: 0х%p \n", (void *) Addr);
        printf("Резервирование в режиме ввода адреса начала области...\n");
        printf("Введите адрес: 0x");
        cin >> hex >> Addr2;

        Addr = VirtualAlloc(Addr2, siSysInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

        if (Addr != nullptr)
            printf("Резервирование и передача прошли успешно! Базовый адрес региона 0x%p \n", (void *) Addr);
        else printf("Резервирование и передача не прошли\n");
    } else printf("Резервирование и передача не прошли\n");

    system("pause");
}

void WriteInfo() {
    LPVOID addr;
    char *strAddr;
    SIZE_T res;
    string str;
    MEMORY_BASIC_INFORMATION lpBuffer;
    printf("Введите адрес участка памяти: 0х");
    cin >> hex >> addr;
    cin >> dec;
    printf("Введите строку данных: ");
    cin >> str;
    res = VirtualQuery(addr, &lpBuffer, sizeof(lpBuffer));
    if (res) {
        if (!((lpBuffer.Protect &
               (PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_READWRITE | PAGE_WRITECOPY)) &&
              (lpBuffer.State == MEM_COMMIT))) {
            printf("Ошибка: память не выделена\n");
        }
        if (!(lpBuffer.RegionSize >= str.length() * sizeof(char))) {
            printf("Слишком длинная строка\n");
        }
        strAddr = (char *) addr;
        CopyMemory(strAddr, str.c_str(), str.length() * sizeof(char));
        printf("Начальный адрес участка памяти: 0x%p\n", (void *) strAddr);
        printf("Записанная информация: ");
        for (int i = 0; i < str.length(); ++i)
            printf("%c", strAddr[i]);
        printf("\n");
    } else printf("Ошибка проверки памяти: %i\n", GetLastError());
    system("pause");
}

void pro_menu() {
    printf("Введите 1 для включения доступа к зафиксированной области страниц \n\t(PAGE_EXECUTE)\n");
    printf("Введите 2 для включения доступа только для выполнения или чтения к зафиксированной области страниц \n\t(PAGE_EXECUTE_READ)\n");
    printf("Введите 3 для включения доступа только для выполнения, чтения или чтения/записи к зафиксированной области страниц \n\t(PAGE_EXECUTE_READWRITE)\n");
    printf("Введите 4 для включения доступа только для выполнения, чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов \n\t(PAGE_EXECUTE_WRITECOPY)\n");
    printf("Введите 5 для отключения всего доступа к зафиксированной области страниц \n\t(PAGE_NOACCESS)\n");
    printf("Введите 6 для включения доступа только для чтения к зафиксированной области страниц \n\t(PAGE_READONLY)\n");
    printf("Введите 7 для включения доступа только для чтения или чтения/записи к зафиксированной области страниц \n\t(PAGE_READWRITE)\n");
    printf("Введите 8 для включения доступа только для чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов \n\t(PAGE_WRITECOPY)\n");
    printf("Введите 9 для установки всех местоположений на страницах в качестве недопустимых целевых объектов для CFG \n\t(PAGE_TARGETS_INVALID)\n");
    printf("Введите 10, чтобы для страниц в области не обновлялась информация о CFG \n\t(PAGE_TARGETS_NO_UPDATE)\n");
    system("pause");
}

DWORD protectChoose(int x) {
    DWORD level;
    if (x == 1)
        level = PAGE_EXECUTE;
    if (x == 2)
        level = PAGE_EXECUTE_READ;
    if (x == 3)
        level = PAGE_EXECUTE_READWRITE;
    if (x == 4)
        level = PAGE_EXECUTE_WRITECOPY;
    if (x == 5)
        level = PAGE_NOACCESS;
    if (x == 6)
        level = PAGE_READONLY;
    if (x == 7)
        level = PAGE_READWRITE;
    if (x == 8)
        level = PAGE_WRITECOPY;
    if (x == 9)
        level = PAGE_TARGETS_INVALID;
    if (x == 10)
        level = PAGE_TARGETS_NO_UPDATE;
    return level;
}

void VirtP() {
    LPVOID address = nullptr;

    int inputLevel;

    DWORD oldLevel = NULL;
    DWORD newLevel = NULL;

    printf("Введите адрес: 0x");
    cin >> address;

    if (address != nullptr) {
        pro_menu();
        cin >> inputLevel;
        newLevel = protectChoose(inputLevel);
        printf("Новый уровень защиты: ");
        protectCheck(newLevel);
        if (VirtualProtect(address, sizeof(DWORD), newLevel, &oldLevel)) {
            printf("Старый уровень защиты:");
            protectCheck(oldLevel);
        } else printf("Ошибка: %i\n", GetLastError());

    } else printf("Нулевой адрес (NULL)\n");
    system("pause");
}

void VirtF() {
    LPVOID address = nullptr;
    BOOL F = FALSE;
    printf("Введите адрес для возврата физ. памяти и освобождения региона адресного пространства: 0x");
    cin >> address;
    F = VirtualFree(address, 0, MEM_RELEASE);
    if (F)
        printf("Регион успешно освобожден\n");
    else printf("Ошибка: %i\n", GetLastError());
    system("pause");
}
