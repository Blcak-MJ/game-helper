#include "stdafx.h"
#include "�ڴ��д.h"

bool �ÿɶ�д(HANDLE ���̾��, int �ڴ��ַ, SIZE_T �ڴ泤��)
{
	typedef BOOL(NTAPI *LPZwProtectVirtualMemory)(HANDLE ProcessHandle,
		PVOID *     BaseAddress,
		SIZE_T *     NumberOfBytesToProtect,
		ULONG     NewAccessProtection,
		PULONG     OldAccessProtection
		);
	LPZwProtectVirtualMemory ZwProtectVirtualMemory = (LPZwProtectVirtualMemory)GetProcAddress(LoadLibrary(L"ntdll.dll"), "ZwProtectVirtualMemory");
	return ZwProtectVirtualMemory(���̾��, (LPVOID*)�ڴ��ַ, &�ڴ泤��, 64, NULL);
}



void �ַ�����(int �ڴ��ַ, int ��ֵ��ַ, int д�볤��)
{
	/*
	��Ϊread����ַ1Ϊ���ݵ�ַ����ַ2Ϊ�ڴ��ַ
	��Ϊwrite����ַ1Ϊ�ڴ��ַ����ַ2Ϊ���ݵ�ַ
	*/
	_asm
	{
		push esi
		push edi
		pushfd
		cld
		mov ecx, [ebp + 10h]
		mov esi, [ebp + 0Ch]
		mov edi, [ebp + 08h]
		rep movsb
		popfd
		pop edi
		pop esi
	}
}


WCHAR* ���ı�(int �ڴ��ַ, int ��ȡ����)
{
	WCHAR* tmp = new WCHAR[200]; // tmpΪ���ݵĵ�ַ��&tmpΪ���ָ��ĵ�ַ
	wmemset(tmp, 0, sizeof(tmp));
	if (IsBadReadPtr((VOID*)�ڴ��ַ, ��ȡ����))
		return NULL;
	�ַ�����(reinterpret_cast<int>(tmp), �ڴ��ַ, ��ȡ����);
	return tmp;
}

bool д�ı�(int �ڴ��ַ, const WCHAR* д������)
{
	DWORD len = (lstrlen(д������) + 1) * sizeof(WCHAR); // ��һ��\0
	if (IsBadWritePtr((VOID*)�ڴ��ַ, len))
		return false;
	�ַ�����(�ڴ��ַ, reinterpret_cast<int>(д������), len);
	return true;
}


void �����¼�()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
}

void ������ʱ(int ��ʱ���)
{
	LARGE_INTEGER int64;
	int64.QuadPart = -10 * ��ʱ��� * 1000;
	HANDLE hTimer = CreateWaitableTimerA(0, false, 0);
	SetWaitableTimer(hTimer, &int64, 0, 0, 0, false);
	while(MsgWaitForMultipleObjects(1, &hTimer, false, -1, 255) != 0)
	{
		�����¼�();
	}
	CloseHandle(hTimer);
}

int ȡƫ�Ƶ�ַ(int ��ַ,std::initializer_list<int> ƫ������)
{
	int ��ַ = ��ַ;
	for (auto p = ƫ������.begin(); p != ƫ������.end(); p++)
	{
		��ַ = read(��ַ);
		��ַ = ��ַ + (*p);
	}
	return ��ַ;
}