#include "stdafx.h"
#include "�ٻ���ż����.h"

int ������ż��ַ()
{
	VMBEGIN
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
	int �׵�ַ_ = read(����ƫ�� + �׵�ַ);
	int β��ַ_ = read(����ƫ�� + β��ַ);
	int �����ַ = read(�����ַ);
	int �������� = (β��ַ_ - �׵�ַ_) / 4;
	for (int i = 1; i <= ��������; i++)
	{
		int �����ַ = read(�׵�ַ_ + 4 * i);
		int �������� = read(�����ַ + ����ƫ��);
		int ������Ӫ = read(�����ַ + ��Ӫƫ��);
		if (�������� == 273 && ������Ӫ == 0 && �����ַ != �����ַ)
		{
			return �׵�ַ_ + 4 * i;
		}
	}
	return 0;
	VMEND
}

void ��żcall(int ����)
{
	VMBEGIN
	if (���� == 0)
		���� = GetPrivateProfileInt(L"��ż����", L"��ż����", 0, filepath);
	int ���� = read(�ٻ�����);
	int ָ�� = read(�����ַ);
	int* �ṹ = new int[5];
	�ṹ[0] = ����;
	�ṹ[1] = -1;
	�ṹ[2] = -1;
	�ṹ[3] = 12345688; // ����ʱ��
	�ṹ[4] = 1; // ��Ч
	int �ٻ���żCall_ = �ٻ���żCall;
	_asm
	{
		push �ṹ
		push ָ��
		mov ecx, ����
		call �ٻ���żCall_
	}
	VMEND
}


void ����call()
{
	VMBEGIN
	int ���� = GetPrivateProfileInt(L"��ż����", L"�������", 0, filepath);
	int ���� = read(�ٻ�����);
	int ָ�� = read(�����ַ);
	int* �ṹ = new int[5];
	�ṹ[0] = ����;
	�ṹ[1] = -1;
	�ṹ[2] = -1;
	�ṹ[3] = 12345688; // ����ʱ��
	�ṹ[4] = 1; // ��Ч
	int �ٻ�����Call_ = �ٻ�����Call;
	_asm
	{
		push �ṹ
		push ָ��
		mov ecx, ����
		call �ٻ�����Call_
	}
	ϵͳ����(L"�Ѿ��ٻ�����");
	VMEND
}