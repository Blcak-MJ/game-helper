#include "stdafx.h"
#include "���ù���.h"
#include "΢��buff.h"

void ����()
{
	if (�Ƿ��ڳ���() == false) {
		int ���ֵ�ַ = read(���ֻ�ַ);
		��������(���ֵ�ַ + 272, 6542475);
		Sleep(300);
	}

}

void ͸��call(int ����)
{
	VMBEGIN
	int call��ַ = �޵�Call;
	_asm
	{
		mov ecx, ����
		mov esi, ecx
		push 0xFF
		push 0x01
		push 0x01
		push 0x01
		mov edx, call��ַ
		call edx
	}
	VMEND
}

void ͸��()
{
	if (�Ƿ��ڳ���() == false)
	{
		͸��call(read(�����ַ));
	}
}

BOOL �Զ�͸������ = FALSE;
HANDLE ͸���߳� = NULL;
BOOL ����͸�� = FALSE;
DWORD ͸��ѭ��()
{
	int ��Ч = 0;
	while(true)
	{
		if (read(�����ַ) <= 0)
		{
			��Ч = 0;
			Sleep(1000);
			continue;
		}
		if (�Ƿ��ڳ���())
		{
			����͸�� = FALSE;
			if (��Ч == 0)
			{
				��Ч = 1;
				��ЧBuff();
			}
		}
		else if (�Ƿ���BOSS��())
		{
			����͸�� = FALSE;
		}
		else if (����͸�� == FALSE)
		{
			����͸�� = TRUE;
			͸��();
			Sleep(500);
			����();
			Sleep(500);
		}
		Sleep(4000);
	}
	return 0;
}

void �Զ�͸��()
{
	if (�Զ�͸������ == TRUE)
	{
		ϵͳ����(L"�ر��Զ�͸��");
		�Զ�͸������ = FALSE;
		SuspendThread(͸���߳�);
		SetThreadPriority(͸���߳�, THREAD_PRIORITY_IDLE);
	}
	else
	{
		�Զ�͸������ = TRUE;
		ϵͳ����(L"�����Զ�͸��");
		if (͸���߳� == NULL)
			͸���߳� = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)͸��ѭ��, NULL, 0, NULL);
		else
			ResumeThread(͸���߳�);
	}
}


bool ��CD���� = false;
const int ������CD = 0x0225CA86;
void ��CD()
{
	VMBEGIN
	DWORD oldprotect;
	VirtualProtect((LPVOID)������CD, 8, PAGE_EXECUTE_READWRITE, &oldprotect);
	if (��CD���� == FALSE)
	{
		write<BYTE>(������CD, 0xeb);
		��CD���� = TRUE;
		ϵͳ����(L"������cd����");
	}
	else
	{
		write<BYTE>(������CD, 0x75);
		��CD���� = FALSE;
		ϵͳ����(L"������cd�ر�");
	}
	VirtualProtect((LPVOID)������CD, 8, oldprotect, &oldprotect);
	VMEND
}


void ��������(int �����ַ, int x, int y, int z)
{
	write(read(�����ַ + 172) + 16, x);
	write(read(�����ַ + 172) + 20, y);
}

void ʰȡ()
{
	VMBEGIN
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
	int �׵�ַ_ = read(����ƫ�� + �׵�ַ);
	int β��ַ_ = read(����ƫ�� + β��ַ);
	int ��Ʒ���� = (β��ַ_ - �׵�ַ_) / 4;
	for (int i = 1; i <= ��Ʒ����; i++)
	{
		int ��ַ = read(�׵�ַ_ + 4 * i);
		int ���� = read(��ַ + ����ƫ��);
		if (���� == 289 && ��ַ != һ��ƫ��)
		{
			���ʰȡ(����(��ַ + 160));
			Sleep(100);
		}
	}
	VMEND
}


int ȡ����ַ(int ��ַ)
{
	int edi = read(��ַ + 160);
	int ecx = read(read(���ܻ�ַ) + (edi >> 16) * 4 + 36);
	ecx = read(ecx + (edi & 65535) * 4 + 8468);
	ecx = ecx & 65535;
	ecx = ecx + (ecx << 16);
	return ecx ^ (read(��ַ + 160) + 8);
}



void ���־���()
{
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
	int �׵�ַ_ = read(����ƫ�� + �׵�ַ);
	int β��ַ_ = read(����ƫ�� + β��ַ);
	int �����ַ = һ��ƫ��;
	int �������� = (β��ַ_ - �׵�ַ_) / 4;
	float x = read<float>(�����ַ + X����);
	float y = read<float>(�����ַ + Y����);
	for (int i = 1; i <= ��������; i++)
	{
		int ��ַ = read(�׵�ַ_ + 4 * i);
		int ���� = read(��ַ + ����ƫ��);
		if ((���� == 529 || ���� == 545 || ���� == 273 || ���� == 289) &&��ַ != һ��ƫ��)
		{
			write(read(��ַ + 172) + 16, x);
			write(read(��ַ + 172) + 20, y);
		}
	}

}

void ����()
{
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
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
			write(read(��ַ + 172) + 16, x);
			write(read(��ַ + 172) + 20, y);
		}
	}
}

void ��ʼ������()
{
	char *filepathA = UnicodeToAscii(filepath);
	if (_access(filepathA, 0) == -1)
	{
		WritePrivateProfileString(L"ȫ��", L"���ܴ���", L"25540",filepath);
		WritePrivateProfileString(L"ȫ��", L"��ɱ����", L"39002", filepath);
		WritePrivateProfileString(L"ȫ��", L"�����˺�", L"123456", filepath);
		WritePrivateProfileString(L"ȫ��", L"���ܸ���", L"4", filepath);
		WritePrivateProfileString(L"ȫ��", L"����Ƶ��", L"1000", filepath);
		WritePrivateProfileString(L"��ż����", L"��ż����", L"416", filepath);
		WritePrivateProfileString(L"��ż����", L"�������", L"69200", filepath);
		WritePrivateProfileString(L"΢��", L"��Ч����", L"165|1109|1108|168|176|175|121", filepath);
	}
	delete filepathA;
}

int ��ӳ��(int ��)
{
	if (�� == VK_F1)
		�� = 328;
	else if (�� == VK_F2)
		�� = 329;
	else if (�� == VK_F3)
		�� = 330;
	else if (�� == VK_F4)
		�� = 331;
	else if (�� == VK_F5)
		�� = 332;
	else if (�� == VK_F6)
		�� = 333;
	else if (�� == VK_F7)
		�� = 334;
	else if (�� == VK_F8)
		�� = 335;
	else if (�� == VK_F9)
		�� = 336;
	else if (�� == VK_F10)
		�� = 337;
	else if (�� == VK_F11)
		�� = 338;
	else if (�� == VK_F12)
		�� = 339;
	else if (�� == '1')
		�� = 271;
	else if (�� == '2')
		�� = 272;
	else if (�� == '3')
		�� = 273;
	else if (�� == '4')
		�� = 274;
	else if (�� == '5')
		�� = 275;
	else if (�� == '6')
		�� = 276;
	else if (�� == '7')
		�� = 277;
	else if (�� == '8')
		�� = 278;
	else if (�� == '9')
		�� = 279;
	else if (�� == '0')
		�� = 280;
	else if (�� == 'Q')
		�� = 285;
	else if (�� == 'W')
		�� = 286;
	else if (�� == 'E')
		�� = 287;
	else if (�� == 'R')
		�� = 288;
	else if (�� == 'T')
		�� = 289;
	else if (�� == 'Y')
		�� = 290;
	else if (�� == 'U')
		�� = 291;
	else if (�� == 'I')
		�� = 292;
	else if (�� == 'O')
		�� = 293;
	else if (�� == 'P')
		�� = 294;
	else if (�� == 'A')
		�� = 299;
	else if (�� == 'S')
		�� = 300;
	else if (�� == 'D')
		�� = 301;
	else if (�� == 'F')
		�� = 302;
	else if (�� == 'G')
		�� = 303;
	else if (�� == 'H')
		�� = 304;
	else if (�� == 'J')
		�� = 305;
	else if (�� == 'K')
		�� = 306;
	else if (�� == 'L')
		�� = 307;
	else if (�� == 'Z')
		�� = 313;
	else if (�� == 'X')
		�� = 314;
	else if (�� == 'C')
		�� = 315;
	else if (�� == 'V')
		�� = 316;
	else if (�� == 'B')
		�� = 317;
	else if (�� == 'N')
		�� = 318;
	else if (�� == 'M')
		�� = 319;
	else if (�� == VK_UP)
		�� = 469;
	else if (�� == VK_DOWN)
		�� = 477;
	else if (�� == VK_LEFT)
		�� = 472;
	else if (�� == VK_RIGHT)
		�� = 474;
	else if (�� == VK_SPACE)
		�� = 326;
	else if (�� == MOD_ALT)
		�� = 325;
	else if (�� == VK_ESCAPE)
		�� = 270;
	return ��;
}

void ����(int ��)
{
	write<BYTE>(read(������ַ) + ��ӳ��(��), 0x01);
}

void ̧��(int ��)
{
	write<BYTE>(read(������ַ) + ��ӳ��(��), 0x00);
}

void ����(int ��, int ʱ��)
{
	if (ʱ�� == 0)
		ʱ�� = 333;
	�� = ��ӳ��(��);
	write<BYTE>(read(������ַ) + ��, 0x01);
	Sleep(ʱ��);
	write<BYTE>(read(������ַ) + ��, 0x00);
}

void װ������()
{
	int ����ָ�� = read(������ַ);
	int �׵�ַ_ = read(����ָ�� + ����ƫ��);
	int װ���� = �׵�ַ_ + 36;
	for (int i = 0; i < 56; i++)
	{
		int װ����ַ = read(װ���� + 4 * i);
		if (װ����ַ != 0)
		{
			int װ������ = read(װ����ַ + װ��Ʒ��);
			if (װ������ == 0 || װ������ == 1 || װ������ == 2)
			{

				�������(i + 8);
				�����¼�();
				Sleep(100);
			}
		}
	}
}

void �������()
{
	VMBEGIN
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
	if (����ƫ�� == 0)
		return;
	int �׵�ַ_ = read(����ƫ�� + �׵�ַ);
	int β��ַ_ = read(����ƫ�� + β��ַ);
	int �������� = (β��ַ_ - �׵�ַ_) / 4;
	int ��������_ = 0;
	int x, y;
	for (int i = 1; i <= ��������; i++)
	{
		int ��ַ = read(�׵�ַ_ + 4 * i);
		if (��ַ <= 0)
			continue;
		int ���� = read(��ַ + ����ƫ��);
		int ��Ӫ = read(��ַ + ��Ӫƫ��);
		int Ѫ�� = read(��ַ + ����Ѫ��ƫ��);
		int ���� = read(��ַ + �������);
		if ((���� == 529 || ���� == 545 || ���� == 273) && ��Ӫ > 0 && Ѫ�� > 0 && ��ַ != һ��ƫ��)
		{
			x = (int)read<float>(��ַ + X����);
			y = (int)read<float>(��ַ + Y����);
			����call(һ��ƫ��, x, y, 0);
			break;
		}

	}
	VMEND
}
