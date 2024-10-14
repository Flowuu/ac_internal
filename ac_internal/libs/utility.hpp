#ifndef utility_h
#define utility_h


#include <Windows.h>
#include <iostream>
#include <vector>
#include <psapi.h>

class utility
{

private:
	std::vector<unsigned char> patternToBytes(const char* pattern) {
		std::vector<unsigned char> bytes;
		char* start = const_cast<char*>(pattern);
		char* end = const_cast<char*>(pattern) + strlen(pattern);

		for (char* current = start; current < end; current++)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					current++;
				bytes.push_back('\?');
			}
			else
			{
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	}

public:

	unsigned char* readBytes(uintptr_t pAddress, size_t length) {
		DWORD pOld;

		VirtualProtect((void*)pAddress, length, PAGE_EXECUTE_READWRITE, &pOld);

		//finish

		VirtualProtect((void*)pAddress, length, pOld, NULL);

		return NULL;
	}
	
	bool patchBytes(uintptr_t pAddress, const char* patternBytes) {
		DWORD pOld;
		std::vector<unsigned char> cBytes = patternToBytes(patternBytes);

		if (!VirtualProtect((void*)pAddress, cBytes.size(), PAGE_EXECUTE_READWRITE, &pOld))
			return false;

		unsigned char* pByte = reinterpret_cast<unsigned char*>(pAddress);
		for (size_t i = 0; i < cBytes.size(); i++)
			pByte[i] = cBytes.data()[i];

		VirtualProtect((void*)pAddress, cBytes.size(), pOld, NULL);

		return true;
	}

	uintptr_t signatureScanner(const char* module, const char* pattern) {
		std::vector<unsigned char> patternBytes = patternToBytes(pattern);

		MODULEINFO moduleInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(module), &moduleInfo, sizeof(MODULEINFO));

		PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((BYTE*)moduleInfo.lpBaseOfDll + ((PIMAGE_DOS_HEADER)moduleInfo.lpBaseOfDll)->e_lfanew);
		uintptr_t PeStart = pNtHeader->OptionalHeader.ImageBase + pNtHeader->OptionalHeader.BaseOfCode;
		uintptr_t PeEnd = PeStart + pNtHeader->OptionalHeader.SizeOfCode;

		for (uintptr_t i = PeStart; i < PeEnd - patternBytes.size(); i++) {
			bool pFound = true;

			for (size_t j = 0; j < patternBytes.size(); ++j) {

				if (patternBytes.data()[j] != '\?' && patternBytes.data()[j] != *(unsigned char*)(i + j)) {
					pFound = false;
					break;
				}
			}

			if (pFound) {
				return i;
			}
		}

		return 0;
	}

}; inline utility cUtility;

#endif