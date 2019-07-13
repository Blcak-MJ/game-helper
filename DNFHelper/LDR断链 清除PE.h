#pragma once

/*
��Ӧ�ò�ͨ���޸�PEB�ṹ�е�ģ�����������ر������е�ĳ��ģ��
���Խ������ProcessExplorer��Ч����IS��Ч,ʹ��PCHunter64�鿴ģ�飬���ص�ģ�����ʾ��ͬ����ɫ��
		  ��PowerTools��Ч
*/

#include "stdafx.h"
#include <Subauth.h>
#include <stdio.h>

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	LPVOID DllBase;
	LPVOID EntryPoint;
	SIZE_T SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

static BOOL RemoveLdr(HINSTANCE DllInstance);

static BOOL ClearPE(HINSTANCE DllInstance);

BOOL Hide(HMODULE DllInstance);