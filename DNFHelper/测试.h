#pragma once
#include "stdafx.h"
#include "CALL.h"
#include "�ڴ��д.h"
#include "ȫ��.h"
#include "�Զ�.h"
#include "���.h"
#include "���ù���.h"
#include "�ٻ���ż����.h"
#include <stdio.h>
#include <string.h>

void �������()
{
	int �׵�ַ_ = read(read(�����ַ) + �����׵�ַ);
	int β��ַ_ = read(read(�����ַ) + ����β��ַ);
	int �������� = (β��ַ_ - �׵�ַ_) / 4;
	for (int i = 0; i < ��������; i++)
	{
		int �����ַ = read(�׵�ַ_ + i * 4);
		int ��������_ = read(�����ַ + ��������);
		if (��������_ == 0)
		{
			int ����ID = read(�����ַ);
			if (����ID == 0) continue;
			���call(����ID);
			������ʱ(300);
			����(L"��� ����IDΪ��%d",����ID);
		}
	}
}

void �������2()
{
	int �׵�ַ_ = read(read(�����ַ) + 0x8);
	int β��ַ_ = read(read(�����ַ) + 0xc);
	int �������� = (β��ַ_ - �׵�ַ_) / 4;
	for (int i = 0; i < ��������; i++)
	{
		int �����ַ = read(�׵�ַ_ + i * 4);
		int ��������_ = read(�����ַ + ��������);
		int ����ID = read(�����ַ);
		���call(����ID);
		������ʱ(300);
		�ύcall(����ID);
		������ʱ(300);
		����(L"��� ����IDΪ��%d", ����ID);
	}
}

void �������3()
{
	int �׵�ַ_ = read(read(�����ַ) + �����׵�ַ);
	int β��ַ_ = read(read(�����ַ) + ����β��ַ);
	int �������� = (β��ַ_ - �׵�ַ_) / 4;
	for (int i = 0; i < ��������; i++)
	{
		int �����ַ = read(�׵�ַ_ + i * 4);
		int ��������_ = read(�����ַ + ��������);
		if (��������_ == 0)
		{
			int ����ID = read(�����ַ);
			�ύcall(����ID);
		}
	}
}
FILE* fp;
char sz_add[30];
void �����ͷ�(int ����)
{
	VMBEGIN
	int һ��ƫ�� = read(�����ַ);
	int x = (int)read<float>(һ��ƫ�� + X����);
	int y = (int)read<float>(һ��ƫ�� + Y����);
	�ͷ�call(һ��ƫ��, ����, 1, x, y, 0);
	VMEND
}

DWORD ������ѭ��(LPVOID)
{
	fopen_s(&fp, "C:\\code.txt", "a+");
	fseek(fp, 0, SEEK_END);
	for (int i = 24000; i <= 40000; i++)
	{
		if (�Ƿ��ڳ���() == true)
		{
			Sleep(5000);
			i--;
			continue;
		}
		����(L"��ǰi Ϊ %d", i);
		�����ͷ�(i);
	}
	return 0;
}

HANDLE aaa = NULL;
int ���ܱ�������()
{
	if (aaa == NULL)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)������ѭ��, NULL, 0, NULL);
	else
	{
		TerminateThread(aaa, 0);
		aaa = NULL;
	}
	return 0;
}

void ���ͱ���()
{
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
	if (����ƫ�� <= 0)
	{
		����(L"����ƫ��Ϊ%d", ����ƫ��);
		return;
	}
	int �׵�ַ_ = read(����ƫ�� + �׵�ַ);
	int β��ַ_ = read(����ƫ�� + β��ַ);
	int �������� = (β��ַ_ - �׵�ַ_) / 4;
	����(L"�׵�ַΪ%d β��ַΪ%d  ��������Ϊ%d", �׵�ַ_, β��ַ_, ��������);
	int x, y, z;
	for (int i = 1; i <= ��������; i++)
	{
		int ��ַ = read(�׵�ַ_ + 4 * i);
		int ���� = read(��ַ + ����ƫ��);
		int ��Ӫ = read(��ַ + ��Ӫƫ��);
		int Ѫ�� = read(��ַ + ����Ѫ��ƫ��);
		x = (int)read<float>(��ַ + X����);
		y = (int)read<float>(��ַ + Y����);
		z = (int)read<float>(��ַ + Z����);
		if ((���� == 529 || ���� == 545 || ���� == 273))
			����(L"��ַ��%d  ���ͣ�%d  ��Ӫ��%d  Ѫ����%d  x��%d  y��%d  z��%d", ��ַ, ����, ��Ӫ, Ѫ��, x, y, z);
	}
}
DWORD ��ż�������(LPVOID)
{
	for (int i = 400; i <= 1000; i++)
	{
		if (�Ƿ��ڳ���() == true)
		{
			Sleep(5000);
			i--;
			continue;
		}
		����(L"��ǰ����Ϊ %d", i);
		��żcall(i);
		Sleep(1000);
	}
	return 0;
}

void ��ż����()
{
	if (aaa == NULL)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)��ż�������, NULL, 0, NULL);
	else
	{
		TerminateThread(aaa, 0);
		aaa = NULL;
	}
}

void test()
{
	int type = GetPrivateProfileInt(L"����", L"type", 1, filepath);
	if (type == 1)
	{
		int code = GetPrivateProfileInt(L"ȫ��", L"���ܴ���", 1, filepath);
		����(L"���� �� %d ", code);
		�����¼�();
		�����ͷ�(code);
	}
	else if (type == 2)
	{
		�������();
	}
	else if (type == 3)
	{
		�������3();
	}
	else if (type == 4)
	{
		int һ��ƫ�� = read(�����ַ);
		int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
		if (����ƫ�� == 0)
		{
			ϵͳ����(L"����ƫ��Ϊ0 ���޷�����");
			return;
		}
		int �׵�ַ_ = read(����ƫ�� + �׵�ַ);
		int β��ַ_ = read(����ƫ�� + β��ַ);
		int �������� = (β��ַ_ - �׵�ַ_) / 4;
		int ��������_ = 0;

		int rx = (int)read<float>(һ��ƫ�� + X����);
		int ry = (int)read<float>(һ��ƫ�� + Y����);
		����(L"���� x��%d  y��%d ����������%d", rx, ry,��������);
		for (int i = 0; i <= ��������; i++)
		{
			int ��ַ = read(�׵�ַ_ + 4 * i);
			int ���� = read(��ַ + ����ƫ��);
			int ��Ӫ = read(��ַ + ��Ӫƫ��);
			int Ѫ�� = read(��ַ + ����Ѫ��ƫ��);
			int ���� = read(��ַ + �������);
			int x, y;
			x = (int)read<float>(��ַ + X����);
			y = (int)read<float>(��ַ + Y����);
			����(L"���ͣ�%d  Ѫ����%d  ���룺%d  x:%d  y:%d ", ����, Ѫ��, ����, x, y);
		}
	}
}