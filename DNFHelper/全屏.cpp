#include "stdafx.h"
#include "ȫ��.h"

/*
11422 Ѫ��
38002 Ѫ��
54141 ������ɱ
25540 ������ż����
39002 ������
*/
int ����Ƶ��;
int �����˺�;
int ���ܸ���;
int ���ܴ���;
int ���ܴ��뼯��[100];
int Obj·��[100], Atk[100] = { 0 };
int ���ܴ������;
int index = 0;

int ȡOBJ�ı�·��(int ID)
{
	VMBEGIN
	int ebp_4 = Ŀ¼��ַ;
	int ebp_8 = ·��Call;
	_asm
	{
		push ID
		mov ecx, ebp_4
		call ebp_8
		mov ebp_4, eax
	}
	VMEND
	return ebp_4;
}

int ȡ����AtkĿ¼(int Obj·���ı�)
{
	VMBEGIN
	int ������Ϣ_ = ������Ϣ;
	int ����_Call = ����Call;
	int �ָ�_Call = �ָ�Call;
	int Atk·��_��ַ = ·����ַ;
	int Atk·��_Call = ����Call;
	int AtkĿ¼ = 0;
	_asm
	{
		mov ecx, ������Ϣ_
		mov ecx, [ecx]
		push 0x01
		push Obj·���ı�
		call ����_Call
		test eax, eax
		je Label1
		mov edi, eax
		lea esi, [edi + 0x000000B4]
		lea eax, [edi + 0x000000F4]
		push esi
		push eax
		lea edx, ������Ϣ_
		push edx
		mov[edx], 0x00000000
		call �ָ�_Call
		add esp, 0x0C
		mov eax, [eax]
		mov ecx, Atk·��_��ַ
		mov ecx, [ecx]
		push 0x01
		push eax
		call Atk·��_Call
		Label1 :
		mov AtkĿ¼, eax
	}
	return AtkĿ¼;
	VMEND

}


void �޸��˺�(int ����, int �˺�)
{
	VMBEGIN
	int Obj·�� = ȡOBJ�ı�·��(����);
	if (Obj·�� > 0)
	{
		int Atk = ȡ����AtkĿ¼(Obj·��);
		if (Atk > 0)
		{
			��������(Atk + 32, �˺�);
		}
	}
	VMEND
}

void ����()
{
	int һ��ƫ�� = read(�����ַ);
	int ����ƫ�� = read(һ��ƫ�� + ��ͼƫ��);
	if (����ƫ�� == 0)
		return;
	int �׵�ַ_ = read(����ƫ�� + �׵�ַ);
	int β��ַ_ = read(����ƫ�� + β��ַ);
	int �������� = (β��ַ_ - �׵�ַ_) / 4;
	for (int i = 0; i <= ��������; i++)
	{
		int ��ַ = read(�׵�ַ_ + 4 * i);
		int ���� = read(��ַ + ����ƫ��);
		int ���� = read(��ַ + �������);
		int x, y;
		x = (int)read<float>(��ַ + X����);
		y = (int)read<float>(��ַ + Y����);
		if (���� == 10660)
		{
			�����¼�();
			�ͷ�call(һ��ƫ��, 11435, 0, x, y, 0);
			�ͷ�call(һ��ƫ��, 11435, 0, x, y, 0);
			continue;
		}
		else if (���� == 1057)
		{
			�����¼�();
			�ͷ�call(һ��ƫ��, 11435, 0, x, y, 0);
		}
	}
}

void ȫ������()
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
	int x, y, z;
	if (�����˺� == 0)
	{
		int sum = 0, cnt = 0;
		for (int i = 1; i <= ��������; i++)
		{
			int ��ַ = read(�׵�ַ_ + 4 * i);
			if (��ַ <= 0)
				continue;
			int ���� = read(��ַ + ����ƫ��);
			int ��Ӫ = read(��ַ + ��Ӫƫ��);
			int Ѫ�� = read(��ַ + ����Ѫ��ƫ��);
			if ((���� == 529 || ���� == 545 || ���� == 273) && ��Ӫ > 0 && Ѫ�� > 0)
			{
				cnt++;
				sum += Ѫ��;
			}
		}
		if (cnt == 0) return;
		for (int i = 0; i < ���ܴ������; i++)
		{
			��������(Atk[i] + 32, sum / cnt );
		}
	}
	for (int i = 0; i <= ��������; i++)
	{
		int ��ַ = read(�׵�ַ_ + 4 * i);
		if (��ַ <= 0)
			continue;
		int ���� = read(��ַ + ����ƫ��);
		int ��Ӫ = read(��ַ + ��Ӫƫ��);
		int Ѫ�� = read(��ַ + ����Ѫ��ƫ��);
		int ���� = read(��ַ + �������);
		x = (int)read<float>(��ַ + X����);
		y = (int)read<float>(��ַ + Y����);
		z = (int)read<float>(��ַ + Z����);
		if ((���� == 529 || ���� == 545 || ���� == 273) &&  ��Ӫ > 0 && Ѫ�� > 0 && ��ַ != һ��ƫ��)
		{
			���ܴ��� = ���ܴ��뼯��[index % ���ܴ������];
			�ͷ�call(һ��ƫ��, ���ܴ���, 0, x, y, z);
			��������_ += 1;
			index++;
			if (��������_ == ���ܸ���)
				break;
		}
		
	}
	if (index > 100)
		index = 0;
	
	VMEND
}

DWORD ����ѭ��(LPVOID lpParam)
{
	VMBEGIN
	ϵͳ����(L"ȫ������");
	int cnt = 0;
	memset(Atk, 0, sizeof(Atk));
	while (true)
	{
		if (read(�����ַ) <= 0)
		{
			Sleep(1000);
			continue;
		}
		if (�Ƿ��ڳ���() == false)
		{
			Sleep(8000);
			break;
		}
		Sleep(500);
	}
	for (int i = 0; i < ���ܴ������; i++)
	{
		Atk[i] = ȡ����AtkĿ¼(Obj·��[i]);
	}
	if (�����˺� > 1)
	{
		for (int i = 0; i < ���ܴ������; i++)
		{
			��������(Atk[i] + 32, �����˺�);
		}
	}
	�޸��˺�(11435, 123456);
	while (true)
	{
		if (read(�����ַ) <= 0)
		{
			Sleep(1000);
			continue;
		}	
#ifdef ����
		���ܴ��� = GetPrivateProfileInt(L"ȫ��", L"���ܴ���", 0, filepath);
		�����˺� = GetPrivateProfileInt(L"ȫ��", L"�����˺�", 0, filepath);
		���ܸ��� = GetPrivateProfileInt(L"ȫ��", L"���ܸ���", 0, filepath);
		����Ƶ�� = GetPrivateProfileInt(L"ȫ��", L"����Ƶ��", 0, filepath);
#endif
		if (cnt % 200 == 0 && �����˺� == 1)
		{
			int x = ��ǰ�ȼ�();
			double �˺� = 0.000443*pow(x, 5) - 0.04617*pow(x, 4) + 1.751*pow(x, 3) - 15.49*pow(x, 2) + 113.4*x + 192.4;
			for (int i = 0; i < ���ܴ������; i++)
			{
				��������(Atk[i] + 32, (int)�˺�);
			}
		}
		����();
		�����¼�();
		ȫ������();
		Sleep(����Ƶ��);
		cnt++;
	}
	VMEND
	return 0;
}

bool ����ȫ������ = false;
HANDLE �����߳�2 = NULL;
void ����ȫ������()
{
	VMBEGIN
	if (����ȫ������ == false)
	{
		ϵͳ����(L"����ȫ������");
		����ȫ������ = true;
		WCHAR ����[200];
		GetPrivateProfileString(L"ȫ��", L"���ܴ���", L"25540|24012", ����, sizeof(����), filepath);
		std::string* str = UnicodeToString(����);
		std::vector<std::string> result = split(*str, '|');
		���ܴ������ = result.size();
		for (size_t i = 0; i < result.size(); i++)
		{
			���ܴ��뼯��[i] = atoi(result[i].c_str());
			Obj·��[i] = ȡOBJ�ı�·��(���ܴ��뼯��[i]);
		}
		�����˺� = GetPrivateProfileInt(L"ȫ��", L"�����˺�", 0, filepath);
		���ܸ��� = GetPrivateProfileInt(L"ȫ��", L"���ܸ���", 0, filepath);
		����Ƶ�� = GetPrivateProfileInt(L"ȫ��", L"����Ƶ��", 0, filepath);
		WCHAR tmp[200];
		format(tmp, L"���ܴ���:%s �����˺�:%d ����Ƶ��:%d", ����, �����˺�, ����Ƶ��);
		ϵͳ����(tmp);
		�����߳�2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)����ѭ��, NULL, 0, NULL);
		SetThreadPriority(�����߳�2, THREAD_PRIORITY_IDLE);
	}
	else
	{
		����ȫ������ = false;
		TerminateThread(�����߳�2, 0);
		ϵͳ����(L"����ȫ�ر�");
	}
	VMEND
}


bool ȫ����ɱ���� = false;
HANDLE �����߳�3 = NULL;
void ȫ����ɱ()
{
	VMBEGIN
		/*if (ȫ����ɱ���� == false)
		{
			ϵͳ����(L"ȫ����ɱ����");
			���ܴ��� = GetPrivateProfileInt(L"ȫ��", L"��ɱ����", 0, filepath);
			ȫ����ɱ���� = true;
			�����߳�3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)����ѭ��, NULL, 0, NULL);

		}
		else
		{
			ȫ����ɱ���� = false;
			TerminateThread(�����߳�3, 0);
			ϵͳ����(L"ȫ����ɱ�ر�");
		}*/
	VMEND

}