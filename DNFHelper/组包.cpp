#include "stdafx.h"
#include "���.h"
#include "����.h"

void �������(int x,int y)
{
	VMBEGIN
	����call(69);
	����call();
	����call(70);
	����call();
	����call(71);
	����call(x, 1);
	����call(y, 1);
	����call();
	VMEND
}


void ���ʰȡ(int ��Ʒ��ַ)
{
	VMBEGIN
	����call(43);
	����call(��Ʒ��ַ, 4);
	����call(0, 1);
	����call(1, 1);
	for (int i = 0; i < 7; i++)
		����call(0, 2);
	����call();
	VMEND
}


void ����ֽ�(int װ��λ��)
{
	VMBEGIN
	����call(26);
	����call(װ��λ��, 2);
	����call(0, 1);
	����call(65535, 2);
	����call(319, 4);
	����call();
	VMEND
}

void ѡ��ɫ(int ��ɫλ��, int ����)
{
	VMBEGIN
	if (���� == 0)
	{
		����call(7);
		����call();
	}
	else
	{
		����call(4);
		����call(��ɫλ��, 4);
		����call();
	}
	VMEND
}

void �����ɱ(int ��ַ)
{
	����call(39);
	����call(��ַ, 4);
	����call(0, 2);
	for (int i = 0; i < 4; i++)
		����call(0, 4);
	����call(0, 1);
	����call(0, 2);
	����call(0, 2);
	for (int i = 0; i < 4; i++)
		����call(0, 1);
	����call(0, 2);
	����call(0, 1);
	����call(0, 4);
	����call(0, 8);
	for (int i = 0; i < 7; i++)
		����call(0, 2);
	����call(0, 1);
	����call(0, 1);
	����call();
}

void �����ͼ(int X, int Y)
{
	VMBEGIN
	����call(45);
	����call(X, 1);
	����call(Y, 1);
	for (int i = 0; i < 2; i++)
		����call(0, 4);
	for (int i = 0; i < 9; i++)
		����call(0, 2);
	for (int i = 0; i < 8; i++)
		����call(0, 4);
	for (int i = 0; i < 7; i++)
		����call(0, 2);
	����call(0, 4);
	for (int i = 0; i < 3; i++)
		����call(0, 2);
	����call(0, 8);
	����call(0, 4);
	����call(0, 2);
	����call();
	VMEND
}

void ����ƶ�(int ����, int λ��, int X, int Y)
{
	VMBEGIN
	����call(36);
	����call(����, 1);
	����call(λ��, 1);
	����call(X, 2);
	����call(Y, 2);
	����call(5, 1);
	����call(9, 2);
	����call(2, 2);
	����call(0, 4);
	����call(0, 1);
	����call();
	VMEND
}

void �����ͼ(int ��ͼ��Ϣ, int ��ͼ�Ѷ�, int ��ͼ��Ԩ, int ��ͼ��ϰ)
{
	VMBEGIN
	����call(16);
	����call(��ͼ��Ϣ, 4);
	����call(��ͼ�Ѷ�, 1);
	����call(0, 2);
	����call(��ͼ��Ԩ, 1);
	����call(��ͼ��ϰ, 1);
	����call(65535, 2);
	����call(0, 4);
	����call(0, 4);
	����call(0, 1);
	����call();
	VMEND
}

void �������(int λ��)
{
	VMBEGIN
	����call(22);
	����call(0, 1);
	����call(λ��, 2);
	����call(1, 2);
	����call(0, 4);
	����call(λ�� + 1, 4);
	����call(0, 4);
	����call();
	VMEND
}

void �������(int ��ͼ��Ϣ, int ��ͼ�Ѷ�, int ����ID)
{
	VMBEGIN
	����call(16);
	����call(��ͼ��Ϣ, 4);
	����call(��ͼ�Ѷ�, 1);
	����call(0, 2);
	����call(0, 1);
	����call(0, 1);
	����call(0, 4);
	����call(����ID, 4);
	����call(0, 1);
	����call(0, 1);
	����call();
	VMEND
}
