// InjectDll2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CInjectDll2App:
// �йش����ʵ�֣������ InjectDll2.cpp
//

class CInjectDll2App : public CWinApp
{
public:
	CInjectDll2App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CInjectDll2App theApp;