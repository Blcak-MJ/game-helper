#include "stdafx.h"
#include "inject.h"
#include <iostream>

using namespace std;

MyClass::MyClass(void)
{
	HKL InputHandle = NULL;

	HKL oldInputHandle = NULL;
}

MyClass::~MyClass(void)
{
}

typedef int  (WINAPI  *g_IMEClearPubString)();

typedef int  (WINAPI  *g_IMESetPubString)(PWCHAR tmpStr,DWORD UnloadDLL,DWORD loadNextIme,DWORD DllData1,DWORD DllData2,DWORD DllData3);

g_IMEClearPubString IMEClearPubString = NULL;

g_IMESetPubString IMESetPubString = NULL;

HINSTANCE hModule = NULL;
bool MyClass::_FreeResFile(DWORD dwResName, LPCWSTR lpResType, LPCWSTR lpFilePathName)
{
	HMODULE hInstance = ::GetModuleHandle(NULL);//�õ�����ʵ�����          
	HRSRC hResID = ::FindResource(hInstance,MAKEINTRESOURCE(dwResName),lpResType);//������Դ      
	HGLOBAL hRes = ::LoadResource(hInstance,hResID);//������Դ       
	LPVOID pRes = ::LockResource(hRes);//������Դ                   
	if (pRes == NULL)//����ʧ��       
	{           return FALSE;       
	}      
	DWORD dwResSize = ::SizeofResource(hInstance,hResID);//�õ����ͷ���Դ�ļ���С       
	HANDLE hResFile = CreateFile(lpFilePathName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);//�����ļ�                  
	if (INVALID_HANDLE_VALUE == hResFile)     
	{                 
		return FALSE;       
	}              
	DWORD dwWritten = 0;//д���ļ��Ĵ�С          
	WriteFile(hResFile,pRes,dwResSize,&dwWritten,NULL);//д���ļ�      
	CloseHandle(hResFile);//�ر��ļ����                   
	return (dwResSize == dwWritten);//��д���С�����ļ���С�����سɹ�������ʧ�� 
	//ʹ��ʾ��: FreeResFile(IDR_MYRES,"MYRES","D:\\1.exe");
}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//ģ�鹦�ܣ��ͷ���Դ��ĳ���͵��ļ�  ReleaseRes("Test.exe",(WORD)IDR_EXE1,"EXE"))
//�� �� ֵ���ɹ�����TRUE�����򷵻�FALSE 
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//����˵����������			|   ����/���  |        ����˵��
//          strFileName     |"Test.exe"
//          wResID          |(WORD)IDR_EXE1
//          strFileType     |"EXE"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
BOOL MyClass:: _FreeResFile2(string strFileName,WORD wResID,string strFileType)    
{    
	// ��Դ��С    
	DWORD   dwWrite=0;  

	//��λ���ǵ��Զ�����Դ��������Ϊ�����Ǵӱ�ģ�鶨λ��Դ�����Խ�����򵥵���ΪNULL����

	HRSRC hrscr =  FindResourceA(NULL, MAKEINTRESOURCEA(wResID),strFileType.c_str());  

	if (NULL == hrscr)
	{
		return FALSE;
	}

	//��ȡ��Դ�Ĵ�С

	DWORD dwSize = SizeofResource( NULL,hrscr); 

	//������Դ

	HGLOBAL hGlobal = LoadResource(NULL,hrscr);   

	if (NULL == hGlobal)
	{
		return FALSE;
	}

	//������Դ

	LPVOID pBuffer = LockResource(hGlobal); 

	if (NULL == pBuffer)
	{
		return FALSE;
	}

	// �����ļ�    
	HANDLE  hFile = CreateFileA(
		strFileName.c_str(), 
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		); 

	if ( hFile == INVALID_HANDLE_VALUE )    
	{    
		return FALSE;    
	}    

	// д���ļ�    
	WriteFile(hFile,pBuffer,dwSize,&dwWrite,NULL);   

	CloseHandle( hFile ); 

	return TRUE;    
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ�ȡ����Ŀ¼ 
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void MyClass::GetCurDirectory(WCHAR* CurPath)
{
	GetModuleFileName (NULL,CurPath,MAX_PATH);

	for(int i=MAX_PATH-1;i>=0;i--)
	{
		if(*(CurPath+i)!='\\')
		{
			*(CurPath+i)=0;
		}
		else
		{
			break;
		}
	}
} 
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ�ö�����뷨�����ؾ��  InputName�����뷨���ƣ�FileName ���뷨�ļ���
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
HKL MyClass::EnumIme(string InputName,string FileName)
{
	HKL *HKLList;

	HKL Imehandle = NULL;

	int StrCount=0,FileCount=0;

	HKLList = NULL;

	UINT uCount = GetKeyboardLayoutList(0, NULL);

	if (0 != uCount)
	{
		HKLList = new HKL[uCount];

		//�����ϵͳ�������ĵ�ǰ�����Ӧ�ļ��̲��־�����ú��������������ָ���Ļ�������
		GetKeyboardLayoutList(uCount, HKLList);
	}
	else
	{
		int nErr = GetLastError();

	}

	char strLayoutText[256];

	char strFileText[256];

	string InputString;

	string InputFile;

	cout << uCount << endl;

	for (UINT i = 0; i < uCount; i++)
	{
		//ȡ�����뷨��
		StrCount = ImmGetDescriptionA(HKLList[i], strLayoutText, 256);

		InputString = strLayoutText;
		cout << InputString << endl;

		if (InputString == InputName)
		{
			cout << "Same" << endl;
			//�õ������뷨���ļ����ƣ����������ͬ���������뷨�����
			FileCount = ImmGetIMEFileNameA(HKLList[i], strFileText, 256);

			InputFile = strFileText;

			if (InputFile == FileName)
			{
				Imehandle = HKLList[i];

				break;
			}
		}	
	}
	delete[]HKLList;

	return Imehandle;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ���ȡ���뷨����ַ���
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void MyClass::GetImeHandleString()
{
	//���ָ���̵߳Ļ���̲���
	HKL iHandle = GetKeyboardLayout(NULL);

	//���������뷨���̲���
	::ActivateKeyboardLayout(InputHandle,NULL);
	//��ȡ���뷨���̲���
	::GetKeyboardLayoutName(ImeSymbol);
	//����ԭ������̲���
	::ActivateKeyboardLayout (iHandle,NULL);
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ����뷨ע�� 
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
bool MyClass::ImeInstall(LPCWSTR lpszdllName)
{

	//����ԭʼ���̲���

	::SystemParametersInfo(SPI_GETDEFAULTINPUTLANG,NULL,oldInputHandle,NULL);

	//�����ļ���Ŀ¼

	//����Ҫ����  ��Դ�Ը� CopyFile(L"Freeime.dll",L"C:\\WINDOWS\\SYSTEM32\\Freeime.ime",FALSE);

	//CopyFile(L"Gamedll.dll",L"C:\\WINDOWS\\SYSTEM32\\Gamedll.dll",FALSE);

	//�������뷨IME�ļ�,������ǰ����أ���������DLL�����������

	hModule = LoadLibrary(L"C:\\Windows\\System32\\Freeime.ime"); 
	
	//�������뷨

	InputHandle = ImmInstallIME(L"C:\\WINDOWS\\SYSTEM32\\Freeime.ime",L"��Ʒ���.12");
	
	//��ȡ���뷨��ʶ��

	GetImeHandleString();

	//�ж����뷨����Ƿ���Ч

	if (!ImmIsIME(InputHandle))
	{
		//��������ڣ�ö�����뷨���Ҿ��
		InputHandle = EnumIme("�Ϲ⻪��ƴ�����뷨V6.7","C:\\WINDOWS\\SYSTEM32\\unispim6.ime");
	}
	if (hModule)
	{
		IMESetPubString = (g_IMESetPubString)GetProcAddress(hModule, "IMESetPubString");
		if (IMESetPubString)
		{
			/*WCHAR CurPath[MAX_PATH+1] = {NULL};

			wmemset(CurPath,0,MAX_PATH+1);

			GetCurDirectory(CurPath);

			wcscat(CurPath,lpszdllName);*/

			IMESetPubString((PWCHAR)lpszdllName, 0, 0, 0, 0, 0);
		}
		else
		{
			FreeLibrary(hModule);
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ�����ָ���������뷨
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
BOOL MyClass::IMEActiv(HWND hWnd)
{

	if (InputHandle != NULL)
	{
		//����ָ���������뷨
		::PostMessage(hWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)InputHandle);
	} 
	else
	{
		//��������ڣ�ö�����뷨���������
		HKL imehandle = EnumIme("��Ʒ���7.12","C:\\WINDOWS\\SYSTEM32\\Freeime.ime");
		if (imehandle != NULL)
		{
			::PostMessage(hWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)imehandle);
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ�ֹͣ���뷨
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
BOOL MyClass:: ImeStop()
{
	if (hModule)
	{
		IMEClearPubString = (g_IMEClearPubString)GetProcAddress(hModule,"IMEClearPubString"); 

		if (IMEClearPubString)
		{
			IMEClearPubString();
			FreeLibrary(hModule);
		}
		else
		{
			FreeLibrary(hModule);
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ���ԭϵͳĬ�����뷨�����ڳ����˳�ʱ��ԭ��Ĭ�ϼ��̲��ֵĸı�.Imehandle�����뷨���
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void MyClass:: QuitImeSystemDefault(HKL imehandle)
{
	HKL retV = NULL;

	::SystemParametersInfo(SPI_GETDEFAULTINPUTLANG,0,retV,0);

	if (retV != imehandle)
	{
		::SystemParametersInfo(SPI_SETDEFAULTINPUTLANG,0,imehandle,SPIF_SENDWININICHANGE);
	}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ������еĶ��������м���ָ����������뷨
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void MyClass:: SetAllWindowActiv(HKL imehandle)
{
	HWND mhWnd = NULL;

	do 
	{
		mhWnd = ::FindWindowExA(NULL,mhWnd,NULL,NULL);

		if (mhWnd != NULL)
		{
			::PostMessage(mhWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)imehandle);
		}
	} while (mhWnd == NULL);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ�ж�����뷨
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
BOOL MyClass:: ImeUnInstall()
{
	HKL handle;

	//�ָ�����ԭʼ����
	QuitImeSystemDefault(oldInputHandle);

	//�����ж������ڼ���ԭʼ���̲���
	SetAllWindowActiv(oldInputHandle);

	if (InputHandle != NULL)
	{
		//ж�����뷨
		UnloadKeyboardLayout(InputHandle);
	}
	else
	{
		//���������ö�����뷨���Ҿ��
		HKL imehandle = EnumIme("��Ʒ���7.12","C:\\WINDOWS\\SYSTEM32\\Freeime.ime");

		if (imehandle != NULL)
		{
			UnloadKeyboardLayout(imehandle);
		} 
		else
		{
			return FALSE;
		}
	} 

	//���뷨��ʶ�����ڣ�ɾ�����뷨ע���
	if (ImeSymbol != L"")
	{
		ImedeleteReg();
	}	

	//ж�����뷨ģ��
	FreeLibrary(hModule);

	return TRUE;
}
//@//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ�ɾ�����뷨ע���,������
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void MyClass::ImedeleteReg()
{
	HKEY phkResult;

	int i = NULL;

	TCHAR ValueName[255];  //�洢�õ��ļ�ֵ��

	TCHAR lpData[255];     //�洢�õ��ļ�ֵ����

	DWORD lenValue = 255;  //�洢��ֵ�����ݳ���

	DWORD lenData = 255;   //�洢��ֵ�����ݳ���

	//��ע�����Ŀ����ȡ���
	RegOpenKey(HKEY_CURRENT_USER,L"Keyboard Layout\\Preload",&phkResult);

	//ö��ע�����Ŀ
	while(RegEnumValue (phkResult,i,ValueName,&lenValue,NULL,NULL,(LPBYTE)lpData,&lenData) != ERROR_NO_MORE_ITEMS)
	{
		//Dbg_Print("1:%ws\n",ImeSymbol);//���뷨��ʶ��

		//Dbg_Print("2:%ws\n",ValueName);//ע�����Ŀ

		//Dbg_Print("3:%ws\n",lpData);   //ע�����Ŀ��ֵ

		if (lenData != NULL)
		{
			if (_tcscmp(ImeSymbol,lpData)==NULL)
			{
				//AfxMessageBox(_T("ɾ��ע�����"));
				RegDeleteValue (phkResult,ValueName);//ɾ����Ŀ��ֵ
				break;
			}
		}

		//�����������ñ����������������Ϊ�գ������������ݲ�ȫ �磺E0200804 ��ȫΪ��0000804
		memset(lpData, 0, sizeof(lpData));

		memset(ValueName, 0, sizeof(ValueName));

		lenValue = 255; 

		lenData = 255;

		i++;
	}
}

void MyClass:: Stop_AND_UnInstall()
{
	ImeStop();
	ImeUnInstall();
}