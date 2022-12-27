#pragma once

#include <string>

class ScanData
{
private:
	static const size_t hexTable[];

public:
	unsigned char* data; //byte array
	size_t size = 0;

	ScanData(const std::string input);
	ScanData(size_t size);
	~ScanData();
    static HANDLE getHandle(const char* proc) {
        HANDLE hProcessId = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        HANDLE handle = nullptr;
        DWORD processID = 0;
        PROCESSENTRY32 pEntry;
        pEntry.dwSize = sizeof(pEntry);
        Process32Next(hProcessId, &pEntry);
        do {
            if (!strcmp(reinterpret_cast<char*>(pEntry.szExeFile), proc)) {
                processID = pEntry.th32ProcessID;
                CloseHandle(hProcessId);
                return OpenProcess(PROCESS_ALL_ACCESS, false, processID);
            }

        } while (Process32Next(hProcessId, &pEntry));
        return 0;
    }
    static uintptr_t bruteForce(const ScanData& signature, const ScanData& data) {
        for (size_t currentIndex = 0; currentIndex < data.size - signature.size; currentIndex++) {
            for (size_t sigIndex = 0; sigIndex < signature.size; sigIndex++) {
                if (data.data[currentIndex + sigIndex] != signature.data[sigIndex] && signature.data[sigIndex] != '?') {
                    break;
                }
                else if (sigIndex == signature.size - 1) {
                    return currentIndex;
                }
            }
        }
        return 0;
    }

	void print();

};

