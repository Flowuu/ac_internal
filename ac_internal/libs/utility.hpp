#ifndef utility_h
#define utility_h


#include <Windows.h>
#include <iostream>
#include <vector>
#include <psapi.h>

class utility
{

private:
	std::vector<unsigned char> patternToBytes(const char* pattern)
	{
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

	std::vector<unsigned char> readBytes(uintptr_t pAddress, size_t length)
	{
		DWORD pOld;
		std::vector<unsigned char> cBytes;

		VirtualProtect((void*)pAddress, length, PAGE_EXECUTE_READWRITE, &pOld);

		unsigned char* rBytes = reinterpret_cast<unsigned char*>(pAddress);

		for (size_t i = 0; i < length; ++i)
			cBytes.push_back(rBytes[i]);

		VirtualProtect((void*)pAddress, length, pOld, NULL);

		return cBytes;
	}
	
	bool patchBytes(uintptr_t pAddress, const char* patternBytes)
	{
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

	uintptr_t signatureScanner(const char* module, const char* pattern)
	{
		std::vector<unsigned char> patternBytes = patternToBytes(pattern);

		MODULEINFO moduleInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(module), &moduleInfo, sizeof(MODULEINFO));

		PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((BYTE*)moduleInfo.lpBaseOfDll + ((PIMAGE_DOS_HEADER)moduleInfo.lpBaseOfDll)->e_lfanew);
		uintptr_t PeStart = pNtHeader->OptionalHeader.ImageBase + pNtHeader->OptionalHeader.BaseOfCode;
		uintptr_t PeEnd = PeStart + pNtHeader->OptionalHeader.SizeOfCode;

		for (uintptr_t i = PeStart; i < PeEnd - patternBytes.size(); i++)
		{
			bool pFound = true;

			for (size_t j = 0; j < patternBytes.size(); ++j)
			{

				if (patternBytes.data()[j] != '\?' && patternBytes.data()[j] != *(unsigned char*)(i + j))
				{
					pFound = false;
					break;
				}
			}

			if (pFound) 
				return i;
		}

		return 0;
	}

	uintptr_t signatureScanner(uintptr_t module, const char* pattern)
	{
		std::vector<unsigned char> patternBytes = patternToBytes(pattern);

		MODULEINFO moduleInfo;
		GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module), &moduleInfo, sizeof(MODULEINFO));

		PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((BYTE*)moduleInfo.lpBaseOfDll + ((PIMAGE_DOS_HEADER)moduleInfo.lpBaseOfDll)->e_lfanew);
		uintptr_t PeStart = pNtHeader->OptionalHeader.ImageBase + pNtHeader->OptionalHeader.BaseOfCode;
		uintptr_t PeEnd = PeStart + pNtHeader->OptionalHeader.SizeOfCode;

		for (uintptr_t i = PeStart; i < PeEnd - patternBytes.size(); i++)
		{
			bool pFound = true;

			for (size_t j = 0; j < patternBytes.size(); ++j)
			{

				if (patternBytes.data()[j] != '\?' && patternBytes.data()[j] != *(unsigned char*)(i + j))
				{
					pFound = false;
					break;
				}
			}

			if (pFound)
				return i;
		}

		return 0;
	}

	bool WorldToScreen(vec3 pos, vec2& screen)
	{
		vec4 clipCoords;
		clipCoords.w = pos.x * offsets.matrix[3] + pos.y * offsets.matrix[7] + pos.z * offsets.matrix[11] + offsets.matrix[15];
		if (clipCoords.w < 0.1f)
			return false;

		clipCoords.x = pos.x * offsets.matrix[0] + pos.y * offsets.matrix[4] + pos.z * offsets.matrix[8] + offsets.matrix[12];
		clipCoords.y = pos.x * offsets.matrix[1] + pos.y * offsets.matrix[5] + pos.z * offsets.matrix[9] + offsets.matrix[13];
		clipCoords.z = pos.x * offsets.matrix[2] + pos.y * offsets.matrix[6] + pos.z * offsets.matrix[10] + offsets.matrix[14];

		screen.x = (offsets.windowWidth / 2.0f) * (clipCoords.x / clipCoords.w + 1.0f);
		screen.y = (offsets.windowHeight / 2.0f) * (1.0f - clipCoords.y / clipCoords.w);

		return true;
	}

}; inline utility cUtility;

#endif