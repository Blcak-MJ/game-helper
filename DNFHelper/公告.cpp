#include "stdafx.h"
#include "����.h"


void ϵͳ����(LPCWSTR ����)
{
	VMBEGIN
	int �������� = 37;
	int ������ɫ = ��ɫ; //��ɫ
	int ���ȹ���_ = ���ȹ���;

	_asm
	{
		mov ecx, �̵��ַ
		mov ecx, [ecx]
		mov ecx, [ecx + 0x50]
		push 00h
		push 00h
		push 00h
		push 00h
		push ��������
		push ������ɫ
		push ����
		call ���ȹ���_
	}
	VMEND
}

void ����(const wchar_t * str, ...)
{
	WCHAR* p = new WCHAR[200];
	va_list va;
	va_start(va, str);
	_vstprintf_s(p, 200, str, va);
	va_end(va);
	ϵͳ����(p);
	delete p;
}