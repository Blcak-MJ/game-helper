#pragma once
#include <imm.h>
#pragma comment(lib,"IMM32.lib")
#pragma warning( disable: 4005 )
#pragma warning( disable: 4102 )
#pragma warning( disable: 4101 )
#pragma warning( disable: 4305 )
#pragma warning( disable: 4312 )
#pragma warning( disable: 4311 )
#pragma warning( disable: 4244 )
#pragma warning( disable: 4267 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4533 )
#pragma warning( disable: 4700 )

class InjectClass
{
public:
	HKL InputHandle ;

	HKL oldInputHandle ;
	
	TCHAR ImeSymbol[255];

	InjectClass(void);
	
	~InjectClass(void);
	bool _FreeResFile(DWORD dwResName, LPCWSTR lpResType, LPCWSTR lpFilePathName);

	BOOL _FreeResFile2(CString strFileName,WORD wResID,CString strFileType);    

	bool ImeInstall(LPCWSTR /*lpszdllName[]*/);

	//��������Ҫ�����DLLȫ·��
	void	GetCurDirectory(WCHAR* CurPath);//ȡ��ǰ����Ŀ¼

	HKL EnumIme(CString InputName,CString FileName);//ö�����뷨 �������뷨���

	void GetImeHandleString();//���ܣ���ȡ���뷨����ַ���

	BOOL IMEActiv(HWND hWnd);//����ָ�����ڵ����뷨

	BOOL ImeStop();//ֹͣ���뷨

	BOOL ImeUnInstall();//ж�����뷨

	void QuitImeSystemDefault(HKL imehandle);///���ܣ���ԭϵͳĬ�����뷨�����ڳ����˳�ʱ��ԭ��Ĭ�ϼ��̲��ֵĸı�.Imehandle�����뷨���
	
	void SetAllWindowActiv(HKL imehandle);//���ܣ������еĶ��������м���ָ����������뷨
	
	void ImedeleteReg();//ɾ�����뷨��ע���ĺۼ�
	
	void Stop_AND_UnInstall();
	
	void  Test(CString MSG);

};
