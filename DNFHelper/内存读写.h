#pragma once

#include "stdafx.h"
#include <wchar.h>
#include <iostream>

bool �ÿɶ�д(HANDLE ���̾��, int �ڴ��ַ, SIZE_T �ڴ泤��);

void �ַ�����(int �ڴ��ַ, int ��ֵ��ַ, int д�볤��);

WCHAR* ���ı�(int �ڴ��ַ, int ��ȡ����);

bool д�ı�(int �ڴ��ַ, const WCHAR* д������);

void �����¼�();

void ������ʱ(int ��ʱ���);

int ȡƫ�Ƶ�ַ(int ��ַ, std::initializer_list<int> ƫ������);

template<typename T=int>
T read(int address)
{
	if (address == 0x18181818)
		return 0;
	if (address <= 0x00400000)
		return 0;
	if (IsBadReadPtr((VOID*)address, sizeof(T)))
		return 0;
	HANDLE hProcess = GetCurrentProcess(); ;
	T result;
	int length = sizeof(T);
	DWORD oldProtect;
	VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);//��Ȩ
	ReadProcessMemory(hProcess, (LPCVOID)address, &result, length, FALSE);//�ڴ������
	VirtualProtectEx(hProcess, (LPVOID)address, length, oldProtect, &oldProtect);//��Ȩ
	CloseHandle(hProcess);
	return (T)result;
}

template<typename T = int>
BOOL write(int address,T data)
{
	if (address == 0x18181818)
		return FALSE;
	if (address <= 0x00400000)
		return FALSE;
	if (IsBadWritePtr((VOID*)address, sizeof(T)))
		return FALSE;
	HANDLE hProcess = GetCurrentProcess();
	DWORD oldProtect;
	int length = sizeof(T);
	VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	BOOL a = WriteProcessMemory(hProcess, (LPVOID)address, (LPCVOID)&data, length, 0);
	VirtualProtectEx(hProcess, (LPVOID)address, length, oldProtect, &oldProtect);
	CloseHandle(hProcess);//�رն���
	return a;
}
