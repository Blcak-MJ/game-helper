#include "stdafx.h"
#include "���ܽ���.h"

void ��������(int ��ַ, int ��ֵ, int ����)
{
	int ����ID, ƫ�Ʋ���, ƫ�Ƶ�ַ, data, ��ַβ;
	short ax, si;
	����ID = read(��ַ);
	ƫ�Ʋ��� = read(read(���ܻ�ַ) + (����ID >> 16) * 4 + 36);
	ƫ�Ƶ�ַ = ƫ�Ʋ��� + (����ID & 65535) * 4 + 8468;
	ƫ�Ʋ��� = read(ƫ�Ƶ�ַ);
	data = ƫ�Ʋ��� & 65535;
	data = data + (data << 16);
	ax = (short)(ƫ�Ʋ��� & 65535);
	si = 0;
	if (���� == 0)
	{
		��ַβ = ��ַ & 15;
		switch (��ַβ)
		{
		case 0:
			si = (short)(��ֵ >> 16);
			si = (short)(si - ax);
			si = (short)(si + ��ֵ);
			break;
		case 4:
			si = (short)((��ֵ & 65535) - (��ֵ >> 16));;
			break;
		case 8:
			si = (short)(��ֵ >> 16);
			si = (short)(si * ��ֵ);
			break;
		case 12:
			si = (short)(��ֵ >> 16);
			si = (short)(si + ��ֵ);
			si = (short)(si + ax);
			break;
		default:
			return;
		}
	}
	else if (���� == 1)
		si = (��ֵ & 255);
	else if (���� == 2)
		si = ��ֵ;
	else if (���� == 3)
	{
		si = (��ֵ >> 16);
		si += ��ֵ;
	}
	else if (���� == 4)
	{
		si = (��ֵ >> 16);
		si = si + (��ֵ & 65535);
	}
	else
		return;
	ax = (short)(si ^ ax);
	data = data ^ ��ֵ;
	write(��ַ + (���� != 4 ? 4 : 8),data);
	write<short>(ƫ�Ƶ�ַ + 2 , ax);
}

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

int ����(int ��ַ)
{
	int eax = read(��ַ);
	int esi = read(���ܻ�ַ);
	int edx = eax >> 16;
	edx = read(esi + edx * 4 + 36);
	eax = eax & 65535;
	eax = read(edx + eax * 4 + 8468);
	edx = eax & 65535;
	esi = edx << 16;
	esi = esi | edx;
	esi = esi ^ (read(��ַ + 4));
	return esi;
}

