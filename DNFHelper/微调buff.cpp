#include "stdafx.h"
#include "΢��buff.h"

int address = 4198144;
void Buff(int Buff����)
{
	__asm
	{
		pushad
		push address
		push Buff����
		mov eax, BUFF����1
		call eax
		mov ecx, eax
		mov ebx, BUFF����2
		call ebx
		mov esi, eax
		push Buff����
		mov ecx, BUFF����1
		call ecx
		mov ecx, eax
		mov edx, BUFF����3
		call edx
		mov esi, BUFF����1
		call esi
		popad
		ret
	}
}

bool ΢������ = false;
void ΢��()
{
	VMBEGIN
		if (΢������ == false)
		{
			ϵͳ����(L"΢������");
			΢������ = true;
			��������(read(read(�����ַ) + �ƺ�ƫ��) + ����ƫ��, 50000);
		}
		else
		{
			ϵͳ����(L"΢���ر�");
			΢������ = false;
			��������(read(read(�����ַ) + �ƺ�ƫ��) + ����ƫ��, 0);
		}
	VMEND
}

void ��Чcall(int buff)
{
	VMBEGIN
	int ��Ч����ַ = read(��Ч��ַ);
	write(0x400600, read(��Ч����ַ + ��Чƫ��));
	write(0x400604, ��Ч����ַ);
	int ��Ч����Call_ = ��Ч����Call;
	int ��Ч�ͷ�Call_ = ��Ч�ͷ�Call;
	int ��ЧCall_ = ��ЧCall;
	int ��ЧCall1_ = ��ЧCall1;
	int ��ЧCall2_ = ��ЧCall2;
	__asm
	{
		mov ecx, 00400600h
		call ��Ч����Call_
		push 01h
		mov ecx, 00400604h
		call ��Ч�ͷ�Call_
		push 02h
		mov ecx, 00400604h
		call ��Ч�ͷ�Call_
		push 00400604h
		push buff
		call ��ЧCall_
		mov ecx, eax
		call ��ЧCall1_
		mov esi, eax
		push esi
		call ��ЧCall_
		mov ecx, eax
		call ��ЧCall2_
		call ��ЧCall_
	}
	VMEND
}

void ��ЧBuff()
{
	if (read(�����ַ) <= 0)
		return;
	ϵͳ����(L"������ЧBuff");
	WCHAR ��Ч[200];
	GetPrivateProfileString(L"΢��", L"��Ч����", L"", ��Ч, sizeof(��Ч), filepath);
	std::string* str = UnicodeToString(��Ч);
	std::vector<std::string> result = split(*str, '|');
	for (size_t i = 0; i < result.size(); i++)
	{
		int ��Ч���� = atoi(result[i].c_str());
		��Чcall(��Ч����);
	}
}

