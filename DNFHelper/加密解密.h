#pragma once

#include "��ַ.h"
#include "�ڴ��д.h"

void ��������(int ��ַ, int ��ֵ, int ���� = 0);

//int ��������(int ��ַ)
//{
//	int EAX, ecx8, esi, EDX;
//	EAX = read(��ַ);
//	ecx8 = read(��ַ + 4);
//	esi = read(���ܻ�ַ);
//	EDX = EAX >> 16;
//	EDX = read((EDX << 2) + esi + 36);
//	EAX = EAX & 65535;
//	EAX = read((EAX << 2) + EDX + 8468);
//	__asm
//	{
//		mov eax, EAX
//		movzx edx, eax
//		mov eax, esi
//		mov esi, edx
//		shl esi, 10h
//		or esi, edx
//		mov edx, EDX
//		xor esi, edx
//		xchg eax, esi
//		leave
//		retn 0x0004
//	}
//	return 0;
//}

int ����(int ��ַ);
