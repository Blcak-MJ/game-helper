#include "stdafx.h"
#include "�ж�.h"

bool �Ƿ��ڳ���()
{
	int tmp = read(read(�����ַ) + ��ͼƫ��);
	return tmp == 0;
}

bool �Ƿ�����Ʒ()
{
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
	if (����ƫ�� <= 0)
		return false;
	int �׵�ַ_ = read(����ƫ�� + �׵�ַ);
	int β��ַ_ = read(����ƫ�� + β��ַ);
	int �����ַ = һ��ƫ��;
	int ���� = (β��ַ_ - �׵�ַ_) / 4;
	float x = read<float>(�����ַ + X����);
	float y = read<float>(�����ַ + Y����);
	for (int i = 1; i <= ����; i++)
	{
		int ��ַ = read(�׵�ַ_ + 4 * i);
		int ���� = read(��ַ + ����ƫ��);
		if (���� == 289 && ��ַ != һ��ƫ��)
		{
			return true;
		}
	}
	return false;
}

bool �Ƿ���()
{
	if (����(read(read(�����ַ) + ��ͼƫ��) + 280) == 0)
		return true;
	return false;
}


int ����ƣ��ֵ()
{
	return ����(����ƣ��);
}

int ʣ��ƣ��()
{
	return ����(���ƣ��) - ����(����ƣ��);
}

bool �Ƿ��Ʋ�()
{
	return read(�Ʋû�ַ) != 0;
}

bool �Ƿ���BOSS��()
{
	int bossx = ����(read(read(read(������) + ʱ���ַ) + 204) + BOSS����X);
	int bossy = ����(read(read(read(������) + ʱ���ַ) + 204) + BOSS����Y);
	int curx = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����X);
	int cury = read(read(read(read(������) + ʱ���ַ) + 204) + ��ǰ����Y);
	return curx == bossx && cury == bossy;
}

bool �Ƿ�����ɫ()
{
	if (read(�����ַ) > 0)
		return true;
	return false;
}

int ��ǰ�ȼ�()
{
	return read(��ɫ�ȼ�);
}
