#include "stdafx.h"
#include "CALL.h"
#include "����.h"

void ����call(int ��ͷ) 
{
	VMBEGIN
	int ����call��ַ = ����Call;
	__asm
	{
		push ��ͷ
		mov ecx, ������ַ
		mov ecx, dword ptr ss : [ecx]
		call ����call��ַ
	}
	VMEND
}

void ����call(int ����, int ����)
{
	VMBEGIN
	int call��ַ = 0;
	if (���� == 1)call��ַ = ���ܰ�Call;
	if (���� == 2)call��ַ = ���ܰ�Call + 48;
	if (���� == 4)call��ַ = ���ܰ�Call + 96;
	if (���� == 8)call��ַ = ���ܰ�Call + 144;
	__asm
	{
		push ����
		mov ecx, ������ַ
		mov ecx, [ecx]
		mov eax, call��ַ
		call eax
	}
	VMEND
}


void ����call()
{
	VMBEGIN
	int ����Call��ַ = ����Call;
	_asm
	{
		mov ecx, ������ַ
		call ����Call��ַ;
	}
	VMEND
}

void ��ͼcall(int ����)
{
	VMBEGIN
	__asm
	{
		mov ecx, ������
		mov ecx, [ecx]
		mov ecx, [ecx + 0020A024h]
		mov ecx, [ecx + 0000008Ch]
		push 0xFF
		push 0xFF
		push 00h
		push 00h
		push 00h
		push 00h
		push 00h
		push [ebp + 08h]
		mov eax, ��ͼCall
		call eax
	}
	VMEND
}

void ����call(int �����ַ, int x, int y, int z)
{
	__asm
	{
		mov esi, [ebp + 08h]
		mov edi, [esi]
		push [ebp + 14h]
		push [ebp + 10h]
		push [ebp + 0Ch]
		mov eax, [edi + 000000A8h]
		mov ecx, esi
		mov eax, eax
		mov eax, eax
		mov eax, eax
		call eax
	}
}

void ����call(int ����ID)
{
	__asm
	{
		push [ebp + 08h]
		mov eax, ����Call
		call eax
	}
}

void �ύcall(int ����ID)
{
	__asm
	{
		push 01h
		push 0xFF
		push[ebp + 08h]
		mov ecx, �����ַ
		mov eax, �ύCall
		mov eax, eax
		call eax
	}
}

void �ͷ�call(int �����ַ, int ����, int �˺�, int X, int Y, int Z)
{
	_asm
	{
		push Z
		push Y
		push X
		push �˺�
		push ����
		push �����ַ
		mov edi, �ͷ�Call
		mov eax, edi
		call eax
		add esp, 0x18
	}
}

void ���call(int ����ID)
{
	__asm
	{
		push 0xFF
		push 255
		push ����ID
		mov eax,���Call
		call eax
	}
}

void ����call(int ����)
{
	__asm
	{
		push ����
		mov ecx,����
		mov esi,ecx
		mov eax,����Call
		call eax
		add esp,4
	}
}
