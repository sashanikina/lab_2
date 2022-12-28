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
        printf("������� 1 ��� ��������� ���������� � �������������� �������\n");
        printf("������� 2 ��� ����������� ������� ����������� ������\n");
        printf("������� 3 ��� ����������� ��������� ����������� ������� ������\n");
        printf("������� 4 ��� �������������� �������\n");
        printf("������� 5 ��� �������������� ������� � �������� ��� ���������� ������\n");
        printf("������� 6 ��� ������ ������ � ������ ������\n");
        printf("������� 7 ��� ��������� ������ ������� ��� ��������� ������� ������ � �� ��������\n");
        printf("������� 8 ��� �������� ���������� ������ � ������������ ������� ��������� ������������ ��������� ������� ������\n");
        printf("������� 0 ��� ������\n");
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
    printf("����������� ����������:  ");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) printf("x64 (AMD ��� Intel)\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) printf("ARM\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) printf("ARM64\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) printf("Intel Itanium-based\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) printf("x86\n");
    if (siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_UNKNOWN) printf("����������� �����������\n");

    printf("������ �������� %i\n", (int) siSysInfo.dwPageSize);
    printf("��������� �� ���������� ����� ������: 0x%p\n", (void *) siSysInfo.lpMinimumApplicationAddress);
    printf("��������� �� ���������� ����� ������: 0x%p\n", (void *) siSysInfo.lpMaximumApplicationAddress);
    printf("�����, �������������� ����� �����������, ����������� � �������: %s\n",
           bitset<sizeof(siSysInfo.dwActiveProcessorMask) * CHAR_BIT>(
                   siSysInfo.dwActiveProcessorMask).to_string().c_str());
    printf("���������� ���������� ����������� � ������� ������: %i\n", (int) siSysInfo.dwNumberOfProcessors);
    printf("������������� ������ �������: %i\n", (int) siSysInfo.dwAllocationGranularity);
    printf("������� ����������: %i\n", (int) siSysInfo.wProcessorLevel);
    printf("������ ����������: %i\n", (int) siSysInfo.wProcessorRevision);

    system("pause");
}

void MemStat() {
    MEMORYSTATUS stat;

    GlobalMemoryStatus(&stat);

    printf("������ ��������� ������ � ������: %ld\n", stat.dwLength);
    printf("������� ������������ ���������� ������: %ld\n", stat.dwMemoryLoad);
    printf("����� ����������� ���������� ������ � %s������: %ld \n", "K", stat.dwTotalPhys / 1024);
    printf("����� ��������� ���������� ������ � %s������: %ld\n", "K", stat.dwAvailPhys / 1024);
    printf("������� ������ ���������������� ����������� ������ � %s������: %ld\n", "K", stat.dwTotalPageFile / 1024);
    printf("������������ ����� ������, ������� ����� ������������� ������� ������� � %s������: %ld\n", "K",
           stat.dwAvailPageFile / 1024);
    printf("������ ����� ������������ ��������� ������������ ����������� �������� � %s������: %ld\n", "K",
           stat.dwTotalVirtual / 1024);
    printf("����� ���������� ������ ������ ������������ ��������� ������������ ����������� �������� � %s������: %ld\n",
           "K", stat.dwAvailVirtual / 1024);

    system("pause");
}

void protectCheck(DWORD level) {

    if (level == 0)
        printf("���������� �������");
    if (level == PAGE_EXECUTE)
        printf("�������� ���������� ������� � ��������������� ������� ������� \n\t(PAGE_EXECUTE)\n");
    if (level == PAGE_EXECUTE_READ)
        printf("������� ������ ������ ��� ���������� ��� ������ � ��������������� ������� �������. "
               "������� ������ � ��������������� ������� �������� � ��������� ������� \n\t(PAGE_EXECUTE_READ)\n");
    if (level == PAGE_EXECUTE_READWRITE)
        printf("������� ������ ������ ��� ����������, ������ ��� ������/������ � ��������������� ������� ������� \n\t(PAGE_EXECUTE_READWRITE)\n");
    if (level == PAGE_EXECUTE_WRITECOPY)
        printf("�������� ������ ������ ��� ����������, ������ ��� ����������� ��� ������ � ��������������� ������������� ������� ������������� ������ \n\t(PAGE_EXECUTE_WRITECOPY)\n");
    if (level == PAGE_NOACCESS)
        printf("�������� ���� ������ � ��������������� ������� ������� \n\t(PAGE_NOACCESS)\n");
    if (level == PAGE_READONLY)
        printf("������� ������ ������ ��� ������ � ��������������� ������� ������� \n\t(PAGE_READONLY)\n");
    if (level == PAGE_READWRITE)
        printf("�������� ������ ������ ��� ������ ��� ������/������ � ��������������� ������� ������� \n\t(PAGE_READWRITE)\n");
    if (level == PAGE_WRITECOPY)
        printf("�������� ������ ������ ��� ������ ��� ����������� ��� ������ � ��������������� ������������� ������� ������������� ������ \n\t(PAGE_WRITECOPY)\n");
    if (level == PAGE_TARGETS_INVALID)
        printf("��� �������������� �� ��������� ����������� � �������� ������������ ������� �������� ��� CFG \n\t(PAGE_TARGETS_INVALID)\n");
    if (level == PAGE_TARGETS_NO_UPDATE)
        printf("��� ������� � ������� �� ����� ����������� ���������� � CFG \n\t(PAGE_TARGETS_NO_UPDATE)\n");


    if ((level & PAGE_GUARD) != 0) {
        printf("�������� � ������� �������� \n(PAGE_GUARD)\n");
    }
    if ((level & PAGE_NOCACHE) != 0)
        printf("�������� �� ���������� \n(PAGE_NOCACHE)\n");
    if ((level & PAGE_WRITECOMBINE) != 0) {
        printf("�������� � ����������� � ����� ��������������� ������ \n(PAGE_WRITECOMBINE)\n");
    }

}

void VirtQ() {
    LPCVOID lpAddress;
    MEMORY_BASIC_INFORMATION lpBuffer;
    int address;

    printf("������� ����������� �����: 0x");
    cin >> hex >> address;
    lpAddress = (LPCVOID) address;
    VirtualQuery(lpAddress, &lpBuffer, sizeof(lpBuffer));

    printf("��������� �� ������� ����� ������� �������: %p\n", (void *) lpBuffer.BaseAddress);
    printf("��������� �� ������� ����� ��������� �������, ���������� �������������: %p\n",
           (void *) lpBuffer.AllocationBase);

    printf("�������� ������ ������ ��� �������������� ��������� �������: ");
    protectCheck(lpBuffer.AllocationProtect);


    if ((lpBuffer.AllocationProtect & PAGE_GUARD) != 0) {
        printf("�������� � ������� �������� \n(PAGE_GUARD)");
    }
    if ((lpBuffer.AllocationProtect & PAGE_NOCACHE) != 0)
        printf("�������� �� ���������� \n(PAGE_NOCACHE)");
    if ((lpBuffer.AllocationProtect & PAGE_WRITECOMBINE) != 0) {
        printf("�������� � ����������� � ����� ��������������� ������ \n(PAGE_WRITECOMBINE)");
    }


    printf("\n������ �������, ������������ � �������� ������, � ������� ��� �������� ����� ���������� ��������:  %u ����\n",
           lpBuffer.RegionSize);
    printf("������ ������� � ��������� � �������: %lx\n", lpBuffer.Protect);

    printf("��������� ������� � �������: ");
    if (lpBuffer.State == MEM_COMMIT)
        printf("��������������� ��������\n");
    if (lpBuffer.State == MEM_FREE)
        printf("��������� ��������, ����������� ��� ����������� �������� � ��������� ��� ���������\n");
    if (lpBuffer.State == MEM_RESERVE) {
        printf("����������������� ��������, �� ������� �������������� �������� ������������ ��������� "
               "������������ �������� ��� ��������� ������ - ���� ����������� ���������\n");
    }

    printf("��� ������� � �������: ");
    if (lpBuffer.Type == MEM_IMAGE)
        printf("�������� ������ � �������� ������� ������������ � ���� ������� �����������\n");
    if (lpBuffer.Type == MEM_MAPPED)
        printf("�������� ������ � �������� ������� �������������� � �������������� �������\n");
    if (lpBuffer.Type == MEM_PRIVATE)
        printf("�������� ������ � �������� ������� �������� ��������\n");
    system("pause");

}

void VirtAll() {
    LPVOID Addr;
    LPVOID Addr2 = nullptr;
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);

    Addr = VirtualAlloc(nullptr, siSysInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (Addr != nullptr) {
        printf("�������������� �������������� �������! ������� ����� �������: 0�%p \n", Addr);
        printf("�������������� � ������ ����� ������ ������ �������...\n");
        printf("������� �����: 0x");
        cin >> hex >> Addr2;

        Addr = VirtualAlloc(Addr2, siSysInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);

        if (Addr != nullptr)
            printf("�������������� �������! ������� ����� �������: 0x%p \n", Addr);
        else printf("������ ��������������.");
    } else printf("������ ��������������.");

    system("pause");
}

void VirtAll2() {
    LPVOID Addr;
    LPVOID Addr2 = nullptr;
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    Addr = VirtualAlloc(nullptr, siSysInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (Addr != nullptr) {
        printf("�������������� �������������� �������! ������� ����� �������: 0�%p \n", (void *) Addr);
        printf("�������������� � ������ ����� ������ ������ �������...\n");
        printf("������� �����: 0x");
        cin >> hex >> Addr2;

        Addr = VirtualAlloc(Addr2, siSysInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

        if (Addr != nullptr)
            printf("�������������� � �������� ������ �������! ������� ����� ������� 0x%p \n", (void *) Addr);
        else printf("�������������� � �������� �� ������\n");
    } else printf("�������������� � �������� �� ������\n");

    system("pause");
}

void WriteInfo() {
    LPVOID addr;
    char *strAddr;
    SIZE_T res;
    string str;
    MEMORY_BASIC_INFORMATION lpBuffer;
    printf("������� ����� ������� ������: 0�");
    cin >> hex >> addr;
    cin >> dec;
    printf("������� ������ ������: ");
    cin >> str;
    res = VirtualQuery(addr, &lpBuffer, sizeof(lpBuffer));
    if (res) {
        if (!((lpBuffer.Protect &
               (PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_READWRITE | PAGE_WRITECOPY)) &&
              (lpBuffer.State == MEM_COMMIT))) {
            printf("������: ������ �� ��������\n");
        }
        if (!(lpBuffer.RegionSize >= str.length() * sizeof(char))) {
            printf("������� ������� ������\n");
        }
        strAddr = (char *) addr;
        CopyMemory(strAddr, str.c_str(), str.length() * sizeof(char));
        printf("��������� ����� ������� ������: 0x%p\n", (void *) strAddr);
        printf("���������� ����������: ");
        for (int i = 0; i < str.length(); ++i)
            printf("%c", strAddr[i]);
        printf("\n");
    } else printf("������ �������� ������: %i\n", GetLastError());
    system("pause");
}

void pro_menu() {
    printf("������� 1 ��� ��������� ������� � ��������������� ������� ������� \n\t(PAGE_EXECUTE)\n");
    printf("������� 2 ��� ��������� ������� ������ ��� ���������� ��� ������ � ��������������� ������� ������� \n\t(PAGE_EXECUTE_READ)\n");
    printf("������� 3 ��� ��������� ������� ������ ��� ����������, ������ ��� ������/������ � ��������������� ������� ������� \n\t(PAGE_EXECUTE_READWRITE)\n");
    printf("������� 4 ��� ��������� ������� ������ ��� ����������, ������ ��� ����������� ��� ������ � ��������������� ������������� ������� ������������� ������ \n\t(PAGE_EXECUTE_WRITECOPY)\n");
    printf("������� 5 ��� ���������� ����� ������� � ��������������� ������� ������� \n\t(PAGE_NOACCESS)\n");
    printf("������� 6 ��� ��������� ������� ������ ��� ������ � ��������������� ������� ������� \n\t(PAGE_READONLY)\n");
    printf("������� 7 ��� ��������� ������� ������ ��� ������ ��� ������/������ � ��������������� ������� ������� \n\t(PAGE_READWRITE)\n");
    printf("������� 8 ��� ��������� ������� ������ ��� ������ ��� ����������� ��� ������ � ��������������� ������������� ������� ������������� ������ \n\t(PAGE_WRITECOPY)\n");
    printf("������� 9 ��� ��������� ���� �������������� �� ��������� � �������� ������������ ������� �������� ��� CFG \n\t(PAGE_TARGETS_INVALID)\n");
    printf("������� 10, ����� ��� ������� � ������� �� ����������� ���������� � CFG \n\t(PAGE_TARGETS_NO_UPDATE)\n");
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

    printf("������� �����: 0x");
    cin >> address;

    if (address != nullptr) {
        pro_menu();
        cin >> inputLevel;
        newLevel = protectChoose(inputLevel);
        printf("����� ������� ������: ");
        protectCheck(newLevel);
        if (VirtualProtect(address, sizeof(DWORD), newLevel, &oldLevel)) {
            printf("������ ������� ������:");
            protectCheck(oldLevel);
        } else printf("������: %i\n", GetLastError());

    } else printf("������� ����� (NULL)\n");
    system("pause");
}

void VirtF() {
    LPVOID address = nullptr;
    BOOL F = FALSE;
    printf("������� ����� ��� �������� ���. ������ � ������������ ������� ��������� ������������: 0x");
    cin >> address;
    F = VirtualFree(address, 0, MEM_RELEASE);
    if (F)
        printf("������ ������� ����������\n");
    else printf("������: %i\n", GetLastError());
    system("pause");
}
