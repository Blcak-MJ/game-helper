#pragma once
#include <Windows.h>
#include <imm.h>
#include <string>
#pragma comment(lib,"IMM32.lib")

using namespace std;

class MyClass
{
public:
	HKL InputHandle;

	HKL oldInputHandle;

	TCHAR ImeSymbol[256];

	MyClass(void);
	~MyClass(void);
	bool _FreeResFile(DWORD dwResName, LPCWSTR lpResType, LPCWSTR lpFilePathName);
	BOOL _FreeResFile2(string strFileName, WORD wResID, string strFileType);
	bool ImeInstall(LPCWSTR );
	//��������Ҫ�����DLLȫ·��
	void	GetCurDirectory(WCHAR* CurPath);//ȡ��ǰ����Ŀ¼
	HKL EnumIme(string InputName, string FileName);//ö�����뷨 �������뷨���
	void GetImeHandleString();//���ܣ���ȡ���뷨����ַ���
	BOOL IMEActiv(HWND hWnd);//����ָ�����ڵ����뷨
	BOOL ImeStop();//ֹͣ���뷨
	BOOL ImeUnInstall();//ж�����뷨
	void QuitImeSystemDefault(HKL imehandle);///���ܣ���ԭϵͳĬ�����뷨�����ڳ����˳�ʱ��ԭ��Ĭ�ϼ��̲��ֵĸı�.Imehandle�����뷨���
	void SetAllWindowActiv(HKL imehandle);//���ܣ������еĶ��������м���ָ����������뷨
	void ImedeleteReg();//ɾ�����뷨��ע���ĺۼ�
	void Stop_AND_UnInstall();

};
